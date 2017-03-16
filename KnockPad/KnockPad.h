#ifndef KNOCKPAD_H
#define KNOCKPAD_H

#include <QApplication>
#include <QString>
#include <QFile>
#include <QTextEdit>
#include <QMessageBox>
#include <QWidget>
#include <QAction>
#include <QtCore>
#include <QFileDialog>
#include <QtGui>
#include <QContextMenuEvent>
#include <QMainWindow>

#include "Menu.h"
#include "EditToolBar.h"
#include "TextField.h"

class KnockPad : public QMainWindow
{
    Q_OBJECT


public:
    explicit KnockPad();
    ~KnockPad();

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

signals:

protected:
    virtual void contextMenuEvent(QContextMenuEvent* pe);

private:
    bool maybeSave();
    void setCurrentFileName(const QString &fileName);

    MenuComponents *menuComponents;
    Menu *menu;
    EditToolBar *editToolBar;

    TextField *textField;

    QString currentFileName;
    QTextEdit textEdit;
    QScrollArea *scrollArea;



    QScrollBar *hBar;
    QScrollBar *vBar;
};

#endif
