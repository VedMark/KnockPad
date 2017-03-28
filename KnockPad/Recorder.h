#ifndef CARRIAGE_H
#define CARRIAGE_H

#include <QtCore>

struct Record
{
    QByteArray data;
    QByteArray dataChanged;
    qint64 absPos;
};


class Recorder: public QObject
{
    Q_OBJECT

public:
    Recorder(QObject *parent = Q_NULLPTR);
    Recorder(QIODevice &ioDevice, QObject *parent = Q_NULLPTR);
    bool setIODevice(QIODevice &ioDevice);

    QByteArray getData(qint64 pos = 0, qint64 count = -1, QByteArray *highlighted = 0);
    bool write(QIODevice &iODevice, qint64 pos = 0, qint64 count = -1);

    void setDataChanged(qint64 pos, bool dataChanged);
    bool dataChanged(qint64 pos);

    qint64 indexOf(const QByteArray &ba, qint64 from);
    qint64 lastIndexOf(const QByteArray &ba, qint64 from);

    bool insert(qint64 pos, char b);
    bool overwrite(qint64 pos, char b);
    bool removeAt(qint64 pos);

    char operator[](qint64 pos);
    qint64 pos();
    qint64 size();

private:
    int getRecordIndex(qint64 absPos);

    QIODevice * _ioDevice;
    qint64 _pos;
    qint64 _size;
    QList<Record> _records;
};

#endif
