#include "KnockPad.h"

KnockPad::KnockPad() :
    QMainWindow()
{
    menuComponents = new MenuComponents;

    menu = new Menu(menuComponents, this);
    setMenuBar(menu);

    editToolBar = new EditToolBar(menuComponents, this);
    addToolBar(editToolBar);

    statusBar = new StatusBar(this);
    setStatusBar(statusBar);

    defaultFont = QFont(editToolBar->getFontType(), editToolBar->getFontSize());

    textField = new TextField(defaultFont, this);
    textField->setFocus();
    setCentralWidget(textField);
    textField->setTextEditorView(Qt::white);

    //setWindowIcon(QIcon(":/images/icon.png"));
    setCurrentFileName("");

    connect(menuComponents->newAction, SIGNAL( triggered() ), SLOT( newFile() ) );
    connect(menuComponents->openAction, SIGNAL( triggered() ), SLOT( open() ) );
    connect(menuComponents->saveAction, SIGNAL( triggered() ), SLOT( save() ) );
    connect(menuComponents->saveAsAction, SIGNAL( triggered() ), SLOT( saveAs() ) );
    connect(menuComponents->exitAction, SIGNAL( triggered() ), SLOT( closeApp() ) );
    connect(menuComponents->cutAction, SIGNAL( triggered() ), SLOT( cutText() ) );
    connect(menuComponents->copyAction, SIGNAL( triggered() ), SLOT( copyText() ) );
    connect(menuComponents->pasteAction, SIGNAL( triggered() ), SLOT( pasteText() ) );
    connect(menuComponents->deleteAction, SIGNAL( triggered() ), SLOT( deleteText() ) );
    connect(menuComponents->fontTypeMenu, SIGNAL( triggered(QAction*) ), SLOT( changeCurrentFont(QAction*) ) );
    connect(menuComponents->fontSizeMenu, SIGNAL( triggered(QAction*) ), SLOT( changeFontSize(QAction*) ) );

    connect(textField, SIGNAL( posChanged(QPoint) ), statusBar, SLOT(updateStatusBar(QPoint)) );

    connect(editToolBar->getFontBox(), SIGNAL( activated(QString) ), textField, SLOT( changeCurrentFont(QString) ) );
    connect(editToolBar->getSizeBox(), SIGNAL(activated(QString)), textField, SLOT( changeCurrentFontSize(QString) ) );
    connect(menuComponents->fontBoldAction, SIGNAL( triggered() ), SLOT( setBoldText() ) );
    connect(menuComponents->fontItalicAction, SIGNAL( triggered() ), SLOT( setItalicText() ) );

    connect(textField, SIGNAL( fontChanged(const QFont&)), editToolBar, SLOT( changeToolBarFonts(const QFont&) ));

    setWindowTitle(tr("KnockPad"));

    textField->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    textField->resize(sizeHint());
    setMinimumSize(400, 200);
    setMaximumSize(1368, 768);
    resize(700, 600);


    show();
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
        closeEvent->accept();
    }
    else
        closeEvent->ignore();
}

bool KnockPad::agreedToContinue()
 {
     if (!textEdit.document()->isModified())
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
                                                tr("Open file"), "/media/bsuir",
                                                tr("Text files (*.txt);;KnockPad files (*.kp)"));
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
                                                tr("Save file"), "/media/bsuir",
                                                tr("Text files (*.txt);;KnockPad files (*.kp)"));
    if(fileName.isEmpty())
        return false;
    if(!fileName.endsWith(".txt") && !fileName.endsWith(".kp"))
        fileName += ".kp";
    return saveFile(fileName);
}

bool KnockPad::loadFile(const QString &fileName)
{
    try{
        textField->setText(fileRecorder.read(fileName, defaultFont));

        textField->setCurrentPos(QPoint(0, 0));
        setCurrentFileName(fileName);
        statusBar->showMessage(tr("File loaded"), 2000);
    }
    catch(FileOpenException &)
    {
        statusBar->showMessage(tr("Loadind canceled"), 2000);
        return false;
    }

    return true;
}

bool KnockPad::saveFile(const QString &fileName)
{
    try{
        fileRecorder.write(textField->getText(), fileName);
        setCurrentFileName(fileName);
        statusBar->showMessage(tr("File saved"), 2000);
    }
    catch(FileOpenException &)
    {
        statusBar->showMessage(tr("Saving canceled"), 2000);
        return false;
    }

    return true;
}

void KnockPad::closeApp()
{
    close();
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

void KnockPad::changeFontSize(QAction* action)
{
    textField->changeCurrentFontSize(action->text());
}

void KnockPad::changeCurrentFont(QAction* action)
{
    textField->changeCurrentFont(action->text());
}

void KnockPad::setBoldText()
{
    bool checked = menuComponents->fontBoldAction->isChecked() ? true : false;
    menuComponents->fontBoldAction->setChecked(checked);
    textField->changeBold(checked);
}

void KnockPad::setItalicText()
{
    bool checked = menuComponents->fontItalicAction->isChecked() ? true : false;
    menuComponents->fontItalicAction->setChecked(checked);
    textField->changeItalics(checked);
}

void KnockPad::setCurrentFileName(const QString &fileName)
{
    currentFileName = fileName;
    //textEdit.setModified(false);

    QString shownName;
    if(currentFileName.isEmpty())
        shownName = tr("untitled.txt");
    else
        shownName = QFileInfo(currentFileName).fileName();

    //setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("Rich Text")));
    //setWindowModified();
}
