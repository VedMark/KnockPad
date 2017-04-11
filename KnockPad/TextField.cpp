#include "TextField.h"

TextField::TextField(QWidget *parent)
    : QAbstractScrollArea(parent)
{
    field_ = new QWidget(this);
    setViewport(field_);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    edge_ = QPoint(5, 5);

    setFont(QFont(QString("Monospace"), 14));

    cursor_ = new Cursor(viewport(), this);
    cursor_->setEdge(edge_);
    cursor_->setWidth(pxCharWidth_);
    cursor_->setHeigth(pxCharHeight_);
    cursor_->setColorCursor(viewport()->palette().color(QPalette::WindowText));
    cursor_->setColorBase(viewport()->palette().color(QPalette::Base));

    textLines_ = Text(23, this);
    textLines_.push_back(Line(textLines_));
    curLineInd_ = 0;
    curSymbInd_ = 0;
    wasCTRLpressed = false;
//    Line l = Line(Symbol(QChar('h')), this->parent());
//    l.push_back(Symbol(QChar('e')));
//    l.push_back(Symbol(QChar('l')));
//    l.push_back(Symbol(QChar('l')));
//    l.push_back(Symbol(QChar('o')));
//    textLines_.push_front(l);

    records_ = new Recorder(this);
    viewport()->update();
}

TextField::~TextField()
{
}

//View public actions

void TextField::setTextEditorView(Qt::GlobalColor color)
{
    QPalette pal = QPalette(field_->palette());
    pal.setBrush(backgroundRole(), QBrush(color));
    field_->setPalette(pal);
    field_->setAutoFillBackground(true);

    field_->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    field_->setCursor(Qt::IBeamCursor);
}

void TextField::setFont(const QFont &font)
{
    QWidget::setFont(font);
    pxCharWidth_ = fontMetrics().width(QChar('W'));
    pxCharHeight_ = fontMetrics().height();

    viewport()->update();
}

void TextField::clear()
{

}

bool TextField::readFile(const QString &fileName)
{
    return true;
}

bool TextField::writeFile(const QString &fileName)
{
    return true;
}

// Events

void TextField::keyPressEvent(QKeyEvent *event)
{
    int x = cursor_->x();
    int y = cursor_->y();
    QPoint p = QPoint(x, y);

    switch(event->key())
    {
    case Qt::Key_Up:{
        p = textLines_.getShiftByCoord(QPoint(x,y), edge_, 0, -1);
        textLines_.getSymbByCoord(p, edge_, &curSymbInd_);
        break;
    }
    case Qt::Key_Down:{
        p = textLines_.getShiftByCoord(QPoint(x,y), edge_, 0, 1);
        textLines_.getSymbByCoord(p, edge_, &curSymbInd_);
        break;
    }
    case Qt::Key_Right:{
        p = textLines_.getShiftByCoord(QPoint(x,y), edge_, 1, 0);
        textLines_.getSymbByCoord(p, edge_, &curSymbInd_);
        break;
    }
    case Qt::Key_Left:{
        p = textLines_.getShiftByCoord(QPoint(x,y), edge_, -1, 0);
        textLines_.getSymbByCoord(p, edge_, &curSymbInd_);
        break;
    }
    case Qt::Key_Control:{
        wasCTRLpressed = true;
        break;
    case Qt::Key_Enter:{
//            Line* line = textLines_[curLineInd_++].setNewLine(curSymbInd_, textLines_);
//            textLines_.insert(curLineInd_, line);
//            curSymbInd_ = 0;
        }
    }
    default:
        wasCTRLpressed = false;
        if(event->key() >= 0x40 && event->key() <=0x5a)
            textLines_[curLineInd_].insert(curSymbInd_++, QChar(event->key() + 32));
        p = textLines_.getShiftByCoord(QPoint(x,y), edge_, 1, 0);
        break;
    }

    Symbol symb = textLines_.getSymbByCoord(p, edge_);
    cursor_->setCursorPosition(p, symb.width(), symb.height());
}

void TextField::mouseMoveEvent(QMouseEvent * event)
{
    QPoint p = textLines_.getShiftByCoord(QPoint(event->x(),event->y()), edge_);
    Symbol symb = textLines_.getSymbByCoord(p, edge_, &curSymbInd_);
    cursor_->setCursorPosition(p, symb.width(), symb.height());
}

void TextField::mousePressEvent(QMouseEvent * event)
{
    QPoint p = textLines_.getShiftByCoord(QPoint(event->x(),event->y()), edge_);
    Symbol symb = textLines_.getSymbByCoord(p, edge_, &curSymbInd_);
    cursor_->setCursorPosition(p, symb.width(), symb.height());
}

void TextField::paintEvent(QPaintEvent *event)
{
    QPainter painter(viewport());
    cursor_->draw(&painter);

    textLines_.draw(&painter, edge_);
}

void TextField::resetSelection()
{
    _bSelectionBegin = _bSelectionInit;
    _bSelectionEnd = _bSelectionInit;
}

void TextField::resetSelection(qint64 pos)
{
    pos /= 2;
    if(pos < 0)
        pos = 0;
    if(pos > records_->size())
        pos = records_->size();

    _bSelectionInit = pos;
    _bSelectionBegin = pos;
    _bSelectionEnd = pos;
}

void TextField::setSelection(qint64 pos)
{
    pos /= 2;
    if(pos < 0)
        pos = 0;
    if(pos > records_->size())
        pos = records_->size();

    if(pos >= _bSelectionInit)
    {
        _bSelectionBegin = _bSelectionInit;
        _bSelectionEnd = pos;
    }
    else
    {
        _bSelectionBegin = pos;
        _bSelectionEnd = _bSelectionInit;
    }
}

int TextField::getSelectionBegin() const
{
    return _bSelectionBegin;
}

int TextField::getSelectionEnd() const
{
    return _bSelectionEnd;
}
