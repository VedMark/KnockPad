#include "Phrase.h"

Phrase::Phrase()
{
    _text = new QByteArray("");

    _font = QFont(QString("Monospace"), 14);
    _font.setBold(false);
    _font.setItalic(false);

    _fontMetrics = new QFontMetrics(_font);

    _beginID = 0;
}

Phrase::Phrase(QByteArray *text, QFont font, qint64 beginID)
{
    _text = text;

    _font = font;
    _font.setBold(font.bold());
    _font.setItalic(font.italic());

    _beginID = beginID;
}

Phrase::~Phrase()
{
    delete _text;
}

Phrase* Phrase::pop(qint64 pos)
{
    return new Phrase(new QByteArray(_text->remove(pos, _text->size() - pos)), _font, 0);
}
