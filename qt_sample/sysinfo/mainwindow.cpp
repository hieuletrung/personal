#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "sysinfo.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mCpuWidget(this),
    mMemoryWidget(this)
{
    ui->setupUi(this);

    SysInfo::instance().init();
    QLayout* layout = ui->centralWidget->layout();
    layout->addWidget(&mCpuWidget);
    layout->addWidget(&mMemoryWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
