#ifndef WORKER_H
#define WORKER_H


#include <QObject>
#include <QTcpSocket>
#include <QDataStream>

#include "Message.h"
#include "JobResult.h"
#include "JobRequest.h"
#include "Job.h"

class Worker : public QObject
{
    Q_OBJECT

public:
    Worker(QObject* parent = nullptr);
    ~Worker();
    int receivedJobsCounter();
    int sentJobsCounter();

signals:
    void abortAllJobs();
private slots:
    void readMessages();

private:
    void sendRegister();
    void handleJobRequest(Message& message);
    void handleAllJobsAbort(Message& message);
    void sendJobResult(JobResult jobResult);
    void sendUnregister();
    Job* createJob(const JobRequest& jobRequest);

private:
    QTcpSocket mSocket;
    QDataStream mSocketReader;
    int mReceivedJobsCounter;
    int mSentJobsCounter;
};

#endif // WORKER_H
