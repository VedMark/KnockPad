#ifndef MENUCOMPONENTS_H
#define MENUCOMPONENTS_H

#include <QAction>
#include <QWidget>
#include "PublicSlots.h"

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
    void addExitAction(QWidget *menu);

public slots:
    static void createNewFile();
    static void showOpenMenu();
    static void saveInCurrentFile();
    static void showSaveMenu();
    static void openRecentFile();

    static void cutText();
    static void copyText();
    static void pasteText();
    static void deleteText();

    static void changeFontType();
    static void changeFontSize();
    static void setBoldText();
    static void setItalicText();
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

    QAction *fontBoldAction;
    QAction *fontItalicAction;
};

#endif
