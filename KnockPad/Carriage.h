#ifndef CARRIAGE_H
#define CARRIAGE_H

#include <QObject>


class Carriage: public QObject
{
    Q_OBJECT

public:
    Carriage(QObject *parent = Q_NULLPTR);

private:
    qint64 x;
    qint64 y;
};

#endif
