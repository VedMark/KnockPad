#include "TextField.h"

TextField::TextField(QWidget *parent)
    : QScrollArea(parent)
{
    field = new QWidget(this);
    this->setViewport(this->field);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

TextField::~TextField()
{
    delete field;
}

void TextField::setTextEditorView(Qt::GlobalColor color)
{
    QPalette pal = QPalette(field->palette());
    pal.setBrush(backgroundRole(), QBrush(color));
    field->setPalette(pal);
    field->setAutoFillBackground(true);

    field->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    field->setCursor(Qt::IBeamCursor);
}

void TextField::clear()
{

}

bool TextField::readFile(const QString &fileName)
{

}

bool TextField::writeFile(const QString &fileName)
{

}
