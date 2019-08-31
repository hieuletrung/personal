#ifndef _JOB_RESULT_H_
#define _JOB_RESULT_H_

#include <QSize>
#include <QVector>
#include <QPointF>
#include <QDataStream>

struct JobResult
{
    JobResult(int valueCount = 1) :
        areaSize(0, 0),
        pixelPositionY(0),
        moveOffset(0, 0),
        scaleFactor(0.0),
        values(valueCount)
    {
    }

    QSize areaSize;
    int pixelPositionY;
    QPointF moveOffset;
    double scaleFactor;
    QVector<int> values;
};

Q_DECLARE_METATYPE(JobResult)


inline QDataStream& operator<<(QDataStream& out, const JobResult& jobResult)
{
    out << jobResult.areaSize
        << jobResult.pixelPositionY
        << jobResult.moveOffset
        << jobResult.scaleFactor
        << jobResult.values;
    return out;
}

inline QDataStream& operator>>(QDataStream& in,  JobResult& jobResult)
{
    in >> jobResult.areaSize;
    in >> jobResult.pixelPositionY;
    in >> jobResult.moveOffset;
    in >> jobResult.scaleFactor;
    in >> jobResult.values;
    return in;
}

#endif
