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
    explicit Symbol(QFont font, QChar value = QChar());
    Symbol(const Symbol&);
    Symbol& operator=(const Symbol&);
    ~Symbol();

    inline bool bold() const { return font_.bold(); }
    inline void setBold(bool bold) { font_.setBold(bold); }

    inline QFont font() const { return font_; }
    inline void setFont(QFont font) {
        font_ = font;
        delete fontMetrics_;
        fontMetrics_ = new QFontMetrics(font);
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
    explicit Line(QObject *parent = 0);
    explicit Line(Symbol symbol, QObject *parent = Q_NULLPTR);
    Line(const Line&);
    Line& operator=(const Line&);
    ~Line();

    inline qint64 getHeight() const { return height_; }
    inline qint64 getWidth() const { return width_; }
    inline int length() const { return content_.length(); }
    inline int size() const { return content_.size(); }

    Symbol pop_front();
    Symbol pop_back();
    void push_front(Symbol);
    void push_back(Symbol);
    void insert(int pos, Symbol);
    Symbol erase(int pos);

    int getSymbolBegin(int x, int edgeX, int ind = 0) const;

    // Divides text into two parts after pos and creates new Line;
    Line* setNewLine(qint64 pos, QObject *parent = Q_NULLPTR);

    void draw(QPoint pos, QPainter &device) const;

    Symbol& operator[](int);

signals:
    void heightChanged();
    void widthChanged();

private:
    void raise_height(int);
    void reduce_height(int);

    SymbolList content_;
    int contentSize_;

    qint64 width_;
    qint64 height_;
};


class Text: public QObject
{
    Q_OBJECT

public:
    explicit Text(QObject *parent = Q_NULLPTR);
    explicit Text(int height, QObject *parent = Q_NULLPTR);
    Text(const Text&);
    Text& operator=(const Text&);
    ~Text();

    inline qint64 getHeight() const { return height_; }
    inline int length() const { return content_.length(); }

    Line pop_front();
    Line pop_back();
    void push_front(Line);
    void push_back(Line);
    void insert(int pos, Line);
    Line erase(int pos);

    QPoint getShiftByCoord(QPoint p, QPoint edge, int indX = 0, int indY = 0) const;
    Symbol getSymbByCoord(QPoint point, QPoint edge, int *ind = NULL) const;
    void draw(QPainter *painter, QPoint edge);
    Line& operator[](int);

signals:
    void heightChanged();

private:
    void raise_height(int);
    void reduce_height(int);

    LineList content_;
    int height_;
};

#endif
