#include "FilterWidget.h"
#include "ui_FilterWidget.h"

#include "Filter.h"

FilterWidget::FilterWidget(Filter &filter, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FilterWidget),
    mFilter(filter),
    mDefaultSourcePicture(":/lenna.jpg"),
    mSourcePicture(mDefaultSourcePicture),
    mSourceThumbnail(mDefaultSourcePicture.scaled(QSize(256, 256), Qt::KeepAspectRatio, Qt::SmoothTransformation)),
    mFilteredPicture(),
    mFilteredThumbnail()
{
    ui->setupUi(this);
    ui->titleLabel->setText(filter.name());

    updateThumbnail();
}

FilterWidget::~FilterWidget()
{
    delete ui;
}

void FilterWidget::process()
{
    mFilteredPicture = mFilter.process(mSourcePicture);
    emit pictureProcessed(mFilteredPicture);
}

void FilterWidget::setSourcePicture(const QImage&sourcePicture)
{
    mSourcePicture = sourcePicture;
}

void FilterWidget::setSourceThumbnail(const QImage&sourceThumbnail)
{
    mSourceThumbnail = sourceThumbnail;
}

void FilterWidget::updateThumbnail() {
    mFilteredThumbnail = mFilter.process(mSourceThumbnail);
    QPixmap pixmap = QPixmap::fromImage(mFilteredThumbnail);
    ui->thumbnailLabel->setPixmap(pixmap);
}

QString FilterWidget::title() const
{
    return this->mFilter.name();
}

void FilterWidget::mousePressEvent(QMouseEvent*)
{
    process();
}
