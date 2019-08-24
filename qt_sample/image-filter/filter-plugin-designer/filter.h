#ifndef FILTER_H
#define FILTER_H

class QImage;

class Filter
{
public:
    Filter();
    virtual ~Filter();
    virtual QImage process(const QImage& image) = 0;
};

#endif // FILTER_H
