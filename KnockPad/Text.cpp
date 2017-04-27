#include "Text.h"

//              Symbol class implementation

Symbol::Symbol()
{
    font_ = QFont(QString("Monospace"), 14);
    font_.setBold(false);
    font_.setItalic(false);
    fontMetrics_ = new QFontMetrics(font_);
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
}

Line::Line(int height, QObject *parent)
    : QObject(parent)
{
    width_ = 0;
    height_ = height;
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

qint64 Line::getWidth(int pos) const
{
    int width = 0;
    for(int i = 0; i < pos && i < content_.size(); ++i)
        width += content_[i].width();
    return width;
}

qint64 Line::getMaxHeight() const
{
    qint64 max = 0;
    if(isEmpty())
        return height_;
    foreach (Symbol symb, content_) {
        if(symb.height() > max)
            max = symb.height();
    }
    return max;
}

Symbol Line::pop_front()
{
    Symbol symb = content_.first();
    content_.pop_front();
    width_ -= symb.width();
    reduce_height(symb.height());

    return symb;
}

Symbol Line::pop_back()
{
    Symbol symb = content_.last();
    content_.pop_back();
    width_ -= symb.width();
    reduce_height(symb.height());

    return symb;
}

void Line::push_front(const Symbol& symb)
{
    content_.push_front(symb);
    width_ += symb.width();
    raise_height(symb.height());

}

void Line::push_back(const Symbol& symb)
{
    content_.push_back(symb);
    width_ += symb.width();
    raise_height(symb.height());

}

void Line::insert(int pos, const Symbol& symb)
{
    content_.insert(content_.begin() + pos, symb);
    width_ += symb.width();
    raise_height(symb.height());
}

Symbol Line::erase(int pos)
{
    Symbol symb = content_[pos];
    width_ -= symb.width();
    reduce_height(symb.height());

    content_.erase(content_.begin() + pos);
    return symb;
}

int Line::getSymbolIndex(int pos, int edgeX) const
{
    qint64 shift = edgeX;
    int i = 0;
    while(shift < pos && shift < width_)
    {
        shift += content_[i++].width();
    }
    return i;
}

int Line::getSymbolBegin(int x, int edgeX, int ind) const
{
    qint64 shift = edgeX;
    int i = 0;
    if(x >= width_)
        shift = width_ + edgeX;
    else if(x <= edgeX)
        shift = edgeX;
    else
    {
        while(shift < width_)
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
    else if(ind == 1){
        if(x >= width_);
        else
            shift += content_.at(i).width();
    }
    return shift;

}

Line Line::getNewLine(int pos)
{
    if(content_.isEmpty())
        return Line(height_, parent());
    int count = content_.size() - pos;
    qint64 height = content_[pos ? count : count - 1].height();
    Line newLine = Line(height, parent());

    while(count--)
        newLine.push_back(erase(pos));

    return newLine;
}

void Line::raise_height(int h)
{
    if(h > height_)
        height_ = h;
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
    height_ = 0;
    curFieldFont_ = NULL;
}

Text::Text(int h, QObject *parent)
    : QObject(parent)
{
    Line line = Line(h, this);
    height_ = 0;
    insert(0, line);
    curFieldFont_ = NULL;
}

Text::Text(const Text& text) :
    QObject(text.parent())
{
    setParent(text.parent());
    content_ = text.content_;
    height_ = text.height_;
    curFieldFont_ = text.curFieldFont_;
}

Text::~Text()
{
}

Text& Text::operator=(const Text& text)
{
    setParent(text.parent());
    content_ = text.content_;
    height_ = text.height_;
    curFieldFont_ = text.curFieldFont_;
    return *this;
}

Line& Text::operator[](int pos)
{
    return content_[pos];
}

Line Text::erase(int pos)
{
    reduce_height(content_[pos].getHeight());
    Line line = content_[pos];
    content_.erase(content_.begin() + pos);
    return line;
}

void Text::insert(int pos, const Line& line)
{
    content_.insert(content_.begin() + pos, line);
    raise_height(line.getMaxHeight());
}

void Text::insert(int posX, int posY, const Symbol &symb)
{
    content_[posX].insert(posY, symb);
    int h = symb.height() - content_[posX].getHeight();
    if(h > 0)
        raise_height(h);
}

Line& Text::pop_front()
{
    Line& line = content_.first();
    content_.pop_front();
    reduce_height(line.getHeight());
    return line;
}

Line& Text::pop_back()
{
    Line& line = content_.last();
    content_.pop_back();
    reduce_height(line.getHeight());
    return line;
}

void Text::push_front(const Line &line)
{
    content_.push_front(line);
    raise_height(line.getHeight());
}

void Text::push_back(const Line &line)
{
    content_.push_back(line);
    raise_height(line.getHeight());
}

Symbol Text::getSymbol(int i, int j)
{
    if(i < 0) i = 0;
    else if(i >= content_.length()) i = content_.length() - 1;
    if(content_[i].isEmpty())
        return Symbol();
    if(j < 0) j = 0;
    else if(j >= content_[i].length()) j = content_[i].length() - 1;

    return content_[i][j];
}

void Text::eraseSymbol(int x, int y)
{
    if(!y && x){
        for(int i = 0; i < content_[x].length(); ++i)
            content_[x - 1].push_back(content_[x][i]);
        reduce_height(content_[x].getHeight());
        content_.erase(content_.begin() + x);
        }
    else if(y)
        content_[x].erase(y - 1);
}

qint64 Text::getHeight(int index) const
{
    qint64 y = 0;
    LineList::const_iterator it = content_.begin();
    for(; it != content_.begin() + index; ++ it)
        y += it->getHeight();
    return y;
}

void Text::deleteText(const QPoint &begin, const QPoint &end)
{
    if(begin.x() < end.x())
    {
        int i = begin.x();
        content_[i].getNewLine(begin.y());
        for(i++; i < end.x(); ++i){
            erase(begin.x() + 1);
        }
        for(int j = 0; j < end.y(); ++j)
            content_[begin.x() + 1].erase(0);

        while(content_[begin.x() + 1].length())
            content_[begin.x()].push_back(content_[begin.x() + 1].erase(0));
        erase(begin.x() + 1);
    }
    else
    {
        for(int j = begin.y(); j < end.y(); ++j)
            content_[begin.x()].erase(begin.y());
    }
}

int Text::getLineIndex(int pos, int edgeY) const
{
    int shift = edgeY;
    int i = 0;
    while(shift < pos && shift < height_)
    {
        shift += content_[i++].getHeight();
    }
    return i;
}

QPoint Text::getShiftByCoord(QPoint point, QPoint edge, int indX, int indY) const
{
    qint64 shiftY = edge.y();
    qint64 shiftX = edge.x();
    qint64 i = 0;
    if(point.y() >=  edge.y() + height_)
    {
        shiftX = edge.x() + content_.last().getWidth();
        shiftY = edge.y() + height_ - content_.last().getHeight();
    }
    else
    {
        if(point.y() <= edge.y())
            shiftY = edge.y();
        else
            while(shiftY < height_)
            {
                if(shiftY + content_.at(i).getHeight() > point.y())
                    break;
                    shiftY += content_.at(i++).getHeight();
            }
        if(indY == -1){
            if(point.y() <= edge.y());
            else
                shiftY -= content_.at(i).getHeight();
        }
        else if(indY == 1){
            if(point.y() >= height_ - content_.last().getHeight() + edge.y());
            else
                shiftY += content_.at(i).getHeight();
        }

        if((i == content_.length() - 1 && indY == 1) || (!i && indY == -1))
            shiftX = content_.at(i).getSymbolBegin(point.x(), edge.x(), indX);
        else if(indX == -1 && point.x() == edge.x()){
                if(i){
                    shiftX = content_.at(i - 1).getWidth() + edge.x();
                    shiftY -= content_.at(i - 1).getHeight();
                }
            }
            else if (indX == 1
                     && point.x() == content_.at(i).getWidth() + edge.x()
                     && i!= content_.length() - 1){
                shiftX = edge.x();
                shiftY += content_.at(i).getHeight();
            }
        else
            shiftX = content_.at(i + indY).getSymbolBegin(point.x(), edge.x(), indX);
    }
    return QPoint(shiftX, shiftY);
}

Symbol* Text::getSymbByCoord(QPoint point, QPoint edge)
{
    qint64 shiftX = edge.x();
    qint64 shiftY = edge.y();
    qint64 i = 0;
    qint64 j = 0;

    Line line(this);
    while(shiftY < point.y())
        shiftY += content_.at(i++).getHeight();

    line = content_.at(i);
    while(shiftX < point.x())
        shiftX += line[j++].width();

    if(j == line.size() && line.size()) j--;
    if(line.isEmpty())
        return NULL;
    return &line[j];
}

void Text::draw(QPainter *painter, QPoint edge)
{
    qint64 x = edge.x();
    qint64 y = edge.y();
    for(int i = 0; i < content_.length(); ++i){
        for(int j = 0; j < content_[i].length(); ++j){
            painter->drawText(x,
                      content_[i].getHeight() * 0.9 + y,
                      content_[i][j].value());
            x += content_[i][j].width();
        }
        x = edge.x();
        y += content_[i].getHeight();
    }
}

void Text::copyPart(Text* res, QPoint beginPos, QPoint endPos)
{
    if(beginPos.x() > endPos.x())
        return;

    if(res != Q_NULLPTR)
        delete res;

    res = new Text(parent());
    Line line(this);
    if(beginPos.x() < endPos.x())
    {
        if(content_[beginPos.x()].isEmpty() && beginPos.x() < endPos.x())
            res->push_back(Line(content_[beginPos.x()].getHeight(), this));
        else{
            for(int j = beginPos.y(); j < content_[beginPos.x()].size(); ++j)
                line.push_back(Symbol(content_[beginPos.x()][j]));
            res->push_back(line);
        }

        for(int i = beginPos.x() + 1; i < endPos.x(); ++i)
            res->push_back(Line(content_[i]));

        line = Line(this);
        for(int j = 0; j < endPos.y(); ++j)
            line.push_back(Symbol(content_[endPos.x()][j]));
        if(!line.isEmpty())
            res->push_back(line);
    }
    else if(beginPos.x() == endPos.x()){
        for(int j = beginPos.y(); j < endPos.y(); ++j)
            line.push_back(Symbol(content_[beginPos.x()][beginPos.y()]));
        res->push_back(line);
    }
}

void Text::cutPart(Text* res, QPoint beginPos, QPoint endPos)
{
    if(beginPos.x() > endPos.x())
        return;

    if(res != Q_NULLPTR)
        delete res;

    res = new Text(parent());
    Line line(this);
    if(beginPos.x() < endPos.x())
    {
        int secondPos = beginPos.x() + 1;
        res->push_back(content_[beginPos.x()].getNewLine(beginPos.y()));

        for(int i = secondPos; i < endPos.x(); ++i)
            res->push_back(erase(secondPos));

        line = Line(this);
        for(int j = 0; j < endPos.y(); ++j)
            line.push_back(content_[secondPos].erase(0));
        if(!line.isEmpty())
            res->push_back(line);

        for(int j = 0; j < content_[secondPos].size(); ++j)
            content_[beginPos.x()].push_back(content_[secondPos][j]);
        erase(secondPos);
    }
    else if(beginPos.x() == endPos.x()){
        for(int j = beginPos.y(); j < endPos.y(); ++j)
            line.push_back(content_[beginPos.x()].erase(beginPos.y()));
        res->push_back(line);
    }
}
void Text::insertPart(Text* source, QPoint pos)
{
    Line line = content_[pos.x()].getNewLine(pos.y());
    for(int j = 0; j < (*source)[0].length(); ++j)
        content_[pos.x()].push_back(Symbol((*source)[0][j]));

    for(int j = 1; j < source->length(); ++j)
        insert(pos.x() + j, Line((*source)[j]));

    for(int j = 0; j < line.length(); ++j)
        content_[pos.x() + source->length() - 1].push_back(Symbol(line[j]));
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
