#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_connectButton_clicked();
    void on_sendButton_clicked();
    void socketConnected();
    void socketDisconnected();
    void socketReadyRead();

private:
    Ui::MainWindow *ui;
    bool connectedToHost;
    QTcpSocket* socket;

    void printMessage(QString message);
};

#endif // MAINWINDOW_H
