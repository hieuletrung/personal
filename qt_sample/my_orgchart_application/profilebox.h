#ifndef PROFILEBOX_H
#define PROFILEBOX_H

#include "mainwindow.h"

class ProfileBox : public QGraphicsItemGroup
{
public:
    explicit ProfileBox(QGraphicsItem* parent = nullptr);

    void init(QString name, MainWindow *window, QGraphicsScene* scene);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    MainWindow* mainWindow;
    QGraphicsTextItem* nameTag;
};

#endif // PROFILEBOX_H
