#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    manager = new QNetworkAccessManager(this);

    // docker run -d -v /data/my_ftp/:/home/vsftpd -p 20:20 -p 21:21 -p 21100-21110:21100-21110 -e FTP_USER=myuser -e FTP_PASS=mypass -e PASV_ADDRESS=127.0.0.1 -e PASV_MIN_PORT=21100 -e PASV_MAX_PORT=21110 --name vsftpd --restart=always fauria/vsftpd
    ftpAddress = "ftp://127.0.0.1/";
    ftpPort = 21;
    username = "myuser"; // Put your FTP user name here
    password = "mypass"; // Put your FTP user password here

    getFileList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getFileList()
{
    QUrl ftpPath;
    ftpPath.setUrl(ftpAddress + "files.txt");
    ftpPath.setUserName(username);
    ftpPath.setPassword(password);
    ftpPath.setPort(ftpPort);
    QNetworkRequest request;
    request.setUrl(ftpPath);
    downloadFileListReply = manager->get(request);
    connect(downloadFileListReply, &QNetworkReply::finished, this, &MainWindow::downloadFileListFinished);
}

void MainWindow::downloadFileListFinished()
{
    if(downloadFileListReply->error() != QNetworkReply::NoError)
    {
        QMessageBox::warning(this, "Failed", "Failed to load file list: " + downloadFileListReply->errorString());
    }
    else
    {
        QByteArray responseData;
        if (downloadFileListReply->isReadable())
        {
            responseData = downloadFileListReply->readAll();
        }
        // Display file list
        ui->fileList->clear();
        fileList = QString(responseData).split(",");
        if (fileList.size() > 0)
        {
            for (int i = 0; i < fileList.size(); i++)
            {
                if (fileList.at(i) != "")
                {
                    ui->fileList->addItem(fileList.at(i));
                }
            }
        }
    }
}

void MainWindow::on_openButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select File", qApp->applicationDirPath());
    ui->uploadFileInput->setText(fileName);
}

void MainWindow::on_uploadButton_clicked()
{
    QFile* file = new QFile(ui->uploadFileInput->text());
    QFileInfo fileInfo(*file);
    uploadFileName = fileInfo.fileName();
    QUrl ftpPath;
    ftpPath.setUrl(ftpAddress + uploadFileName);
    ftpPath.setUserName(username);
    ftpPath.setPassword(password);
    ftpPath.setPort(ftpPort);
    if (file->open(QIODevice::ReadOnly))
    {
        ui->uploadProgress->setEnabled(true);
        ui->uploadProgress->setValue(0);
        QNetworkRequest request;
        request.setUrl(ftpPath);
        uploadFileReply = manager->put(request, file);
        connect(uploadFileReply, SIGNAL(uploadProgress(qint64,qint64)), this, SLOT(uploadFileProgress(qint64,qint64)));
        connect(uploadFileReply, SIGNAL(finished()), this, SLOT(uploadFileFinished()));
    }
    else
    {
        QMessageBox::warning(this, "Invalid File", "Failed to open file for upload.");
    }
}

void MainWindow::uploadFileProgress(qint64 bytesSent, qint64 bytesTotal)
{
    qint64 percentage = 100 * bytesSent / bytesTotal;
    ui->uploadProgress->setValue((int) percentage);
}

void MainWindow::uploadFileFinished()
{
    if(uploadFileReply->error() != QNetworkReply::NoError)
    {
        QMessageBox::warning(this, "Failed", "Failed to upload file: " + uploadFileReply->errorString());
    }
    else
    {
        // Add new file to file list array if not exist yet
        bool exists = false;
        if (fileList.size() > 0) {
            for (int i = 0; i < fileList.size(); i++) {
                if (fileList.at(i) == uploadFileName) {
                    exists = true;
                }
            }
        }
        if (!exists) {
            fileList.append(uploadFileName);
        }

        // Create new files.txt
        QString fileName = "files.txt";
        QFile* file = new QFile(qApp->applicationDirPath() + "/" + fileName);
        file->open(QIODevice::ReadWrite);
        if (fileList.size() > 0) {
            for (int j = 0; j < fileList.size(); j++) {
                if (fileList.at(j) != "") {
                    file->write(QString(fileList.at(j) + ",").toUtf8());
                }
            }
        }
        file->close();

        // Re-open the file
        QFile* newFile = new QFile(qApp->applicationDirPath() + "/" + fileName);
        if (newFile->open(QIODevice::ReadOnly)) {
            // Update file list to server
            QUrl ftpPath;
            ftpPath.setUrl(ftpAddress + fileName);
            ftpPath.setUserName(username);
            ftpPath.setPassword(password);
            ftpPath.setPort(ftpPort);
            QNetworkRequest request;
            request.setUrl(ftpPath);
            uploadFileListReply = manager->put(request, newFile);
            connect(uploadFileListReply, SIGNAL(finished()), this, SLOT(uploadFileListFinished()));
            file->close();
        }

        QMessageBox::information(this, "Success", "File successfully uploaded.");
    }
}

void MainWindow::uploadFileListFinished()
{
    if(uploadFileListReply->error() != QNetworkReply::NoError) {
        QMessageBox::warning(this, "Failed", "Failed to update file list: " + uploadFileListReply->errorString());
    } else {
        getFileList();
    }
}

void MainWindow::on_setFolderButton_clicked()
{
    QString folder = QFileDialog::getExistingDirectory(this, tr("Open Directory"), qApp->applicationDirPath(),
    QFileDialog::ShowDirsOnly);
    ui->downloadPath->setText(folder);
}

void MainWindow::on_fileList_itemDoubleClicked(QListWidgetItem *item)
{
    downloadFileName = item->text();
    // Check folder
    QString folder = ui->downloadPath->text();
    if (folder != "" && QDir(folder).exists()) {
        QUrl ftpPath;
        ftpPath.setUrl(ftpAddress + downloadFileName);
        ftpPath.setUserName(username);
        ftpPath.setPassword(password);
        ftpPath.setPort(ftpPort);
        QNetworkRequest request;
        request.setUrl(ftpPath);
        downloadFileReply = manager->get(request);
        connect(downloadFileReply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(downloadFileProgress(qint64,qint64)));
        connect(downloadFileReply, SIGNAL(finished()), this, SLOT(downloadFileFinished()));
    } else {
        QMessageBox::warning(this, "Invalid Path", "Please set the download path before download.");
    }
}

void MainWindow::downloadFileProgress(qint64 byteReceived,qint64 bytesTotal)
{
    qint64 percentage = 100 * byteReceived / bytesTotal;
    ui->downloadProgress->setValue((int) percentage);
}

void MainWindow::downloadFileFinished()
{
    if(downloadFileReply->error() != QNetworkReply::NoError) {
        QMessageBox::warning(this, "Failed", "Failed to download file: " + downloadFileReply->errorString());
    } else {
        QByteArray responseData;
        if (downloadFileReply->isReadable()) {
            responseData = downloadFileReply->readAll();
        }
        if (!responseData.isEmpty()) {
            // Download finished
            QString folder = ui->downloadPath->text();
            QFile file(folder + "/" + downloadFileName);
            file.open(QIODevice::WriteOnly);
            file.write((responseData));
            file.close();
            QMessageBox::information(this, "Success", "File successfully downloaded.");
        }
    }
}
