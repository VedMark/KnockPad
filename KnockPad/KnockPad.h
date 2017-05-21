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
#include "StatusBar.h"
#include "TextField.h"
#include "Recorder.h"

class KnockPad : public QMainWindow
{
    Q_OBJECT


public:
    explicit KnockPad();
    ~KnockPad();

public slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();

    void closeApp();

    void cutText();
    void copyText();
    void pasteText();
    void deleteText();

    void changeCurrentFont(QAction*);
    void changeFontSize(QAction*);
    void setBoldText();
    void setItalicText();

protected:
    void contextMenuEvent(QContextMenuEvent* pe);
    void closeEvent(QCloseEvent * closeEvent);

    void createStatusBar();

private:
    bool loadFile(const QString &openFileName);
    bool saveFile(const QString &openFileName);

    bool agreedToContinue();
    void setCurrentFileName(const QString &fileName);

    MenuComponents *menuComponents;
    Menu *menu;
    EditToolBar *editToolBar;
    StatusBar *statusBar;

    TextField *textField;

    Recorder fileRecorder;

    QFont defaultFont;

    QString currentFileName;
    QTextEdit textEdit;
};

#endif
