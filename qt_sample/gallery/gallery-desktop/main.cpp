#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    qSetMessagePattern("[%{time yyyy-MM-dd hh:mm:ss}] [%{type}] %{function} %{message}");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
