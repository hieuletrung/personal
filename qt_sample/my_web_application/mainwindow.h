#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QWebEngineProfile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);

private slots:
    void on_backButton_clicked();

    void on_forwardButton_clicked();

    void on_refreshButton_clicked();

    void on_goButton_clicked();

    void on_addressInput_returnPressed();

    void webviewLoading(int progress);
    void webviewLoaded(bool );

private:
    Ui::MainWindow *ui;
    QWebEngineView* webview;

    void loadPage();
};

#endif // MAINWINDOW_H
