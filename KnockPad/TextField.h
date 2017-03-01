#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>

class TextField : public QGraphicsView
{
    Q_OBJECT

public:
    explicit TextField(QWidget *parent = 0, qreal left = 0, qreal top = 0, qreal width = 800, qreal height = 600);

private:
    QGraphicsScene scene;
    QGraphicsView view;
};

#endif
