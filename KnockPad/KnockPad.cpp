#include "KnockPad.h"

KnockPad::KnockPad(int argc, char **argv)
    : QApplication(argc, argv)
{
    textField = new TextField(&mainWindow);
    mainWindow.createMenu(&this->menuComponents);
    mainWindow.createToolBar(&this->menuComponents);
    mainWindow.createContextMenu(&this->menuComponents);
    mainWindow.createTextField(this->textField);

    connect(this->menuComponents.newAction, SIGNAL( triggered() ), SLOT( createNewFile() ) );
    connect(this->menuComponents.openAction, SIGNAL( triggered() ), SLOT( showOpenMenu() ) );
    connect(this->menuComponents.saveAction, SIGNAL( triggered() ), SLOT( saveInCurrentFile() ) );
    connect(this->menuComponents.saveAsAction, SIGNAL( triggered() ), SLOT( showSaveMenu() ) );
    for(int i = 0; i < MenuComponents::MAX_RECENT_FILES; ++i)
        connect(this->menuComponents.recentFileActions[i], SIGNAL( triggered() ), SLOT( openRecentFile() ) );
    // TODO: add normal exit()
    //connect(this->menuComponents.exitAction, SIGNAL( triggered() ), &this->mainWindow, SLOT( Quit() ) );
    connect(this->menuComponents.cutAction, SIGNAL( triggered() ), SLOT( cutText() ) );
    connect(this->menuComponents.copyAction, SIGNAL( triggered() ), SLOT( copyText() ) );
    connect(this->menuComponents.pasteAction, SIGNAL( triggered() ), SLOT( pasteText() ) );
    connect(this->menuComponents.deleteAction, SIGNAL( triggered() ), SLOT( deleteText() ) );
    connect(this->menuComponents.fontTypeAction, SIGNAL( triggered() ), SLOT( changeFontType() ) );
    connect(this->menuComponents.fontSizeAction, SIGNAL( triggered() ), SLOT( changeFontSize() ) );
    connect(this->menuComponents.fontBoldAction, SIGNAL( triggered() ), SLOT( setBoldText() ) );
    connect(this->menuComponents.fontItalicAction, SIGNAL( triggered() ), SLOT( setItalicText() ) );

    this->mainWindow.setWindowTitle("KnockPad");

    this->mainWindow.resize(1366, 768);
    this->mainWindow.show();
}

KnockPad::~KnockPad()
{
    delete this->textField;
}

bool KnockPad::maybeSave()
 {
     if (!this->textEdit.document()->isModified())
         return true;
     if (currentFileName.startsWith(QLatin1String(":/")))
         return true;
     QMessageBox::StandardButton ret;
     //ret = QMessageBox::warning(this, tr("Application"),
       //                         tr("The document has been modified.\n"
         //                          "Do you want to save your changes?"),
           //                     QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
     QMessageBox::warning(&this->mainWindow, tr("text"), tr("text2"));
     if (ret == QMessageBox::Save)
         return true;//fileSave();
     else if (ret == QMessageBox::Cancel)
         return false;
     return true;
 }

void KnockPad::setCurrentFileName(const QString &fileName)
{
    this->currentFileName = fileName;
    //this->textEdit.setModified(false);

    QString shownName;
    if(this->currentFileName.isEmpty())
        shownName = "untitled.txt";
    else
        shownName = QFileInfo(this->currentFileName).fileName();

    //setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("Rich Text")));
    //setWindowModified();
}

void KnockPad::createNewFile()
{
    if(maybeSave())
    {
        textEdit.clear();
        //setCurrentFileName(QString());
    }
}

void KnockPad::showOpenMenu()
{
    qDebug() <<"showOpenMenu";
}

void KnockPad::saveInCurrentFile()
{
    QString str = QFileDialog::getSaveFileName(0, tr("Save File"));
    if(!currentFileName.isEmpty())
    {
        QFile file(currentFileName);
    }
}

void KnockPad::showSaveMenu()
{
    QString str = QFileDialog::getSaveFileName(0, "Save File");
}

void KnockPad::openRecentFile()
{
    qDebug() << "openRecentFile";
}

void KnockPad::cutText()
{
    qDebug() << "cutText";
}

void KnockPad::copyText()
{
    qDebug() << "copyText";
}

void KnockPad::pasteText()
{
    qDebug() << "pasteText";
}

void KnockPad::deleteText()
{
    qDebug() << "deleteText";
}

void KnockPad::changeFontType()
{
    qDebug() << "changeFontType";
}

void KnockPad::changeFontSize()
{
    qDebug() << "changeFontSize";
}

void KnockPad::setBoldText()
{
    qDebug() << "setBoldText";
}

void KnockPad::setItalicText()
{
    qDebug() << "setItalicText";
}
