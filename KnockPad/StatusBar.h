#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QLabel>
#include <QSizePolicy>
#include <QStatusBar>
#include <QString>

class StatusBar : public QStatusBar
{
    Q_OBJECT

public:
    explicit StatusBar(QWidget *parent = Q_NULLPTR);
    explicit StatusBar(int line, int column, QWidget *parent = Q_NULLPTR);
    ~StatusBar();

public slots:
    void updateStatusBar(QPoint);

private:
    QLabel *carriagePos;
    QString _pos_info[4];
};

#endif
