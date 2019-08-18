#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QPushButton>

class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = nullptr);
private:
    QPushButton *m_button;

signals:

public slots:
};

#endif // WINDOW_H
