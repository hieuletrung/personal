#ifndef FILTERPLUGINGRAYSCALE_H
#define FILTERPLUGINGRAYSCALE_H

#include <QObject>
#include <Filter.h>

#include "filter-plugin-grayscale_global.h"

class FilterGrayscale : public QObject, Filter
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.myproject.imageanimation.filters.Filter")
    Q_INTERFACES(Filter)

public:
    FilterGrayscale(QObject* parent = nullptr);
    ~FilterGrayscale();

    QString name() const override;
    QImage process(const QImage& image) override;
};

#endif // FILTERPLUGINGRAYSCALE_H
