#ifndef WORKERWIDGET_H
#define WORKERWIDGET_H

#include <QWidget>
#include <QThread>
#include <QProgressBar>
#include <QTimer>

#include "Worker.h"

namespace Ui {
class WorkerWidget;
}

class WorkerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WorkerWidget(QWidget *parent = nullptr);
    ~WorkerWidget();

private:
    QProgressBar mStatus;
    Worker mWorker;
    QThread mWorkerThread;
    QTimer mRefreshTimer;
};

#endif // WORKERWIDGET_H
