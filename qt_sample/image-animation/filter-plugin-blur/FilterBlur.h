#ifndef FILTERPLUGINBLUR_H
#define FILTERPLUGINBLUR_H

#include <QObject>
#include <Filter.h>

#include "filter-plugin-blur_global.h"

class FilterBlur : public QObject, Filter
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.myproject.imageanimation.filters.Filter")
    Q_INTERFACES(Filter)

public:
    FilterBlur(QObject* parent = nullptr);
    ~FilterBlur();

    QString name() const override;
    QImage process(const QImage& image) override;
};

#endif // FILTERPLUGINBLUR_H
