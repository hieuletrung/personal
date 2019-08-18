#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mTasks()
{
    ui->setupUi(this);

    connect(ui->addTaskButton, &QPushButton::clicked, this, &MainWindow::addTask);

    updateStatus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addTask() {
    bool ok;
    QString name = QInputDialog::getText(this, tr("Add Task"), tr("Task Name"), QLineEdit::Normal, tr("Untitled Task"), &ok);
    if (ok && !name.isEmpty()) {
        qDebug() << "Add new task!";
        Task* task = new Task(name);
        connect(task, &Task::removed, this, &MainWindow::removeTask);
        connect(task, &Task::statusChanged, this, &MainWindow::taskStatusChanged);

        mTasks.append(task);
        ui->taskLayout->addWidget(task);

        updateStatus();
    }
}

void MainWindow::removeTask(Task *task) {
    mTasks.removeOne(task);
    ui->taskLayout->removeWidget(task);
    task->setParent(nullptr);
    delete task;

    updateStatus();
}

void MainWindow::taskStatusChanged(Task */*task */) {
    updateStatus();
}

void MainWindow::updateStatus() {
    int completeCount = 0;
    for (auto t : mTasks) {
        if (t->isCompleted()) {
            completeCount++;
        }
    }
    int todoCount = mTasks.size() - completeCount;

    ui->statusLabel->setText(QString("Status: %1 todo / %2 completed").arg(todoCount).arg(completeCount));
}
