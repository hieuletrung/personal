#ifndef JOB_H
#define JOB_H

#include <QObject>
#include <QRunnable>
#include <QPointF>
#include <QSize>
#include <QAtomicInteger>

#include "JobResult.h"

class Job : public QObject, public QRunnable
{
    Q_OBJECT
public:
    Job(QObject *parent = nullptr);
    void run() override;

    void setPixelPositionY(int value);
    void setMoveOffset(const QPointF& value);
    void setScaleFactor(double value);
    void setAreaSize(const QSize& value);
    void setIterationMax(int value);

signals:
    void jobCompleted(JobResult jobResult);

public slots:
    void abort();

private:
    QAtomicInteger<bool> mAbort;
    /**
     * @brief picture height index.
     */
    int mPixelPositionY;
    /**
     * @brief Mandelbrot origin offset. The user can pan the picture, so the origin will not always be (0, 0).
     */
    QPointF mMoveOffset;
    /**
     * @brief the Mandelbrot scale value. The user can also zoom into the picture.
     */
    double mScaleFactor;
    /**
     * @brief final picture size in a pixel.
     */
    QSize mAreaSize;
    /**
     * @brief the count of iterations allowed to determine the Mandelbrot result for one pixel.
     */
    int mIterationMax;
};

#endif // JOB_H
