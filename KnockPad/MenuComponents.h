#ifndef MENUCOMPONENTS_H
#define MENUCOMPONENTS_H

#include <QAction>
#include <QtCore>
#include <QMenu>
//#include <QWidget>

class MenuComponents : public QWidget
{
    Q_OBJECT

public:
    explicit MenuComponents(QWidget *parent = 0);
    ~MenuComponents();

    void addFileActions(QWidget *menu);
    void addRecentFilesActions(QWidget *menu);
    void addEditActions(QWidget *menu);
    void addFontActions(QWidget *menu);
    void addDropDawnFontActions(QMenu *menu);
    void addExitAction(QWidget *menu);

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
private:
    enum { MAX_RECENT_FILES = 5 };

    void createFileActions();
    void createEditActions();
    void createFontActions();

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

    QMenu *fontTypeMenu;
    QMenu *fontSizeMenu;

    QAction *fontTypeAction;
    QAction *fontSizeAction;
    QAction *fontBoldAction;
    QAction *fontItalicAction;
};

#endif
