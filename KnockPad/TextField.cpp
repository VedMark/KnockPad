#include "TextField.h"

TextField::TextField(QWidget *parent)
    : QWidget(parent)
{}

TextField::~TextField()
{
}

void TextField::setView(Qt::GlobalColor color)
{
    QPalette pal = QPalette(this->palette());
    pal.setBrush(backgroundRole(), QBrush(color));
    this->setPalette(pal);
    this->setAutoFillBackground(true);

    this->setCursor(Qt::IBeamCursor);
}
