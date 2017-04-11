#include "Text.h"

//              Symbol class implementation

Symbol::Symbol()
{
    font_ = QFont(QString("Monospace"), 14);
    font_.setBold(false);
    font_.setItalic(false);
    fontMetrics_ = new QFontMetrics(font_);
    value_ = QChar(0x00);
}

Symbol::Symbol(QChar value)
{
    font_ = QFont(QString("Monospace"), 14);
    font_.setBold(false);
    font_.setItalic(false);
    fontMetrics_ = new QFontMetrics(font_);
    value_ = QChar(value);
}

Symbol::Symbol(QFont font, QChar value)
{
    font_ = QFont(font);
    fontMetrics_ = new QFontMetrics(font_);
    value_ = QChar(value);
}

Symbol::Symbol(const Symbol& symbol)
{
    font_ = symbol.font_;
    fontMetrics_ = symbol.fontMetrics_;
    value_ = symbol.value_;
}

Symbol& Symbol::operator=(const Symbol& symbol)
{
    font_ = symbol.font_;
    fontMetrics_ = symbol.fontMetrics_;
    value_ = symbol.value_;
    return *this;
}

Symbol::~Symbol()
{
}

//              Line class implementation

Line::Line(QObject *parent)
    : QObject(parent)
{
    width_ = 0;
    height_ = 0;
    content_.push_back(Symbol());
}

Line::Line(Symbol symbol, QObject *parent)
    : QObject(parent)
{
    content_.push_back(symbol);

    width_ = symbol.width();
    height_ = symbol.height();
}

Line::Line(const Line& line) :
    QObject(line.parent())
{
    content_ = line.content_;
    width_ = line.width_;
    height_ = line.height_;
}

Line& Line::operator=(const Line& line)
{
    setParent(line.parent());
    content_ = line.content_;
    width_ = line.width_;
    height_ = line.height_;
    return *this;
}

Line::~Line()
{
}

Symbol& Line::operator[](int pos)
{
    return content_[pos];
}

Symbol Line::pop_front()
{
    Symbol symb = content_.first();
    content_.pop_front();
    width_ -= symb.width();
    reduce_height(symb.height());
    emit widthChanged();
    return symb;
}

Symbol Line::pop_back()
{
    Symbol symb = content_.last();
    content_.pop_back();
    width_ -= symb.width();
    reduce_height(symb.height());
    emit widthChanged();
    return symb;
}

void Line::push_front(Symbol symb)
{
    content_.push_front(symb);
    width_ += symb.width();
    raise_height(symb.height());
    emit widthChanged();
}

void Line::push_back(Symbol symb)
{
    content_.push_back(symb);
    width_ += symb.width();
    raise_height(symb.height());
    emit widthChanged();
}

void Line::insert(int pos, Symbol symb)
{
    content_.insert(content_.begin() + pos, symb);
    width_ += symb.width();
    raise_height(symb.height());
    emit widthChanged();
}

Symbol Line::erase(int pos)
{
    Symbol symb = content_[pos];
    width_ -= symb.width();
    reduce_height(symb.height());
    emit widthChanged();
    return *content_.erase(content_.begin() + pos);
}

int Line::getSymbolBegin(int x, int edgeX, int ind) const
{
    int shift = edgeX;
    int i = 0;
    if(x >= width_)
        shift = width_ + edgeX;
    else if(x < edgeX)
        shift = edgeX;
    else
    {
        while(shift <= width_)
        {
            if(shift + content_.at(i).width() / 2 >= x)
                break;
            shift += content_.at(i).width();
        }
    }

    if(ind == -1)
        if(x <= edgeX);
        else
            shift -= content_.at(i).width();
    else if(ind == 1)
        if(x >= width_);
        else
            shift += content_.at(i).width();

    return shift;
}

Line* Line::setNewLine(qint64 pos, QObject *parent)
{
    Line *newLine = new Line(parent);
    for(int i = pos; i < content_.size(); ++i)
    {
        newLine->push_back(erase(pos));
    }
    return newLine;
}

void Line::draw(QPoint pos, QPainter &device) const
{
    foreach(Symbol symbol, content_)
    {
        device.drawText(pos, symbol.value());
    }
}

// Private functions
void Line::raise_height(int h)
{
    if(h > height_)
    {
        height_ = h;
        emit heightChanged();
    }
}

void Line::reduce_height(int h)
{
    if(h == height_)
    {
        int heighest = 0;
        foreach(Symbol symb, content_)
        {
            if(symb.height() > heighest)
                heighest = symb.height();
        }
        if(heighest < height_)
        {
            height_ = heighest;
            emit heightChanged();
        }
    }
}

//              Text class implementation

Text::Text(QObject *parent)
    : QObject(parent)
{
    content_.push_back(Line(parent));
    height_ = 23;
}

Text::Text(int height, QObject *parent)
    : QObject(parent)
{
    content_.push_back(Line(parent));
    height_ = height;
}

Text::Text(const Text& text) :
    QObject(text.parent())
{
    setParent(text.parent());
    content_ = text.content_;
    height_ = text.height_;
}

Text& Text::operator=(const Text& text)
{
    setParent(text.parent());
    content_ = text.content_;
    height_ = text.height_;
    return *this;
}

Text::~Text()
{
}

Line& Text::operator[](int pos)
{
    return content_[pos];
}

Line Text::pop_front()
{
    Line line = content_.first();
    content_.pop_front();
    reduce_height(line.getHeight());
    return line;
}

Line Text::pop_back()
{
    Line line = content_.last();
    content_.pop_back();
    reduce_height(line.getHeight());
    return line;
}

void Text::push_front(Line line)
{
    content_.push_front(line);
    raise_height(line.getHeight());
}

void Text::push_back(Line line)
{
    content_.push_back(line);
    raise_height(line.getHeight());
}

void Text::insert(int pos, Line line)
{
    content_.insert(content_.begin() + pos, line);
    raise_height(line.getHeight());
}

Line Text::erase(int pos)
{
    Line line = content_[pos];
    reduce_height(line.getHeight());
    return *content_.erase(content_.begin() + pos);
}

QPoint Text::getShiftByCoord(QPoint point, QPoint edge, int indX, int indY) const
{
    int shiftY = edge.y();
    int shiftX = edge.x();
    int i = 0;
    int cont_height = content_.at(content_.length() - 1).getHeight();
    if(point.y() >  edge.y() + height_)
    {
        shiftX = content_.at(i).getWidth();
        shiftY = edge.y() + height_ - cont_height;
    }
    else
    {
        if(point.y() < edge.y())
            shiftY = edge.y();
        else
        {
            while(shiftY <= height_)
            {
                if(shiftY + content_.at(i).getHeight() >= point.y())
                    break;
                    shiftY += content_.at(i++).getHeight();
            }
        }
        if(indY == -1)
            if(point.y() <= edge.y());
            else
                shiftY -= content_.at(i).getHeight();
        else if(indY == 1)
            if(point.y() > height_ - content_.last().getHeight());
            else
                shiftY += content_.at(i).getHeight();

        shiftX = content_.at(i).getSymbolBegin(point.x(), edge.x(), indX);
    }
    return QPoint(shiftX, shiftY);
}

Symbol Text::getSymbByCoord(QPoint point, QPoint edge, int *ind) const
{
    int shiftX = edge.x();
    int shiftY = edge.y();
    int i = 0;
    int j = 0;

    Line line;
    while(shiftY < point.y())
        shiftY += content_.at(i++).getHeight();

    line = content_.at(i);
    while(shiftX < point.x())
        shiftX += line[j++].width();

    if(j == line.size() && line.size()) j--;
    if(ind) *ind = j;
    return line[j];
}

void Text::draw(QPainter *painter, QPoint edge)
{
    int x = edge.x();
    int y = edge.y();
    for(int i = 0; i < content_.length(); ++i){
        for(int j = 0; j < content_[i].length(); ++j){
            painter->drawText(x,
                      content_[i].getHeight() * 0.9 + y,
                      content_[i][j].value());
            x += content_[i][j].width();
        }
        y += content_[i].getHeight();
    }
}

void Text::raise_height(int h)
{
    height_ += h;
    emit heightChanged();
}

void Text::reduce_height(int h)
{
    height_ -= h;
    emit heightChanged();
}
