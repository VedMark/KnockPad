#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include <QKeyEvent>
#include <QPainter>
#include <QPalette>
#include <QScrollArea>
#include <QScrollBar>
#include <QString>
#include <QTimer>
#include <QWidget>

#include "Recorder.h"
#include "Line.h"
#include "Phrase.h"

class TextField : public QAbstractScrollArea
{
    Q_OBJECT

public:
    explicit TextField(QWidget *parent = Q_NULLPTR);
    ~TextField();

    void setTextEditorView(Qt::GlobalColor color);
    void setFont(const QFont &font);
    void clear();

    bool readFile(const QString &fileName);
    bool writeFile(const QString &fileName);


    // Properties

    void setHexCaps(const bool isCaps);
    bool hexCaps() const;

    //Cursor functions
    void setCursorPosition(QPoint position);
    QPoint cursorPosition() const;

public slots:


signals:
    void currentAddressChanged(qint64 address);
    void currentSizeChanged(qint64 size);


protected:
    void keyPressEvent(QKeyEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

private:
    void resetSelection();
    void resetSelection(qint64 pos);
    void setSelection(qint64 pos);
    int getSelectionBegin() const;
    int getSelectionEnd() const;

private slots:
    //Cursor functions
    void updateCursor();


private:
    QWidget *field;    

    int _pxCharHeight;
    int _pxCharWidth;
    int _pxCursorWidth;
    int _pxHorEdge;
    int _pxVertEdge;

    int _pxPosHexX;
    int _pxSelectionSub;


    qint64 _bSelectionBegin;
    qint64 _bSelectionEnd;
    qint64 _bSelectionInit;
    qint64 _bPosCurrent;
    qint64 _bPosFirst;

    qint64 _addressOffset;
    bool _addressArea;
    QColor _addressAreaColor;
    QBrush _brushHighlighted;
    QBrush _brushSelection;
    int _bytesPerLine;
    bool _hexCaps;
    int _hexCharsInLine;
    bool _highlighting;
    bool _overwriteMode;
    QPen _penHighlighted;
    QPen _penSelection;
    Recorder *_records;

    //Cursor vars
    int _addressWidth;
    int _addrDigits;
    bool _blink;
    qint64 _cursorPosition;
    QTimer _cursorTimer;
    QRect _cursorRect;
    QByteArray _dataShown;
    QByteArray _hexDataShown;
    qint64 _lastEventSize;
    QByteArray _markedShown;
    int _rowsShown;
    bool _dynamicBytesPerLine;
};

#endif
