#include "Recorder.h"
#include <limits.h>

Recorder::Recorder(QObject *parent):
    QObject(parent)
{
    QBuffer *buf = new QBuffer(this);
    setIODevice(*buf);
}

Recorder::Recorder(QIODevice &ioDevice, QObject *parent):
    QObject(parent)
{
    setIODevice(ioDevice);
}

bool Recorder::setIODevice(QIODevice &ioDevice)
{
    _ioDevice = &ioDevice;
    bool ok = _ioDevice->open(QIODevice::ReadOnly);
    if (ok)
    {
        _size = _ioDevice->size();
        _ioDevice->close();
    }
    else
    {
        QBuffer *buf = new QBuffer(this);
        _ioDevice = buf;
        _size = 0;
    }
    _records.clear();
    _pos = 0;
    return ok;
}

QByteArray Recorder::getData(qint64 pos, qint64 maxSize, QByteArray *highlighted)
{
    qint64 ioDelta = 0;
    int recordIdx = 0;

    Record record;
    QByteArray buffer;

    if (highlighted)
        highlighted->clear();

    if (pos >= _size)
        return buffer;

    if (maxSize < 0)
        maxSize = _size;
    else
        if ((pos + maxSize) > _size)
            maxSize = _size - pos;

    _ioDevice->open(QIODevice::ReadOnly);

    while (maxSize > 0)
    {
        record.absPos = LLONG_MAX;
        bool RecorderLoopOngoing = true;
        while ((recordIdx < _records.count()) && RecorderLoopOngoing)
        {
            record = _records[recordIdx];
            if (record.absPos > pos)
                RecorderLoopOngoing = false;
            else
            {
                recordIdx += 1;
                qint64 count;
                qint64 recordOfs = pos - record.absPos;
                if (maxSize > ((qint64)record.data.size() - recordOfs))
                {
                    count = (qint64)record.data.size() - recordOfs;
                    ioDelta += 0x1000 - record.data.size();
                }
                else
                    count = maxSize;
                if (count > 0)
                {
                    buffer += record.data.mid(recordOfs, (int)count);
                    maxSize -= count;
                    pos += count;
                    if (highlighted)
                        *highlighted += record.dataChanged.mid(recordOfs, (int)count);
                }
            }
        }

        if ((maxSize > 0) && (pos < record.absPos))
        {
            qint64 byteCount;
            QByteArray readBuffer;
            if ((record.absPos - pos) > maxSize)
                byteCount = maxSize;
            else
                byteCount = record.absPos - pos;

            maxSize -= byteCount;
            _ioDevice->seek(pos + ioDelta);
            readBuffer = _ioDevice->read(byteCount);
            buffer += readBuffer;
            if (highlighted)
                *highlighted += QByteArray(readBuffer.size(), 0);
            pos += readBuffer.size();
        }
    }
    _ioDevice->close();
    return buffer;
}

bool Recorder::write(QIODevice &iODevice, qint64 pos, qint64 count)
{
    if (count == -1)
        count = _size;
    bool ok = iODevice.open(QIODevice::WriteOnly);
    if (ok)
    {
        for (qint64 idx=pos; idx < count; idx += 0x10000)
        {
            QByteArray ba = getData(idx, 0x10000);
            iODevice.write(ba);
        }
        iODevice.close();
    }
    return ok;
}

void Recorder::setDataChanged(qint64 pos, bool dataChanged)
{
    if ((pos < 0) || (pos >= _size))
        return;
    int recordIdx = getRecordIndex(pos);
    qint64 posInBa = pos - _records[recordIdx].absPos;
    _records[recordIdx].dataChanged[(int)posInBa] = char(dataChanged);
}

bool Recorder::dataChanged(qint64 pos)
{
    QByteArray highlighted;
    getData(pos, 1, &highlighted);
    return bool(highlighted.at(0));
}

qint64 Recorder::indexOf(const QByteArray &ba, qint64 from)
{
    qint64 result = -1;
    QByteArray buffer;

    for (qint64 pos=from; (pos < _size) && (result < 0); pos += 0x10000)
    {
        buffer = getData(pos, 0x10000 + ba.size() - 1);
        int findPos = buffer.indexOf(ba);
        if (findPos >= 0)
            result = pos + (qint64)findPos;
    }
    return result;
}

qint64 Recorder::lastIndexOf(const QByteArray &ba, qint64 from)
{
    qint64 result = -1;
    QByteArray buffer;

    for (qint64 pos=from; (pos > 0) && (result < 0); pos -= 0x10000)
    {
        qint64 sPos = pos - 0x10000 - (qint64)ba.size() + 1;
        if (sPos < 0)
            sPos = 0;
        buffer = getData(sPos, pos - sPos);
        int findPos = buffer.lastIndexOf(ba);
        if (findPos >= 0)
            result = sPos + (qint64)findPos;
    }
    return result;
}

bool Recorder::insert(qint64 pos, char b)
{
    if ((pos < 0) || (pos > _size))
        return false;
    int recordIdx;
    if (pos == _size)
        recordIdx = getRecordIndex(pos-1);
    else
        recordIdx = getRecordIndex(pos);
    qint64 posInBa = pos - _records[recordIdx].absPos;
    _records[recordIdx].data.insert(posInBa, b);
    _records[recordIdx].dataChanged.insert(posInBa, char(1));
    for (int idx=recordIdx+1; idx < _records.size(); idx++)
        _records[idx].absPos += 1;
    _size += 1;
    _pos = pos;
    return true;
}

bool Recorder::overwrite(qint64 pos, char b)
{
    if ((pos < 0) || (pos >= _size))
        return false;
    int recordIdx = getRecordIndex(pos);
    qint64 posInBa = pos - _records[recordIdx].absPos;
    _records[recordIdx].data[(int)posInBa] = b;
    _records[recordIdx].dataChanged[(int)posInBa] = char(1);
    _pos = pos;
    return true;
}

bool Recorder::removeAt(qint64 pos)
{
    if ((pos < 0) || (pos >= _size))
        return false;
    int recordIdx = getRecordIndex(pos);
    qint64 posInBa = pos - _records[recordIdx].absPos;
    _records[recordIdx].data.remove(posInBa, 1);
    _records[recordIdx].dataChanged.remove(posInBa, 1);
    for (int idx=recordIdx+1; idx < _records.size(); idx++)
        _records[idx].absPos -= 1;
    _size -= 1;
    _pos = pos;
    return true;
}

char Recorder::operator[](qint64 pos)
{
    return getData(pos, 1)[0];
}

qint64 Recorder::pos()
{
    return _pos;
}

qint64 Recorder::size()
{
    return _size;
}

int Recorder::getRecordIndex(qint64 absPos)
{
    int foundIdx = -1;
    int insertIdx = 0;
    qint64 ioDelta = 0;


    for (int idx = 0; idx < _records.size(); idx++)
    {
        Record record = _records[idx];
        if ((absPos >= record.absPos) && (absPos < (record.absPos + record.data.size())))
        {
            foundIdx = idx;
            break;
        }
        if (absPos < record.absPos)
        {
            insertIdx = idx;
            break;
        }
        ioDelta += record.data.size() - 0x1000;
        insertIdx = idx + 1;
    }

    if (foundIdx == -1)
    {
        Record newRecord;
        qint64 readAbsPos = absPos - ioDelta;
        qint64 readPos = (readAbsPos & Q_INT64_C(0xfffffffffffff000));
        _ioDevice->open(QIODevice::ReadOnly);
        _ioDevice->seek(readPos);
        newRecord.data = _ioDevice->read(0x1000);
        _ioDevice->close();
        newRecord.absPos = absPos - (readAbsPos - readPos);
        newRecord.dataChanged = QByteArray(newRecord.data.size(), char(0));
        _records.insert(insertIdx, newRecord);
        foundIdx = insertIdx;
    }
    return foundIdx;
}
