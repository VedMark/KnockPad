#include "TextField.h"

TextField::TextField(QWidget *parent)
    : QWidget(parent)
{
    this->painter = new QPainter(this);
    this->setGeometry(100, 100, 200, 200);
    this->setVisible(true);
    this->show();
    setCursor(Qt::IBeamCursor);
}

TextField::~TextField()
{
}

void TextField::paintEvent(QPaintEvent * paintEvent)
{
    QSize sz = size();
    sz.width();
    sz.height();
    QBrush brush(Qt::white);
    painter->setBrush( brush );
}

