#ifndef LINE_H
#define LINE_H

#include <QChar>
#include <QFont>
#include <QFontMetrics>
#include <QObject>
#include <QPainter>
#include <QPoint>
#include <QWidget>
#include <QtGlobal>
#include <QtCore>

class Symbol;
class Line;
class Text;

typedef QList<Symbol> SymbolList;
typedef QList<Line> LineList;

class Symbol
{
public:
    Symbol();
    Symbol(QChar value);
    explicit Symbol(QFont font);
    explicit Symbol(const QFont& font, QChar value);
    Symbol(const Symbol&);
    Symbol& operator=(const Symbol&);
    ~Symbol();

    inline bool bold() const { return font_.bold(); }
    inline void setBold(bool bold) { font_.setBold(bold); }

    inline const QFont& font() const { return font_; }
    inline void setFont(const QFont& font) {
        font_ = QFont(font);
        delete fontMetrics_;
        fontMetrics_ = new QFontMetrics(font_);
    }

    inline bool italic() const { return font_.italic(); }
    inline void setItalic(bool italic) { font_.setItalic(italic); }

    inline qint64 height() const { return fontMetrics_->height(); }
    inline qint64 width() const { return fontMetrics_->width(value_); }

    inline QChar value() const { return value_; }
    inline void setValue(QChar value) { value_ = value; }

private:
    QFont font_;
    QFontMetrics *fontMetrics_;

    QChar value_;
};

class Line : public QObject
{
    Q_OBJECT

public:
    explicit Line(QObject *parent = Q_NULLPTR);
    explicit Line(int height, QObject *parent = Q_NULLPTR);
    Line(const Line&);
    Line& operator=(const Line&);
    ~Line();

    inline int height() const { return height_; }
    qint64 getMaxHeight() const;
    void setHeight(qint64 height) {
        if(height > height_)
            height_ = height;
    }
    inline int getWidth() const { return width_; }
    inline int length() const { return content_.length(); }
    inline int size() const { return content_.size(); }

    inline bool isEmpty() const { return !content_.size(); }

    Symbol pop_front();
    Symbol pop_back();
    void push_front(const Symbol&);
    void push_back(const Symbol&);
    void insert(int pos, const Symbol&);
    Symbol erase(int pos);

    int getSymbolIndex(int pos, int edgeX) const;
    qint64 getSymbShift(int s) const;
    int getSymbolBegin(int x, QPoint &pos) const;
    inline int getDifference(int s) const;
    // Divides text into two parts after pos and creates new Line;
    Line getNewLine(int pos);

    Symbol& operator[](int);
    const Symbol& at(int) const;

signals:
    void heightChanged();
    void widthChanged();

private:
    void raise_height(int);
    void reduce_height(int);

    SymbolList content_;

    qint64 width_;
    qint64 height_;
    qint64 maxHeight_;
};


class Text: public QObject
{
    Q_OBJECT

public:
    explicit Text(QObject *parent = Q_NULLPTR);
    explicit Text(int h, QObject *parent = Q_NULLPTR);
    Text(const Text&);
    ~Text();

    Text& operator=(const Text&);
    Line& operator[](int);

    inline qint64 getHeight() const { return height_; }
    qint64 getHeight(int index) const;

    inline int length() const { return content_.length(); }

    inline QFont* getCurrentFont() const { return curFieldFont_; }
    inline void setCurrentFont(const QFont* font){
        curFieldFont_ = const_cast<QFont*>(font);
    }

    int getLineIndex(int pos, int edgeY) const;
    int getLineShift(int l, int s) const;
    int getLineRoof(int l) const;

    Line erase(int pos);
    void insert(int pos, const Line &);
    void insert(int posX, int posY, const Symbol &);
    Line &pop_front();
    Line &pop_back();
    void push_front( const Line &);
    void push_back( const Line &);

    Symbol getSymbol(int i, int j);
    void eraseSymbol(int x, int y, QPoint &pos);
    void deleteText(const QPoint& begin,const QPoint& end);

    QPoint getShiftByCoord(QPoint p, QPoint &pos) const;
    QPoint getShiftByPos(int x, int y, QPoint &pos) const;
    void draw(QPainter *painter, QPoint edge);

    void copyPart(Text* res, QPoint beginPos, QPoint endPos);
    void cutPart(Text* res, QPoint beginPos, QPoint endPos);
    void insertPart(Text* source, QPoint &pos);

    void reduce_height(int);

signals:
    void heightChanged();

private:
    void raise_height(int);

    LineList content_;
    qint64 height_;

    QFont* curFieldFont_;
};

#endif
