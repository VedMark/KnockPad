#ifndef CURSOR_H
#define CURSOR_H

#include <QAbstractScrollArea>
#include <QColor>
#include <QtCore>
#include <QObject>
#include <QPainter>
#include <QPoint>
#include <QRect>
#include <QTimer>

class Cursor: QObject
{
    Q_OBJECT
public:
    explicit Cursor(QWidget *holder, QObject *parent = Q_NULLPTR);
    ~Cursor();

    void setCursorPosition(QPoint position);
    void setCursorPosition(QPoint position, int w, int h);
    QPoint cursorPosition() const;

    inline QRect rectangle() const { return rect_; }
    inline void setRectangle(QRect rect) { rect_ = rect; }

    inline QWidget* holder() const { return holder_; }
    inline void setHolder(QWidget * holder) { holder_ = holder; }

    inline bool blink() const { return blink_; }
    inline void setBlink(bool blink) { blink_ = blink; }

    inline QColor colorCursor() const { return colorCursor_; }
    inline void setColorCursor(QColor color) { colorCursor_ = color; }

    inline QColor colorBase() const { return colorBase_; }
    inline void setColorBase(QColor color) { colorBase_ = color; }

    inline int x() const { return rect_.x(); }
    inline void setX(int x) { rect_.setX(x); }

    inline int y() const { return rect_.y(); }
    inline void setY(int y) { rect_.setY(y); }

    inline int width() const { return rect_.width(); }
    inline void setWidth(int width)
    {
        rect_.setWidth(static_cast<int>(log(width) / log(4)) + 1);
    }

    inline int heigth() const { return rect_.height(); }
    inline void setHeigth(int heigth) { rect_.setHeight(heigth); }

    inline QPoint Edge() const { return edge_; }
    inline void setEdge(QPoint edge)
    {
        edge_ = edge;
        rect_.setX(rect_.x() + edge.x());
        rect_.setY(rect_.y() + edge.y());
    }

    void draw(QPainter *painter);

signals:
    void currentAddressChanged(QPoint address);

public slots:
    void updateCursor();

private:
    QRect rect_;
    QWidget *holder_;

    QTimer timer_;

    QColor colorCursor_;
    QColor colorBase_;
    QPoint edge_;
    bool blink_;
};

#endif