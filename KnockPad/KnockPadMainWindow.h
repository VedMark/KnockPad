#ifndef KNOCKPADMAINWINDOW_H
#define KNOCKPADMAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QtWidgets>
#include <QtCore>
#include <QtGui>

class KnockPadMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    KnockPadMainWindow(QWidget *parent = 0);
    ~KnockPadMainWindow();

signals:

public slots:
    void createNewFile();
    void showOpenMenu();
    void saveInCurrentFile();
    void showSaveMenu();
    void openRecentFile();

    void cutText();
    void copyText();
    void pasteText();
    void deleteText();

    void changeFontType();
    void changeFontSize();
    void setBoldText();
    void setItalicText();

    void slotActivated(QAction* pAction);

protected:
     virtual void contextMenuEvent(QContextMenuEvent* pe);

private:
    void createFileActions();
    void createFileMenu();
    void createEditActions();
    void createEditMenu();
    void createToolBar();
    void createContextMenu();


    enum { MAX_RECENT_FILES = 5 };

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *contextMenu;
    QMenu *fontMenu;
    QMenu *sizeMenu;

    QToolBar *toolBar;

    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *recentFileActions[MAX_RECENT_FILES];
    QAction *exitAction;

    QAction *cutAction;
    QAction *copyAction;
    QAction *pasteAction;
    QAction *deleteAction;

    QAction *fontTypeAction;
    QAction *fontSizeAction;
    QAction *fontBoldAction;
    QAction *fontItalicAction;
};

#endif
