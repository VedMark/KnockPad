#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include <QPalette>
#include <QScrollArea>
#include <QString>
#include <QWidget>

#include <QKeyEvent>
#include <QPainter>

class TextField : public QScrollArea
{
    Q_OBJECT

public:
    explicit TextField(QWidget *parent = Q_NULLPTR);
    ~TextField();

    void setTextEditorView(Qt::GlobalColor color);
    void clear();

    bool readFile(const QString &fileName);
    bool writeFile(const QString &fileName);

public slots:

signals:
    void sign();

protected:
    //void paintEvent(QPaintEvent *);
    //void mousePressEvent(QPaintEvent *);

private:
    QWidget *field;

};

#endif
