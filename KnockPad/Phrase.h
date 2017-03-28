#ifndef PHRASE_H
#define PHRASE_H

#include <QByteArray>
#include <QFont>
#include <QFontMetrics>
#include <QWidget>

class Phrase;
typedef Phrase* Phrases;
typedef Phrases* PhraseList;

class Phrase
{
public:
    explicit Phrase();
    explicit Phrase(QByteArray *text, QFont font, qint64 beginID);
    ~Phrase();

    inline bool bold() const { return _font.bold(); }
    inline void setBold(bool bold) { _font.setBold(bold); }

    inline bool italic() const { return _font.italic(); }
    inline void setItalic(bool italic) { _font.setItalic(italic); }

    inline QFont font() const { return _font; }
    inline void setFont(QFont font) { _font = font; }

    inline qint64 size() const { return _text->size(); }

    inline qint64 height() const { return _fontMetrics->height(); }
    inline qint64 length() const { return _fontMetrics->width(QString(_fontMetrics->height())); }

    inline int charLength(qint64 index) const
        { return _fontMetrics->width(QChar(_text->at(index))); }

    inline qint64 beginID() const { return _beginID; }
    inline void setBeginID(qint64 ID) { _beginID = ID; }
    inline void changeID(qint64 shift) { _beginID += shift; }

    inline QByteArray* getText() const { return _text; }

    inline void push(QString str) { _text->append(str); }

    // Creates Phrase object with _text of this starting from pos to the end
    Phrase* pop(qint64 pos);

private:
    QByteArray *_text;
    QFontMetrics *_fontMetrics;
    QFont _font;

    qint64 _beginID;
};

#endif
