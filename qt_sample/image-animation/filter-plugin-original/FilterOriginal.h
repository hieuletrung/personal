#ifndef FILTERPLUGINORIGINAL_H
#define FILTERPLUGINORIGINAL_H

#include <QObject>
#include <Filter.h>

#include "filter-plugin-original_global.h"
class FilterOriginal : public QObject, Filter
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.myproject.imageanimation.filters.Filter")
    Q_INTERFACES(Filter)

public:
    FilterOriginal(QObject* parent = nullptr);
    ~FilterOriginal();

    QString name() const override;
    QImage process(const QImage& image) override;
};

#endif // FILTERPLUGINORIGINAL_H
