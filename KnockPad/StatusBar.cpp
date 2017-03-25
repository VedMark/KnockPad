#include "StatusBar.h"

StatusBar::StatusBar(QWidget *parent)
    : QStatusBar(parent)
{
    _pos_info[0] = "Line ";
    _pos_info[2] = ", Column ";
    this->carriagePos = new QLabel(this);
    updateStatusBar(1,1);
    carriagePos->setAlignment(Qt::AlignHCenter);
    carriagePos->setMinimumSize(carriagePos->sizeHint());
}

StatusBar::StatusBar(int line, int column, QWidget *parent)
    : QStatusBar(parent)
{
    QString _pos_info[4];
    _pos_info[0] = "Line ";
    _pos_info[2] = ", Column ";
    this->carriagePos = new QLabel(this);
    updateStatusBar(line, column);
}

StatusBar::~StatusBar()
{
    delete carriagePos;
}

void StatusBar::updateStatusBar(int line, int column)
{
    _pos_info[1] = QString::number(line);
    _pos_info[3] = QString::number(column);
    this->carriagePos->setText(_pos_info[0] + _pos_info[1] + _pos_info[2] + _pos_info[3]);
}
