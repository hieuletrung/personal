#include "Worker.h"
#include <QThread>
#include <QThreadPool>
#include <QDebug>
#include <QHostAddress>

#include "Job.h"
#include "JobRequest.h"
#include "MessageUtils.h"

Worker::Worker(QObject* parent) :
    QObject(parent),
    mSocket(this),
    mSocketReader(&mSocket),
    mReceivedJobsCounter(0),
    mSentJobsCounter(0)
{
    connect(&mSocket, &QTcpSocket::connected, [this] {
                                                    qDebug() << "Connected";
                                                    sendRegister();
                                                });
    connect(&mSocket, &QTcpSocket::disconnected, [] {
                                                    qDebug() << "Disconnected";
                                                });
    connect(&mSocket, &QTcpSocket::readyRead, this, &Worker::readMessages);

    mSocket.connectToHost(QHostAddress::LocalHost, 5000);
}

Worker::~Worker()
{
    sendUnregister();
}

void Worker::sendUnregister()
{
    MessageUtils::sendMessage(mSocket,
    Message::Type::WORKER_UNREGISTER, true);
}

void Worker::sendRegister()
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out << QThread::idealThreadCount();
    MessageUtils::sendMessage(mSocket, Message::Type::WORKER_REGISTER, data);
}

void Worker::readMessages()
{
    auto messages = MessageUtils::readMessages(mSocketReader);
    qDebug() << "readMessages() ";

    for(auto& message : *messages) {
        switch (message->type) {
        case Message::Type::JOB_REQUEST:
            handleJobRequest(*message);
            break;
        case Message::Type::ALL_JOBS_ABORT:
            handleAllJobsAbort(*message);
            break;
        default:
            break;
        }
    }
}

void Worker::handleJobRequest(Message& message)
{
    QDataStream in(&message.data, QIODevice::ReadOnly);
    QList<JobRequest> requests;
    in >> requests;
    mReceivedJobsCounter += requests.size();
    for(const JobRequest& jobRequest : requests) {
        QThreadPool::globalInstance()->start(createJob(jobRequest));
    }
}

Job* Worker::createJob(const JobRequest& jobRequest)
{
    Job* job = new Job(jobRequest);
    connect(this, &Worker::abortAllJobs, job, &Job::abort);
    connect(job, &Job::jobCompleted, this, &Worker::sendJobResult);
    return job;
}

void Worker::sendJobResult(JobResult jobResult)
{
    mSentJobsCounter++;
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out << jobResult;
    MessageUtils::sendMessage(mSocket, Message::Type::JOB_RESULT, data);
}

void Worker::handleAllJobsAbort(Message& /*message*/)
{
    emit abortAllJobs();
    QThreadPool::globalInstance()->clear();
    mReceivedJobsCounter = 0;
    mSentJobsCounter = 0;
}

int Worker::receivedJobsCounter() {
    return mReceivedJobsCounter;
}

int Worker::sentJobsCounter() {
    return mSentJobsCounter;
}
