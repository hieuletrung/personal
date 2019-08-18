#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    webview = new QWebEngineView(ui->webviewFrame);
    webview->load(QUrl("qrc:/html/test.html"));

    connect(webview, SIGNAL(loadProgress(int)), this, SLOT(webviewLoading(int)));
    connect(webview, SIGNAL(loadFinished(bool)), this, SLOT(webviewLoaded(bool)));

    // Cookies
//    Then, simply call the following function to force persistent cookies:
//    QWebEngineProfile::defaultProfile()->setPersistentCookiesPolicy(QWebEngineProfile::ForcePersistentCookies);
//    After calling the preceding function, your login session will continue to exist after closing
//    the program. To revert it to non-persistent cookies, we simply call:
//    QWebEngineProfile::defaultProfile()->setPersistentCookiesPolicy(QWebEngineProfile::NoPersistentCookies);
//    Other than that, you can also change the directory in which your Qt program stores the
//    cookies. To do that, add the following code to your source file:
//    QWebEngineProfile::defaultProfile()->setPersistentStoragePath("your folder");
//    If, for some reason, you want to manually delete all the cookies, use the following code:
//    QWebEngineProfile::defaultProfile()->cookieStore()->deleteAllCookies();

    // Cache
//    By default, the web engine module saves all the cache to the disk, if you need to change
//    them to Memory Cache, call the following function:
//    QWebEngineProfile::defaultProfile()->setHttpCacheType(QWebEngineProfile::MemoryHttpCache);
//    Alternatively, you can also disable caching completely by calling:
//    QWebEngineProfile::defaultProfile()->setHttpCacheType(QWebEngineProfile::NoCache);
//    As for changing the folder to which your program saves the cache files, call the
//    setCachePath() function:
//    QWebEngineProfile::defaultProfile()->setCachePath("your folder");
//    Lastly, to delete all the cache files, call clearHttpCache():
//    QWebEngineProfile::defaultProfile()->clearHttpCache();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_backButton_clicked()
{
    webview->back();
}

void MainWindow::on_forwardButton_clicked()
{
    webview->forward();
}

void MainWindow::on_refreshButton_clicked()
{
    webview->reload();
}

void MainWindow::on_goButton_clicked()
{
    loadPage();
}

void MainWindow::loadPage()
{
    QString url = ui->addressInput->text();
    if (!url.startsWith("http://") && !url.startsWith("https://")) {
        url = "http://" + url;
    }

    ui->addressInput->setText(url);
    webview->load(QUrl(url));
}

void MainWindow::on_addressInput_returnPressed()
{
    loadPage();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);
    webview->resize(ui->webviewFrame->size());
}

void MainWindow::webviewLoading(int progress)
{
    ui->progressBar->setValue(progress);
}

void MainWindow::webviewLoaded(bool )
{
    ui->addressInput->setText(webview->url().toString());
}
