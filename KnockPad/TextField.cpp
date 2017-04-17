﻿#include "TextField.h"

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
    cursor_->setCursor(edge_, QFontMetrics(font()).height());
    cursor_->setColorCursor(viewport()->palette().color(QPalette::WindowText));
    cursor_->setColorBase(viewport()->palette().color(QPalette::Base));

    textLines_ = new Text(QFontMetrics(font()).height(), this);
    textLines_->setCurrentFont(&font());

    textBuffer_= new Text(QFontMetrics(font()).height(), this);

    //connect(this, SIGNAL( fontChanged(QFont*) ), textLines_, SLOT( setCurrentFont(QFont*) ) );
    highlightningColor_ = QColor(0xff, 0x66, 0x00);
    this->palette().highlight().color();
    selectionBegin_ = edge_;
    selectionEnd_ = edge_;
    selectionPos_ = QPoint(0, 0);
    setSelected(false);
    curPos_ = QPoint(0, 0);

    setCapsLock(false);

    records_ = new Recorder(this);
    viewport()->update();
}

TextField::~TextField()
{
    delete field_;
    delete cursor_;
    delete textBuffer_;
    delete textLines_;
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
    QWidget::setFont(font);\

    viewport()->update();
}

void TextField::clear()
{
    selectAll();
    QPoint p = _handle_backspace();
    _change_positions(p);
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

    if(event->matches(QKeySequence::Copy))
        copy();
    else if(event->matches(QKeySequence::Cut))
        cut();
    else if(event->matches(QKeySequence::Paste))
        paste();
    else if(event->matches(QKeySequence::SelectAll))
        selectAll();

    else if((event->key() >= 0x20 && event->key() <= 0x7E) ||
            (event->key() >= 0x410 && event->key() <= 0x42f) ||
            (event->key() == 1000021)){
        if(isSelected())
            _erase_highlighted_text();

        QChar in_char = event->text().at(0);

        if((QApplication::keyboardModifiers() == Qt::NoModifier)){
            if(capsLock())
                in_char = in_char.toUpper();
        }
        else if(QApplication::keyboardModifiers() == Qt::ShiftModifier)
                if(capsLock())
                    in_char = in_char.toLower();
        textLines_->insert(curPos_.x(), curPos_.y(), in_char);
        p = textLines_->getShiftByCoord(selectionBegin_, edge_, 1, 0);
    }

    else if(event->key() == Qt::Key_Return)
        p =_handle_enter();
    else if(event->key() == Qt::Key_Backspace)
        p = _handle_backspace();
    else if(event->key() == Qt::Key_CapsLock)
        setCapsLock(capsLock() ? false : true);

    else if(event->matches(QKeySequence::MoveToNextChar))
        p = textLines_->getShiftByCoord(QPoint(x,y), edge_, 1, 0);
    else if(event->matches(QKeySequence::MoveToEndOfLine))
        p = textLines_->getShiftByCoord(QPoint((*textLines_)[curPos_.x()].getWidth() + edge_.x(), y), edge_);
    else if(event->matches(QKeySequence::MoveToPreviousChar))
        p = textLines_->getShiftByCoord(QPoint(x,y), edge_, -1, 0);
    else if(event->matches(QKeySequence::MoveToStartOfLine))
        p = textLines_->getShiftByCoord(QPoint(edge_.x(), y), edge_);
    else if(event->matches(QKeySequence::MoveToNextLine))
        p = textLines_->getShiftByCoord(QPoint(x,y), edge_, 0, 1);
    else if(event->matches(QKeySequence::MoveToPreviousLine))
        p = textLines_->getShiftByCoord(QPoint(x,y), edge_, 0, -1);
    else if(event->matches(QKeySequence::MoveToStartOfDocument))
        p = textLines_->getShiftByCoord(edge_, edge_);
    else if(event->matches(QKeySequence::MoveToEndOfDocument)) {
        p = textLines_->getShiftByCoord(_get_end_document(), edge_);
    }
    if(p != QPoint(x, y))
        _change_positions(p);
}

void TextField::mouseMoveEvent(QMouseEvent * event)
{
    QPoint p = textLines_->getShiftByCoord(QPoint(event->x(),event->y()), edge_);
    Symbol* symb = textLines_->getSymbByCoord(p, edge_);
    if(symb != NULL)
        cursor_->setCursor(p, symb->height());
    curPos_.setX(textLines_->getLineIndex(p.y(), edge_.y()));
    curPos_.setY((*textLines_)[curPos_.x()].getSymbolIndex(p.x(), edge_.x()));
    _set_selection_end(p);
    setSelected(true);
}

void TextField::mousePressEvent(QMouseEvent * event)
{
    QPoint p = textLines_->getShiftByCoord(QPoint(event->x(),event->y()), edge_);
    Symbol* symb = textLines_->getSymbByCoord(p, edge_);
    if(symb != NULL)
        cursor_->setCursor(p, symb->height());
    else
        cursor_->setCursor(p, (*textLines_)[textLines_->getLineIndex(p.x(), p.y())].getHeight());
    curPos_.setX(textLines_->getLineIndex(p.y(), edge_.y()));
    curPos_.setY((*textLines_)[curPos_.x()].getSymbolIndex(p.x(), edge_.x()));
    _set_selection_pos(curPos_);
    _set_selection_begin(p);
    _set_selection_end(p);
}

void TextField::paintEvent(QPaintEvent *)
{
    QPainter painter(viewport());
    cursor_->draw(&painter);
    if(selectionBegin_ != selectionEnd_)
    {
        const QPoint& beginSelect = minPoint(selectionBegin_, selectionEnd_);
        const QPoint& endSelect = maxPoint(selectionBegin_, selectionEnd_);
        _fill_highlightning_rect(painter, beginSelect, endSelect);
    }
    textLines_->draw(&painter, edge_);
}

void TextField::copy()
{
    textLines_->copyPart(textBuffer_,
                minPos(curPos_, selectionPos_),
                maxPos(curPos_, selectionPos_));
}

void TextField::cut()
{

    textLines_->cutPart(textBuffer_,
                minPos(curPos_, selectionPos_),
                maxPos(curPos_, selectionPos_));
    _change_positions(minPoint(selectionBegin_, selectionEnd_));
    _change_positions(minPoint(selectionBegin_, selectionEnd_));
}

void TextField::paste()
{
    int x = 0;
    int y = 0;

    if(isSelected())
        _erase_highlighted_text();
    textLines_->insertPart(textBuffer_, curPos_);
    if(textLines_->length() > 1){
        x = (*textBuffer_)[textBuffer_->length() - 1].getWidth()
                + edge_.x();
        y = textLines_->getHeight(curPos_.x())
                + textBuffer_->getHeight(textBuffer_->length() - 1) + edge_.y();
    }
    else{
        x = (*textLines_)[curPos_.x()].getWidth(curPos_.y())
                + (*textBuffer_)[textBuffer_->length() - 1].getWidth()
                + edge_.x();
        y = textLines_->getHeight(curPos_.x()) + edge_.y();
    }
    _change_positions(QPoint(x, y));
}

void TextField::selectAll()
{
    setSelected(true);
    selectionBegin_ = edge_;
    selectionEnd_ = _get_end_document();
    selectionPos_ = QPoint(0, 0);
    curPos_ = QPoint(textLines_->length() - 1,
                     (*textLines_)[textLines_->length() - 1].length());
}

QPoint TextField::_get_end_document()
{
    Line* lasLine = &(*textLines_)[textLines_->length() - 1];
    return QPoint(lasLine->getWidth() + edge_.x(),
                  textLines_->getHeight() - lasLine->getHeight() + edge_.y());
}

void TextField::_change_positions(QPoint p)
{
    curPos_.setX(textLines_->getLineIndex(p.y(), edge_.y()));
    curPos_.setY( (*textLines_)[curPos_.x()].getSymbolIndex(p.x(), edge_.x()));
    _set_selection_pos(curPos_);
    _set_selection_begin(p);
    _set_selection_end(p);

    Symbol symb = textLines_->getSymbol(curPos_.x(), curPos_.y());
    if(symb.value() == QChar()){
        QFontMetrics metrics(font());
        cursor_->setCursor(p, metrics.height());
    }
    else
        cursor_->setCursor(p, symb.height());
}

QPoint TextField::_handle_backspace()
{
    QPoint p;
    if(isSelected()){
        _erase_highlighted_text();
        p = minPoint(selectionBegin_, selectionEnd_);
    }
    else{
        p = textLines_->getShiftByCoord(minPoint(selectionBegin_, selectionEnd_), edge_, -1, 0);
        textLines_->backspace(curPos_.x(), curPos_.y());
    }
    return p;
}

QPoint TextField::_handle_enter()
{
    if(isSelected())
        _erase_highlighted_text();
    Line line = (*textLines_)[curPos_.x()].getNewLine(curPos_.y());
    textLines_->insert(curPos_.x() + 1, line);
    return QPoint(edge_.x(), selectionBegin_.y() + (*textLines_)[curPos_.x()].getHeight());
}

void TextField::_fill_highlightning_rect(QPainter &painter, const QPoint &begin, const QPoint &end)
{
    int  beginPos = selectionPos_.x() < curPos_.x() ?
                selectionPos_.x() :
                curPos_.x();
    int endPos = selectionPos_.x() > curPos_.x() ?
                selectionPos_.x() :
                curPos_.x();

    QBrush brush = QBrush(highlightningColor_);

    if(beginPos < endPos){
        int xBegin = begin.x();
        int yBegin = begin.y();
        int xEnd = (*textLines_)[beginPos].getWidth() + edge_.x();
        int yEnd = begin.y() + (*textLines_)[beginPos].getHeight();
        painter.fillRect(QRect(begin, QPoint(xEnd + 5, yEnd)),
                         highlightningColor_);

        xBegin = edge_.x();
        int xPos = beginPos + 1;
        for(; xPos < endPos; ++xPos)
        {
            yBegin = yEnd;
            yEnd += (*textLines_)[xPos].getMaxHeight();
            if((*textLines_)[xPos].isEmpty())
            {

                painter.fillRect(QRect(QPoint(xBegin, yBegin),
                                       QPoint(10, yEnd)),
                                 brush);
                continue;
            }
            xEnd = (*textLines_)[xPos].getWidth() + edge_.x();

            painter.fillRect(QRect(QPoint(xBegin, yBegin),
                                   QPoint(xEnd + 5, yEnd)),
                             brush);
        }

        yBegin = yEnd;
        xEnd = end.x();
        yEnd += (*textLines_)[xPos].getMaxHeight();
        painter.fillRect(QRect(QPoint(xBegin, yBegin),
                           QPoint(xEnd, yEnd)),
                           brush);
    }
    else{
        painter.fillRect(QRect(QPoint(begin.x(), begin.y()),
                                QPoint(end.x(), end.y() + (*textLines_)[beginPos].getMaxHeight())),
                         brush);
    }
}

void TextField::_set_selection_begin(QPoint p)
{
    selectionBegin_.setX(p.x());
    selectionBegin_.setY(p.y());
}

void TextField::_set_selection_end(QPoint p)
{
    selectionEnd_.setX(p.x());
    selectionEnd_.setY(p.y());
}

void TextField::_set_selection_pos(QPoint p)
{
    selectionPos_.setX(p.x());
    selectionPos_.setY(p.y());
}

void TextField::_erase_highlighted_text()
{
    textLines_->deleteText(minPos(curPos_, selectionPos_),
                          maxPos(curPos_, selectionPos_));
    _reset_selection();
    setSelected(false);
}

const QPoint& TextField::minPoint(const QPoint &p1, const QPoint &p2) const
{
    if(p1.y() < p2.y() )
        return p1;
    else if(p2.y() < p1.y())
        return p2;
     return p1.x() <= p2.x() ? p1 : p2;
}

const QPoint& TextField::maxPoint(const QPoint &p1, const QPoint &p2) const
{
    if(p1.y() > p2.y() )
        return p1;
    else if(p2.y() > p1.y())
        return p2;
     return p1.x() >= p2.x() ? p1 : p2;
}

const QPoint& TextField::minPos(const QPoint &p1, const QPoint &p2) const
{
    if(p1.x() < p2.x() )
        return p1;
    else if(p2.x() < p1.x())
        return p2;
     return p1.y() <= p2.y() ? p1 : p2;
}

const QPoint& TextField::maxPos(const QPoint &p1, const QPoint &p2) const
{
    if(p1.x() > p2.x() )
        return p1;
    else if(p2.x() > p1.x())
        return p2;
     return p1.y() >= p2.y() ? p1 : p2;
}

void TextField::_reset_selection()
{
    curPos_ = minPos(curPos_, selectionPos_);
    selectionPos_ = minPos(curPos_, selectionPos_);
    selectionBegin_ = minPoint(selectionBegin_, selectionEnd_);
    selectionEnd_ = minPoint(selectionBegin_, selectionEnd_);
}
