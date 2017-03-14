#ifndef KNOCKPADMAINWINDOW_H
#define KNOCKPADMAINWINDOW_H

#include <QApplication>
#include <QtCore>
#include <QtGui>
#include <QContextMenuEvent>
#include <QWidget>
#include <QMainWindow>
//#include <QMenu>
#include <QMenuBar>
#include <QPalette>
#include <QToolBar>

#include "MenuComponents.h"
#include "TextField.h"

class KnockPadMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    KnockPadMainWindow(QWidget *parent = 0);
    ~KnockPadMainWindow();

    void createMenu(MenuComponents *menuComponents);
    void createToolBar(MenuComponents *menuComponents);
    void createContextMenu(MenuComponents *menuComponents);
    void createTextField(TextField *textField);

signals:

public slots:

protected:
     virtual void contextMenuEvent(QContextMenuEvent* pe);

private:
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *contextMenu;
    QToolBar *toolBar;
};

#endif
