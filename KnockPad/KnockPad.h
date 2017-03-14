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
#include <QMenu>
#include <QDialog>

#include "KnockPadMainWindow.h"
#include "MenuComponents.h"
#include "TextField.h"

class KnockPad : public QApplication
{
    Q_OBJECT

public:
    explicit KnockPad(int argc, char **argv);
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

private:
    bool maybeSave();
    void setCurrentFileName(const QString &fileName);

    KnockPadMainWindow mainWindow;
    MenuComponents menuComponents;
    TextField *textField;

    QString currentFileName;
    QTextEdit textEdit;
};

#endif
