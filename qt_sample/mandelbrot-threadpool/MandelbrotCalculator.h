#ifndef MANDELBROTCALCULATOR_H
#define MANDELBROTCALCULATOR_H


#include <QObject>
#include <QSize>
#include <QPointF>
#include <QElapsedTimer>
#include <QList>

#include "JobResult.h"

class Job;

class MandelbrotCalculator : public QObject
{
    Q_OBJECT
public:
    explicit MandelbrotCalculator(QObject *parent = nullptr);
    void init(QSize imageSize);

signals:
    void pictureLinesGenerated(QList<JobResult> jobResults);
    void abortAllJobs();

public slots:
    void generatePicture(QSize areaSize, QPointF moveOffset, double scaleFactor, int iterationMax);
    void process(JobResult jobResult);

private:
    Job* createJob(int pixelPositionY);
    void clearJobs();

private:
    QPointF mMoveOffset;
    double mScaleFactor;
    QSize mAreaSize;
    int mIterationMax;
    /**
     * @brief count of the JobResult received, which was sent by the jobs.
     */
    int mReceivedJobResults;
    /**
     * @brief list that contains received JobResult.
     */
    QList<JobResult> mJobResults;
    /**
     * @brief calculates the elapsed time to run all jobs for a requested picture.
     */
    QElapsedTimer mTimer;
};

#endif // MANDELBROTCALCULATOR_H
