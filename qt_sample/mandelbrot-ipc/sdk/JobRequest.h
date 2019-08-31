#ifndef _JOB_REQUEST_H_
#define _JOB_REQUEST_H_

#include <QSize>
#include <QPointF>
#include <QDataStream>

struct JobRequest
{
    int pixelPositionY;
    QPointF moveOffset;
    double scaleFactor;
    QSize areaSize;
    int iterationMax;
};

Q_DECLARE_METATYPE(JobRequest)

inline QDataStream& operator<<(QDataStream& out, const JobRequest& jobRequest)
{
    out << jobRequest.pixelPositionY
        << jobRequest.moveOffset
        << jobRequest.scaleFactor
        << jobRequest.areaSize
        << jobRequest.iterationMax;
    return out;
}

inline QDataStream& operator>>(QDataStream& in, JobRequest& jobRequest)
{
    in >> jobRequest.pixelPositionY;
    in >> jobRequest.moveOffset;
    in >> jobRequest.scaleFactor;
    in >> jobRequest.areaSize;
    in >> jobRequest.iterationMax;
    return in;
}

#endif
