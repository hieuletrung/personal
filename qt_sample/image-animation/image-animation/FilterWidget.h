#ifndef FILTERWIDGET_H
#define FILTERWIDGET_H

#include <QWidget>
#include <QImage>

namespace Ui {
class FilterWidget;
}

class Filter;

class FilterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FilterWidget(Filter& filter, QWidget *parent = nullptr);
    ~FilterWidget();

    void process();
    void setSourcePicture(const QImage& sourcePicture);
    void setSourceThumbnail(const QImage& sourceThumbnail);
    void updateThumbnail();
    QString title() const;

signals:
    void pictureProcessed(const QImage& picture);

protected:
    void mousePressEvent(QMouseEvent*) override;

private:
    Ui::FilterWidget *ui;
    Filter& mFilter;
    QImage mDefaultSourcePicture;
    QImage mSourcePicture;
    QImage mSourceThumbnail;
    QImage mFilteredPicture;
    QImage mFilteredThumbnail;
};

#endif // FILTERWIDGET_H
