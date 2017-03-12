#ifndef KNOCKPADMAINWINDOW_H
#define KNOCKPADMAINWINDOW_H

#include <QApplication>
//#include <QtCore>
//#include <QtGui>
#include <QContextMenuEvent>
#include <QWidget>
#include <QMainWindow>
//#include <QMenu>
#include <QMenuBar>
#include <QToolBar>

#include "MenuComponents.h"
#include "TextField.h"

class KnockPadMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    KnockPadMainWindow(QWidget *parent = 0);
    ~KnockPadMainWindow();

signals:

public slots:

protected:
     virtual void contextMenuEvent(QContextMenuEvent* pe);

private:
    void createMenu();
    void createToolBar();
    void createContextMenu();
    void createTextField();

    MenuComponents menuComponents;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *contextMenu;

    QToolBar *toolBar;

    TextField *textField;
};

#endif
