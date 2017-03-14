#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QRectF>
#include <QWidget>
#include <QHBoxLayout>
//#include <QWidget>

class TextField : public QWidget
{
    Q_OBJECT

public:
    explicit TextField(QWidget *parent = 0);
    ~TextField();

protected:
    void paintEvent(QPaintEvent *);

private:
    QHBoxLayout layout;
    QPainter *painter;
};

#endif
