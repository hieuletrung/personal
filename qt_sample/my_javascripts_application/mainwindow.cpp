#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    webview = new QWebEngineView(ui->webviewFrame);
    webview->load(QUrl("qrc:/html/test.html"));

    QWebChannel* channel = new QWebChannel(this);
    channel->registerObject("mainwindow", this);
    webview->page()->setWebChannel(channel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);
    webview->resize(ui->webviewFrame->size());
}

void MainWindow::on_pushButton_clicked()
{
    webview->page()->runJavaScript("hello();");
}

void MainWindow::doSomething()
{
    ui->label->setText("This text has been changed by javascript!");
}
