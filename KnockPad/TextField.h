#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include <QKeyEvent>
#include <QPainter>
#include <QPalette>
#include <QString>
#include <QTimer>
#include <QWidget>

#include "Recorder.h"
#include "Text.h"
#include "Cursor.h"


class TextField : public QAbstractScrollArea
{
    Q_OBJECT

public:
    explicit TextField(QWidget *parent = Q_NULLPTR);
    ~TextField();

    void setTextEditorView(Qt::GlobalColor color);
    void setFont(const QFont &font);
    void clear();

    QPoint getShiftByCoord(QPoint point);
    bool readFile(const QString &fileName);
    bool writeFile(const QString &fileName);

    // Properties

    void setHexCaps(const bool isCaps);
    bool hexCaps() const;

signals:
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

private:
    QWidget *field_;
    QPoint edge_;

    Cursor *cursor_;

    Text textLines_;
    int curLineInd_;
    int curSymbInd_;

    int pxCharHeight_;
    int pxCharWidth_;
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
    Recorder *records_;

    //Cursor vars
    int _addressWidth;
    int _addrDigits;

    QByteArray _dataShown;
    QByteArray _hexDataShown;
    qint64 _lastEventSize;
    QByteArray _markedShown;
    int _rowsShown;
    bool _dynamicBytesPerLine;
};

#endif
