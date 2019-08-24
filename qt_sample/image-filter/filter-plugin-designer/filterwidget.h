#ifndef FILTERWIDGET_H
#define FILTERWIDGET_H

#include <QWidget>
#include <memory>

#include "filter-plugin-global.h"

#include "filter.h"

namespace Ui {
class FilterWidget;
}

class FILTERPLUGINDESIGNERSHARED_EXPORT FilterWidget : public QWidget
{
    Q_OBJECT
    Q_ENUMS(FilterType)
    Q_PROPERTY(QString title READ title WRITE setTitle)
    Q_PROPERTY(FilterType filterType READ filterType WRITE setFilterType)

public:
    enum FilterType { Original, Blur, Grayscale };

    explicit FilterWidget(QWidget *parent = nullptr);
    ~FilterWidget();

    void process();
    void setSourcePicture(const QImage&sourcePicture);
    void updateThumbnail(const QImage&sourceThumbnail);
    QString title() const;
    FilterType filterType() const;

public slots:
    void setTitle(const QString& tile);
    void setFilterType(FilterType filterType);

signals:
    void pictureProcessed(const QImage& picture);

protected:
    void mousePressEvent(QMouseEvent*) override;

private:
    Ui::FilterWidget *ui;
    std::unique_ptr<Filter> mFilter;
    FilterType mFilterType;
    QImage mDefaultSourcePicture;
    QImage mSourcePicture;
    QImage mSourceThumbnail;
    QImage mFilteredPicture;
    QImage mFilteredThumbnail;
};

#endif // FILTERWIDGET_H
