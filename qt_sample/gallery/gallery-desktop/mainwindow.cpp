#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "albummodel.h"
#include "picturemodel.h"
#include "thumbnailproxymodel.h"
#include "gallerywidget.h"
#include "picturewidget.h"

#include <QItemSelectionModel>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mGalleryWidget(new GalleryWidget(this)),
    mPictureWidget(new PictureWidget(this)),
    mStackedWidget(new QStackedWidget(this))
{
    ui->setupUi(this);

    AlbumModel* albumModel = new AlbumModel(this);
    QItemSelectionModel* albumSelectionModel = new QItemSelectionModel(albumModel, this);
    mGalleryWidget->setAlbumModel(albumModel);
    mGalleryWidget->setAlbumSelectionModel(albumSelectionModel);

    PictureModel* pictureModel = new PictureModel(*albumModel, this);
    ThumbnailProxyModel* thumbnailModel = new ThumbnailProxyModel(this);
    thumbnailModel->setSourceModel(pictureModel);

    QItemSelectionModel* pictureSelectionModel = new QItemSelectionModel(thumbnailModel, this);
    mGalleryWidget->setPictureModel(thumbnailModel);
    mGalleryWidget->setPictureSelectionModel(pictureSelectionModel);
    mPictureWidget->setModel(thumbnailModel);
    mPictureWidget->setSelectionModel(pictureSelectionModel);

    connect(mGalleryWidget, &GalleryWidget::pictureActivated, this, &MainWindow::displayPicture);
    connect(mPictureWidget, &PictureWidget::backToGallery, this, &MainWindow::displayGallery);

    mStackedWidget->addWidget(mGalleryWidget);
    mStackedWidget->addWidget(mPictureWidget);
    displayGallery();
    setCentralWidget(mStackedWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::displayGallery()
{
    mStackedWidget->setCurrentWidget(mGalleryWidget);
}
void MainWindow::displayPicture(const QModelIndex& index)
{
    qDebug() << "displayPicture: " << index;
    mStackedWidget->setCurrentWidget(mPictureWidget);
}