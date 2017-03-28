#include "Line.h"

Line::Line(QObject *parent)
    : QObject(parent)
{
    _content = new Phrases[1];
    _content[0] = new Phrase();
    _contentSize = 1;

    _width = 0;
    _height = _content[0]->height();
}

Line::Line(Phrase *ph, QObject *parent)
    : QObject(parent)
{
    _content = new Phrases[1];
    _content[0] = ph;
    _contentSize = 1;

    _width = ph->length();
    _height = ph->height();
}

Line::~Line()
{
    delete[] _content;
}

Line* Line::setNewLine(qint64 absPos, QObject *parent)
{
    qint64 relPos = 0;
    int i = 0;
    for(; i < _contentSize; ++i)
    {
        if(_content[i]->beginID() >= absPos)
        {
            relPos = absPos - _content[i]->beginID();
            break;
        }
    }
    return new Line(_content[i]->pop(relPos), parent);
}
