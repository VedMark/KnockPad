#include "StatusBar.h"

StatusBar::StatusBar(QWidget *parent)
    : QStatusBar(parent)
{
    _pos_info[0] = "Line ";
    _pos_info[2] = ", Column ";
    this->carriagePos = new QLabel(this);
    updateStatusBar(QPoint(0, 0));
    carriagePos->setAlignment(Qt::AlignLeft);
    carriagePos->setMinimumSize(carriagePos->sizeHint());
}

StatusBar::StatusBar(int line, int column, QWidget *parent)
    : QStatusBar(parent)
{
    QString _pos_info[4];
    _pos_info[0] = "Line ";
    _pos_info[2] = ", Column ";
    this->carriagePos = new QLabel(this);
    updateStatusBar(QPoint(line, column));
}

StatusBar::~StatusBar()
{
}

void StatusBar::updateStatusBar(QPoint pos)
{
    _pos_info[1] = QString::number(pos.x() + 1);
    _pos_info[3] = QString::number(pos.y() + 1);
    this->carriagePos->setText(_pos_info[0] + _pos_info[1] + _pos_info[2] + _pos_info[3]);
    carriagePos->setMinimumSize(carriagePos->sizeHint());
}
