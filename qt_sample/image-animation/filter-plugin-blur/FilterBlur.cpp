#include "FilterBlur.h"

#include <opencv/cv.h>
#include <opencv/cv.hpp>

#include <QDebug>

FilterBlur::FilterBlur(QObject* parent) :
    QObject(parent)
{
}

FilterBlur::~FilterBlur() {

}

QString FilterBlur::name() const
{
    return "Blur";
}

QImage FilterBlur::process(const QImage& image)
{
    qDebug() << "QImage FilterBlur::process(const QImage& image) " << image;

    // QImage => cv::mat
    cv::Mat tmp(image.height(), image.width(), CV_8UC4, (uchar*)image.bits(), image.bytesPerLine());
    int blur = 25;
    cv::Mat resultMat;
    cv::GaussianBlur(tmp, resultMat, cv::Size(blur, blur), 0.0, 0.0);

    // cv::mat => QImage
    QImage resultImage((const uchar *) resultMat.data, resultMat.cols, resultMat.rows, resultMat.step, QImage::Format_RGB32);

    return resultImage.copy();
}
