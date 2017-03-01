#ifndef KNOCKPADMAINWINDOW_H
#define KNOCKPADMAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QtWidgets>
#include <QtCore>
#include <QtGui>
#include "MenuComponents.h"
#include "PublicSlots.h"
#include "TextField.h"

class KnockPadMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    KnockPadMainWindow(QWidget *parent = 0);
    ~KnockPadMainWindow();

signals:

public slots:
    //void slotActivated(QAction* pAction);

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

    QAction *fontTypeAction;
    QAction *fontSizeAction;
    QMenu *fontMenu;
    QMenu *sizeMenu;

    QToolBar *toolBar;

    TextField *textField;

};

#endif
