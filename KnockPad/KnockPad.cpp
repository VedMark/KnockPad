#include "KnockPad.h"

KnockPad::KnockPad() : QMainWindow()
{
    menuComponents = new MenuComponents;

    menu = new Menu(menuComponents, this);
    setMenuBar(menu);

    editToolBar = new EditToolBar(menuComponents, this);
    addToolBar(editToolBar);

    statusBar = new StatusBar(this);
    setStatusBar(statusBar);

    textField = new TextField(editToolBar->getFontType(), editToolBar->getFontSize(), this);
    textField->setFocus();
    setCentralWidget(textField);
    textField->setTextEditorView(Qt::white);

    //setWindowIcon(QIcon(":/images/icon.png"));
    //setCurrentFileName("");

    connect(menuComponents->newAction, SIGNAL( triggered() ), SLOT( newFile() ) );
    connect(menuComponents->openAction, SIGNAL( triggered() ), SLOT( open() ) );
    connect(menuComponents->saveAction, SIGNAL( triggered() ), SLOT( save() ) );
    connect(menuComponents->saveAsAction, SIGNAL( triggered() ), SLOT( saveAs() ) );
    for(int i = 0; i < MenuComponents::MAX_RECENT_FILES; ++i)
        connect(menuComponents->recentFileActions[i], SIGNAL( triggered() ), SLOT( openRecentFile() ) );
    connect(menuComponents->exitAction, SIGNAL( triggered() ), SLOT( closeApp() ) );
    connect(menuComponents->cutAction, SIGNAL( triggered() ), SLOT( cutText() ) );
    connect(menuComponents->copyAction, SIGNAL( triggered() ), SLOT( copyText() ) );
    connect(menuComponents->pasteAction, SIGNAL( triggered() ), SLOT( pasteText() ) );
    connect(menuComponents->deleteAction, SIGNAL( triggered() ), SLOT( deleteText() ) );
    connect(menuComponents->fontTypeAction, SIGNAL( triggered() ), SLOT( changeFontType() ) );
    connect(menuComponents->fontSizeAction, SIGNAL( triggered() ), SLOT( changeFontSize() ) );
    connect(menuComponents->fontBoldAction, SIGNAL( triggered() ), SLOT( setBoldText() ) );
    connect(menuComponents->fontItalicAction, SIGNAL( triggered() ), SLOT( setItalicText() ) );

    connect(textField, SIGNAL( posChanged(QPoint) ), statusBar, SLOT(updateStatusBar(QPoint)) );
    connect(editToolBar->getFontBox(), SIGNAL( activated(QString) ), textField, SLOT( changeCurrentFont(QString) ) );
    connect(editToolBar->getSizeBox(), SIGNAL(activated(QString)), textField, SLOT( changeCurrentFontSize(QString) ) );
    connect(textField, SIGNAL( fontChanged(const QFont&)), editToolBar, SLOT( changeToolBarFonts(const QFont&) ));

    this->setWindowTitle(tr("KnockPad"));

    this->resize(1366, 768);
    this->show();
}

KnockPad::~KnockPad()
{
}

void KnockPad::contextMenuEvent(QContextMenuEvent* mouse_pointer)
{
    menu->getContextMenu()->exec(mouse_pointer->globalPos());
}

void KnockPad::closeEvent(QCloseEvent * closeEvent)
{
    if(agreedToContinue()){
        //writeSettings();
        closeEvent->accept();
    }
    else
        closeEvent->ignore();
}

void KnockPad::resizeEvent(QResizeEvent *)
{

}

bool KnockPad::agreedToContinue()
 {
     if (!this->textEdit.document()->isModified())
         return true;
     QMessageBox::StandardButton answer = QMessageBox::warning(this,
                       tr("The document has been modified"),
                       tr("Do you want to save your changes?"),
                       QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

     if (answer == QMessageBox::Save)
         return save();
     else if (answer == QMessageBox::Cancel)
         return false;
     return true;
 }

void KnockPad::newFile()
{
    if(agreedToContinue()){
        textField->clear();
        setCurrentFileName("");
    }
}

void KnockPad::open()
{
    if(agreedToContinue()){
        QString openFileName = QFileDialog::getOpenFileName(this,
                                                tr("Open file"), ".",
                                                tr("*.*"));
        if(!openFileName.isEmpty())
            loadFile(openFileName);

    }
}

bool KnockPad::save()
{
    if(currentFileName.isEmpty())
        return saveAs();
    else
        return saveFile(currentFileName);
}

bool KnockPad::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                tr("Save file"), ".",
                                                tr("*.*"));
    if(!fileName.isEmpty())
        return false;
    return saveFile(fileName);
}

bool KnockPad::loadFile(const QString &fileName)
{
    if(!textField->readFile(fileName)){
        statusBar->showMessage(tr("Loadind canceled"), 2000);
        return false;
    }
    setCurrentFileName(fileName);
    statusBar->showMessage(tr("File loaded"), 2000);
    return true;
}

bool KnockPad::saveFile(const QString &fileName)
{
    if(!textField->writeFile(fileName)){
        statusBar->showMessage(tr("Saving canceled"));
        return false;
    }
    setCurrentFileName(fileName);
    statusBar->showMessage(tr("File saved"), 2000);
    return true;
}

void KnockPad::closeApp()
{
    close();
}

void KnockPad::saveInCurrentFile()
{
    QString str = QFileDialog::getSaveFileName(0, tr("Save File"));
    if(!currentFileName.isEmpty())
    {
    }
}

void KnockPad::openRecentFile()
{
//    if(agreedToContinue())
//        loadFile(recentFileNames[menuComponents->MAX_RECENT_FILES - 1]);

}

void KnockPad::cutText()
{
    textField->cut();
}

void KnockPad::copyText()
{
    textField->copy();
}

void KnockPad::pasteText()
{
    textField->paste();
}

void KnockPad::deleteText()
{
     textField->clear();
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

void KnockPad::setCurrentFileName(const QString &fileName)
{
    this->currentFileName = fileName;
    //this->textEdit.setModified(false);

    QString shownName;
    if(this->currentFileName.isEmpty())
        shownName = tr("untitled.txt");
    else
        shownName = QFileInfo(this->currentFileName).fileName();

    //setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("Rich Text")));
    //setWindowModified();
}
