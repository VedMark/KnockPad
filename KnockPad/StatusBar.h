#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QLabel>
#include <QStatusBar>
#include <QString>

class StatusBar : public QStatusBar
{
public:
    explicit StatusBar(QWidget *parent = Q_NULLPTR);
    explicit StatusBar(int line, int column, QWidget *parent = Q_NULLPTR);
    ~StatusBar();

public slots:
    void updateStatusBar(int line, int column);

private:
    QLabel *carriagePos;
    QString _pos_info[4];
};

#endif
