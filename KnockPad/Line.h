#ifndef LINE_H
#define LINE_H

#include <QObject>

#include "Phrase.h"

class Line : public QObject
{
    Q_OBJECT

public:
    explicit Line(QObject *parent = 0);
    explicit Line(Phrase *ph, QObject *parent = 0);
    ~Line();

    inline qint64 getHeight() const { return _height; }
    inline qint64 getWidth() const { return _width; }

    Line* setNewLine(qint64 absPos, QObject *parent = Q_NULLPTR);

private:
    PhraseList _content;
    int _contentSize;

    qint64 _width;
    qint64 _height;
};

#endif
