#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <QByteArray>
#include <QDataStream>

struct Message {
    enum class Type {
        // This is the message sent by the worker when it first connects to the application. The content of the message is only the number of cores of the worker's CPU.
        WORKER_REGISTER,
        // This is the message sent by the worker when it is disconnected. This lets the application know that it should remove this worker from its list and stop sending any messages to it.
        WORKER_UNREGISTER,
        // This is the message sent by the application each time a picture generation is canceled. The worker is then responsible for canceling all its current local threads.
        ALL_JOBS_ABORT,
        // This is the message sent by the application to calculate a specific line of the desired picture.
        JOB_REQUEST,
        // This is the message sent by the worker with the calculated result from the JOB_REQUEST inputs.
        JOB_RESULT,
    };

    Message(const Type type = Type::WORKER_REGISTER, const QByteArray& data = QByteArray()) : type(type), data(data)
    {
    }

    ~Message() {}

    Type type;
    QByteArray data;
};

inline QDataStream &operator<<(QDataStream &out, const Message &message)
{
    out << static_cast<qint8>(message.type)
        << message.data;
    return out;
}

inline QDataStream &operator>>(QDataStream &in, Message &message)
{
    qint8 type;
    in >> type;
    in >> message.data;
    message.type = static_cast<Message::Type>(type);
    return in;
}

#endif
