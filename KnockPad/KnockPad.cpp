#include "KnockPad.h"

KnockPad::KnockPad() : QMainWindow()
{
    menuComponents = new MenuComponents;

    menu = new Menu(menuComponents, this);
    setMenuBar(menu);

    editToolBar = new EditToolBar(menuComponents, this);
    addToolBar(editToolBar);

    this->textField = new TextField(this);
    setCentralWidget(textField);
    this->textField->setView(Qt::white);

/*
    scrollArea = new QScrollArea(this);
    scrollArea->setGeometry(50, 50, 1208, 650);
    scrollArea->setViewport(this->textField);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
*/
    connect(menuComponents->newAction, SIGNAL( triggered() ), SLOT( createNewFile() ) );
    connect(menuComponents->openAction, SIGNAL( triggered() ), SLOT( showOpenMenu() ) );
    connect(menuComponents->saveAction, SIGNAL( triggered() ), SLOT( saveInCurrentFile() ) );
    connect(menuComponents->saveAsAction, SIGNAL( triggered() ), SLOT( showSaveMenu() ) );
    for(int i = 0; i < MenuComponents::MAX_RECENT_FILES; ++i)
        connect(menuComponents->recentFileActions[i], SIGNAL( triggered() ), SLOT( openRecentFile() ) );
    connect(menuComponents->exitAction, SIGNAL( triggered() ), SLOT( close() ) );
    connect(menuComponents->cutAction, SIGNAL( hovered() ), SLOT( cutText() ) );
    connect(menuComponents->copyAction, SIGNAL( triggered() ), SLOT( copyText() ) );
    connect(menuComponents->pasteAction, SIGNAL( triggered() ), SLOT( pasteText() ) );
    connect(menuComponents->deleteAction, SIGNAL( triggered() ), SLOT( deleteText() ) );
    connect(menuComponents->fontTypeAction, SIGNAL( triggered() ), SLOT( changeFontType() ) );
    connect(menuComponents->fontSizeAction, SIGNAL( triggered() ), SLOT( changeFontSize() ) );
    connect(menuComponents->fontBoldAction, SIGNAL( triggered() ), SLOT( setBoldText() ) );
    connect(menuComponents->fontItalicAction, SIGNAL( triggered() ), SLOT( setItalicText() ) );

    this->setWindowTitle("KnockPad");

    this->resize(1366, 768);
    this->show();
}

KnockPad::~KnockPad()
{
    delete menuComponents;\
    delete menu;
    delete editToolBar;
    delete textField;
}

void KnockPad::contextMenuEvent(QContextMenuEvent* mouse_pointer)
{
    menu->getContextMenu()->exec(mouse_pointer->globalPos());
}

void KnockPad::createNewFile()
{
    if(maybeSave())
    {
        textEdit.clear();
        //setCurrentFileName(QString());
    }
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
     QMessageBox::warning(this, tr("text"), tr("text2"));
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
