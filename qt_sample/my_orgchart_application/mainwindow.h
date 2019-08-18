#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QBrush>
#include <QPen>
#include <QDebug>
#include <QFont>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include <QInputDialog>
#include <QKeyEvent>

class ProfileBox;
class ProfileLine;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateLines();
    void keyReleaseEvent(QKeyEvent* event);

public slots:
    void selectionChanged();

private slots:
    void on_addButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    QList<ProfileLine*> lines;
};

#endif // MAINWINDOW_H
