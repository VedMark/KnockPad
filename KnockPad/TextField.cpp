#include "TextField.h"

TextField::TextField(QWidget *parent, qreal left, qreal top, qreal width, qreal height)
    : QGraphicsView(parent),
    scene(QRectF(left, top, width, height)),
    view(&scene)
{
    setCursor(Qt::IBeamCursor);
}

