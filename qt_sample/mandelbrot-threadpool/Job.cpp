#include "Job.h"

#include <QDebug>

Job::Job(QObject* parent) :
    QObject(parent),
    mAbort(false),
    mPixelPositionY(0),
    mMoveOffset(0.0, 0.0),
    mScaleFactor(0.0),
    mAreaSize(0, 0),
    mIterationMax(1)
{

}

void Job::run()
{
//    qDebug() << "Job::run";

    JobResult jobResult(mAreaSize.width());
    jobResult.areaSize = mAreaSize;
    jobResult.pixelPositionY = mPixelPositionY;
    jobResult.moveOffset = mMoveOffset;
    jobResult.scaleFactor = mScaleFactor;

    double imageHalfWidth = mAreaSize.width() / 2.0;
    double imageHalfHeight = mAreaSize.height() / 2.0;
    for (int imageX = 0; imageX < mAreaSize.width(); ++imageX) {
        int iteration = 0;
        double x0 = (imageX - imageHalfWidth) * mScaleFactor + mMoveOffset.x();
        double y0 = (mPixelPositionY - imageHalfHeight) * mScaleFactor - mMoveOffset.y();
        double x = 0.0;
        double y = 0.0;
        do {
            if (mAbort.load()) {
                return;
            }
            double nextX = (x * x) - (y * y) + x0;
            y = 2.0 * x * y + y0;
            x = nextX;
            iteration++;
        } while(iteration < mIterationMax && (x * x) + (y * y) < 4.0);

        jobResult.values[imageX] = iteration;
    }

    emit jobCompleted(jobResult);
}

void Job::abort()
{
    mAbort.store(true);
}

void Job::setPixelPositionY(int value) {
    this->mPixelPositionY = value;
}

void Job::setMoveOffset(const QPointF& value) {
    this->mMoveOffset = value;
}

void Job::setScaleFactor(double value) {
    this->mScaleFactor = value;
}

void Job::setAreaSize(const QSize& value) {
    this->mAreaSize = value;
}

void Job::setIterationMax(int value) {
    this->mIterationMax = value;
}
