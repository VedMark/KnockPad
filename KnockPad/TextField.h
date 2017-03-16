#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include <QBrush>
#include <QPalette>
#include <QPixmap>
#include <QWidget>
#include <QScrollBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QBoxLayout>
#include <QScrollArea>

class TextField : public QWidget
{
    Q_OBJECT

public:
    explicit TextField(QWidget *parent = Q_NULLPTR);
    ~TextField();

    void setView(Qt::GlobalColor color);

public slots:

signals:
    void sign();

protected:
    //void paintEvent(QPaintEvent *);

private:

};

#endif
