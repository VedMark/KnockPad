#ifndef MENUCOMPONENTS_H
#define MENUCOMPONENTS_H

#include <QAction>
#include <QtCore>
#include <QComboBox>
#include <QFileDialog>
#include <QMenu>
#include <QDialog>

class MenuComponents : public QWidget
{
    Q_OBJECT

public:
    explicit MenuComponents(QWidget *parent = Q_NULLPTR);
    ~MenuComponents();

    void addFileActions(QWidget *menu);
    void addRecentFilesActions(QWidget *menu);
    void addEditActions(QWidget *menu);
    void addFontActions(QWidget *menu);
    void addDropDawnFontActions(QMenu *menu);
    void addExitAction(QWidget *menu);

    enum { MAX_RECENT_FILES = 5 };

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

    inline const QStringList& getFontList() const { return fonts; }
    inline const QStringList& getFontSizeList() const { return fontSizes; }

public slots:

private:
    QString resentFileNames[MAX_RECENT_FILES];
    void createFileActions();
    void createEditActions();
    void createFontActions();

    QMenu *fontTypeMenu;
    QMenu *fontSizeMenu;

    QStringList fonts;
    QStringList fontSizes;
};

#endif
