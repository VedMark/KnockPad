#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include <QApplication>
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
    explicit TextField(QString fontName, int fontSize, QWidget *parent = Q_NULLPTR);
    ~TextField();

    void setTextEditorView(Qt::GlobalColor color);
    void clear();

    QPoint getShiftByCoord(QPoint point);
    bool readFile(const QString &fileName);
    bool writeFile(const QString &fileName);

    inline bool capsLock() const { return capsPressed_; }
    inline void setCapsLock(const bool caps) { capsPressed_ = caps; }

    inline bool isSelected() const { return selected_; }
    inline void setSelected(bool selected) { selected_ = selected; }

    inline int getCurPosX() const;
    inline int getCurPosY() const;
    inline void setCurrentPos(const QPoint& curPos);

    void copy();
    void cut();
    void paste();
    void selectAll();

public slots:
    void changeCurrentFontSize(const QString &font);
    void changeCurrentFont(const QString &font);
    void changeToItalics();
    void changeToBold();

signals:
    void posChanged(QPoint);
    void fontChanged(const QFont&);

protected:
    void keyPressEvent(QKeyEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

private:
    inline QPoint _get_end_document();
    inline void _change_positions(QPoint p);

    inline QPoint _handle_backspace();
    inline QPoint _handle_enter();

    void _fill_highlightning_rect(QPainter &painter, const QPoint&, const QPoint&);
    inline void _set_selection_begin(QPoint);
    inline void _set_selection_end(QPoint);
    inline void _set_selection_pos(QPoint);
    inline void _erase_highlighted_text();
    inline const QPoint& minPoint(const QPoint&, const QPoint&) const;
    inline const QPoint& maxPoint(const QPoint&, const QPoint&) const;
    inline void _reset_selection();
    inline void _set_cursor_points(QPoint p);
    inline void _change_cursor(QPoint p);

private:
    QWidget *field_;
    QPoint edge_;

    Cursor* cursor_;

    Text* textLines_;
    Text* textBuffer_;

    QPoint curPos_;
    bool capsPressed_;

    QColor highlightningColor_;
    QPoint selectionBegin_;
    QPoint selectionEnd_;
    QPoint selectionPos_;
    bool selected_;

    int currentFontSize;
};

#endif
