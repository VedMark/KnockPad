#include "TextField.h"

TextField::TextField(QWidget *parent)
    : QAbstractScrollArea(parent)
{
    field = new QWidget(this);
    this->setViewport(this->field);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    _addressArea = true;
    _addressWidth = 4;
    _overwriteMode = true;
    _highlighting = true;
    _cursorPosition = 0;
    _hexCaps = false;
    _dynamicBytesPerLine = false;

    setFont(QFont(QString("Monospace"), 100));

    _pxHorEdge = 5;
    _pxVertEdge = 5;

    _cursorRect.setRect(5, 5, _pxCursorWidth, _pxCharHeight);

    _records = new Recorder(this);

    _hexDataShown = QByteArray("Hello, World! Дратуй, мир!");

    connect(&_cursorTimer, SIGNAL( timeout() ), this, SLOT( updateCursor() ) );

    _cursorTimer.setInterval(500);
    _cursorTimer.start();
}

TextField::~TextField()
{
}

 //Properties

void TextField::setHexCaps(const bool isCaps)
{
    if(_hexCaps != isCaps)
    {
        _hexCaps = isCaps;
        viewport()->update();
    }
}

bool TextField::hexCaps() const
{
    return _hexCaps;
}


//View public actions

void TextField::setTextEditorView(Qt::GlobalColor color)
{
    QPalette pal = QPalette(field->palette());
    pal.setBrush(backgroundRole(), QBrush(color));
    field->setPalette(pal);
    field->setAutoFillBackground(true);

    field->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    field->setCursor(Qt::IBeamCursor);
}

void TextField::setFont(const QFont &font)
{
    QWidget::setFont(font);
    _pxCharWidth = fontMetrics().width(QChar('1'));
    _pxCharWidth = fontMetrics().width(QChar('w'));
    _pxCharHeight = fontMetrics().height();

    _pxCursorWidth = static_cast<int>(log(_pxCharWidth) / log(4)) + 1;

    viewport()->update();
}

void TextField::clear()
{

}

bool TextField::readFile(const QString &fileName)
{

}

bool TextField::writeFile(const QString &fileName)
{

}

void TextField::setCursorPosition(QPoint position)
{
    _blink = false;
    viewport()->update(_cursorRect);

    _cursorRect.setX((position.x() / _pxCharWidth) * _pxCharWidth + 5);
    _cursorRect.setY((position.y() / _pxCharHeight) * _pxCharHeight + 5);

    _blink = true;
    viewport()->update(_cursorRect);
    emit currentAddressChanged(_bPosCurrent);
}

QPoint TextField::cursorPosition() const
{
    QPoint(_cursorRect.x(), _cursorRect.y());
}

// Events

void TextField::keyPressEvent(QKeyEvent *event)
{
    int x = _cursorRect.x();
    int y = _cursorRect.y();

    QPoint top = geometry().topLeft();
    QPoint bottom = geometry().bottomRight();

    _blink = false;
    viewport()->update();

    switch(event->key())
    {
        case Qt::Key_Up:
        {
            if(y >= _pxCharHeight)
                y -= _pxCharHeight;
            break;
        }
        case Qt::Key_Down:
        {
            if(y < bottom.y() - _pxCharHeight - 10)
                y += _pxCharHeight;
            break;
        }

        case Qt::Key_Right:
        {
            if(x < bottom.x() - _pxCharWidth - 5)
                x += _pxCharWidth;
            break;
        }
        case Qt::Key_Left:
        {
            if(x >= _pxCharWidth)
                x -= _pxCharWidth;
            break;
        }
    }

    setCursorPosition(QPoint(x, y));
}

void TextField::mouseMoveEvent(QMouseEvent * event)
{
    qDebug() << "mouseMoveEvent";
    _blink = false;
    viewport()->update();

    setCursorPosition(event->pos());
}

void TextField::mousePressEvent(QMouseEvent * event)
{
    qDebug() <<"mousePressEvent";
    _blink = false;
    viewport()->update();

    setCursorPosition(event->pos());
}

void TextField::paintEvent(QPaintEvent *event)
{
    QPainter painter(viewport());
    int shiftX = horizontalScrollBar()->value();
    int shiftY = horizontalScrollBar()->value();

    if(_blink)
        painter.fillRect( QRect(_cursorRect.x() - shiftX, _cursorRect.y() - shiftY, _pxCursorWidth, _pxCharHeight),
                          palette().color(QPalette::WindowText) );
    else
        painter.fillRect( QRect(_cursorRect.x() - shiftX, _cursorRect.y() - shiftY, _pxCursorWidth, _pxCharHeight),
                          viewport()->palette().color(QPalette::Base) );

    painter.drawText(5, 5 + _pxCharHeight * 0.9, _hexDataShown.mid(_cursorPosition - _bPosFirst));
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
    if(pos > _records->size())
        pos = _records->size();

    _bSelectionInit = pos;
    _bSelectionBegin = pos;
    _bSelectionEnd = pos;
}

void TextField::setSelection(qint64 pos)
{
    pos /= 2;
    if(pos < 0)
        pos = 0;
    if(pos > _records->size())
        pos = _records->size();

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

// Private slots

void TextField::updateCursor()
{
    _blink = !_blink;
    viewport()->update();
}
