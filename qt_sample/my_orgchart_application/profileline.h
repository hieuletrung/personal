#ifndef PROFILELINE_H
#define PROFILELINE_H

#include <QWidget>
#include <QGraphicsItem>
#include <QPen>

class ProfileLine : public QGraphicsLineItem
{
public:
    ProfileLine(QGraphicsItem* parent = nullptr);
    void initLine(QGraphicsItem* start, QGraphicsItem* end);
    void updateLine();

    QGraphicsItem* startBox;
    QGraphicsItem* endBox;

private:
};
#endif // PROFILELINE_H
