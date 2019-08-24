#include "filteroriginal.h"

#include <QImage>

FilterOriginal::FilterOriginal() : Filter()
{
}

FilterOriginal::~FilterOriginal()
{
}

QImage FilterOriginal::process(const QImage& image)
{
    return image;
}
