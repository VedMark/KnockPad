#include "Cursor.h"

Cursor::Cursor(QWidget *holder, QObject *parent)
    : QObject(parent)
{
    rect_.setRect(0, 0, 2, 14);
    blink_ = true;
    holder_ = holder;

    connect(&timer_, SIGNAL( timeout() ), SLOT( updateCursor() ) );

    timer_.setInterval(500);
    timer_.start();
}

Cursor::~Cursor()
{
}

void Cursor::setCursor(QPoint pos, int h)
{
    blink_ = false;
    holder_->update();

    setWidth(h);
    setHeigth(h);

    rect_.setRect(pos.x(), pos.y(), rect_.width(), rect_.height());

    blink_ = true;
    holder_->update();

    emit currentAddressChanged(this->cursorPosition());
}

QPoint Cursor::cursorPosition() const
{
    return QPoint(rect_.x(), rect_.y());
}

void Cursor::setWidth(int CharHeight)
{
    rect_.setWidth(static_cast<int>(log(CharHeight ) / log(16)) + 1);
}

void Cursor::draw(QPainter *painter)
{
    if(blink_)
        painter->fillRect(rect_, colorCursor_);
    else
        painter->fillRect(rect_, colorBase_);
}

void Cursor::updateCursor()
{
    blink_ = !blink_;
    holder_->update();
}
