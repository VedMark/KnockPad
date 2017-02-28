#include "KnockPadMainWindow.h"

KnockPadMainWindow::KnockPadMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->createFileActions();
    this->createFileMenu();
    this->createEditActions();
    this->createEditMenu();
    this->createToolBar();
    this->createContextMenu();
    //this->setWindowIcon();
}

KnockPadMainWindow::~KnockPadMainWindow()
{
    delete fileMenu;
    delete contextMenu;
    delete fontMenu;
    delete sizeMenu;
    delete editMenu;

    delete newAction;
    delete openAction;
    delete saveAction;
    delete saveAsAction;
    for(int i = 0; i < MAX_RECENT_FILES; ++i)
        delete this->recentFileActions[i];
    delete exitAction;

    delete cutAction;
    delete copyAction;
    delete pasteAction;
    delete deleteAction;

    delete fontTypeAction;
    delete fontSizeAction;
    delete fontBoldAction;
    delete fontItalicAction;
}

void KnockPadMainWindow::createFileActions()
{
    this->newAction = new QAction("&New", this);
    this->newAction->setIcon(QIcon(":/images/new.png"));
    this->newAction->setShortcut(QKeySequence::New);
    connect(this->newAction, SIGNAL( triggered() ), SLOT( createNewFile() ) );

    this->openAction = new QAction("&Open", this);
    this->openAction->setIcon(QIcon(":/images/open.png"));
    this->openAction->setShortcut(QKeySequence::Open);
    connect(this->openAction, SIGNAL( triggered() ), SLOT( showOpenMenu() ) );

    this->saveAction = new QAction("&Save", this);
    this->saveAction->setIcon(QIcon(":/images/save.png"));
    this->saveAction->setShortcut(Qt::CTRL + Qt::Key_S);
    this->saveAction->setStatusTip("Save in current file");
    connect(this->saveAction, SIGNAL( triggered() ), SLOT( saveInCurrentFile() ) );

    this->saveAsAction = new QAction("&Save As", this);
    this->saveAsAction->setShortcut(QKeySequence::SaveAs);
    connect(this->saveAsAction, SIGNAL( triggered() ), SLOT( showSaveMenu() ) );

    for(int i = 0; i < MAX_RECENT_FILES; ++i)
    {
        this->recentFileActions[i] = new QAction(this);
        this->recentFileActions[i]->setVisible(false);
        connect(this->recentFileActions[i], SIGNAL( triggered() ), SLOT( openRecentFile() ) );
    }

    this->exitAction = new QAction("&Exit", this);
    this->exitAction->setShortcut(QKeySequence::Quit);
    connect(this->exitAction, SIGNAL( triggered() ), SLOT( close() ) );
}

void KnockPadMainWindow::createFileMenu()
{
    this->fileMenu = menuBar()->addMenu("&file");
    this->fileMenu->addAction(this->newAction);
    this->fileMenu->addAction(this->openAction);
    this->fileMenu->addAction(this->saveAction);
    this->fileMenu->addAction(this->saveAsAction);
    this->fileMenu->addSeparator();

    for(int i = 0; i < MAX_RECENT_FILES; ++i)
        fileMenu->addAction(this->recentFileActions[i]);
    this->fileMenu->addSeparator();

    this->fileMenu->addAction(this->exitAction);
}

void KnockPadMainWindow::createEditActions()
{
    this->cutAction = new QAction("&Cut", this);
    this->cutAction->setIcon(QIcon(":/images/cut.png"));
    this->cutAction->setShortcut(QKeySequence::Cut);
    connect(this->cutAction, SIGNAL( triggered() ), SLOT( cutText() ) );

    this->copyAction = new QAction("&Copy", this);
    this->copyAction->setIcon(QIcon(":/images/copy.png"));
    this->copyAction->setShortcut(QKeySequence::Copy);
    connect(this->copyAction, SIGNAL( triggered() ), SLOT( copyText() ) );

    this->pasteAction = new QAction("&Paste", this);
    this->pasteAction->setIcon(QIcon(":/images/paste.png"));
    this->pasteAction->setShortcut(QKeySequence::Paste);
    connect(this->saveAction, SIGNAL( triggered() ), SLOT( pasteText() ) );

    this->deleteAction = new QAction("&Delete", this);
    this->deleteAction->setIcon(QIcon(":/images/delete.png"));
    this->deleteAction->setShortcut(QKeySequence::Delete);
    connect(this->deleteAction, SIGNAL( triggered() ), SLOT( deleteText() ) );

    this->fontTypeAction = new QAction("&Font", this);
    connect(this->fontTypeAction, SIGNAL( triggered() ), SLOT( changeFontType() ) );

    this->fontSizeAction = new QAction("&Size", this);
    connect(this->fontSizeAction, SIGNAL( triggered() ), SLOT( changeFontSize() ) );

    this->fontBoldAction = new QAction("&Bold", this);
    connect(this->fontBoldAction, SIGNAL( triggered() ), SLOT( setBoldText() ) );

    this->fontItalicAction = new QAction("&Italics", this);
    connect(this->fontItalicAction, SIGNAL( triggered() ), SLOT( setItalicText() ) );
}

void KnockPadMainWindow::createEditMenu()
{
    this->editMenu = menuBar()->addMenu("&edit");
    this->editMenu->addAction(this->cutAction);
    this->editMenu->addAction(this->copyAction);
    this->editMenu->addAction(this->pasteAction);
    this->editMenu->addAction(this->deleteAction);
    this->editMenu->addSeparator();

    this->fontMenu = new QMenu("&Font", this->editMenu);
    this->editMenu->addMenu(this->fontMenu);
    this->fontMenu->addAction(this->fontTypeAction);

    this->sizeMenu = new QMenu("&Size", this->editMenu);
    this->editMenu->addMenu(this->sizeMenu);
    this->sizeMenu->addAction(this->fontSizeAction);

    this->editMenu->addAction(this->fontBoldAction);
    this->editMenu->addAction(this->fontItalicAction);
}

void KnockPadMainWindow::createToolBar()
{
    this->toolBar = new QToolBar(this);

    this->toolBar->resize(600, 50);

    this->toolBar->addAction(this->newAction);
    this->toolBar->addAction(this->openAction);
    this->toolBar->addAction(this->saveAction);
    this->toolBar->addAction(this->saveAsAction);

    this->toolBar->addSeparator();

    this->toolBar->addAction(this->cutAction);
    this->toolBar->addAction(this->copyAction);
    this->toolBar->addAction(this->pasteAction);
    this->toolBar->addAction(this->deleteAction);

    this->toolBar->addSeparator();

    this->toolBar->addAction(this->fontTypeAction);
    this->toolBar->addAction(this->fontSizeAction);
    this->toolBar->addAction(this->fontBoldAction);
    this->toolBar->addAction(this->fontItalicAction);
}

void KnockPadMainWindow::createContextMenu()
{
    this->contextMenu = new QMenu(this);
    this->contextMenu->addAction(cutAction);
    this->contextMenu->addAction(copyAction);
    this->contextMenu->addAction(pasteAction);
    this->contextMenu->addAction(deleteAction);

    this->contextMenu->addSeparator();

    this->contextMenu->addMenu(fontMenu);
    this->contextMenu->addMenu(sizeMenu);
    this->contextMenu->addAction(this->fontBoldAction);
    this->contextMenu->addAction(this->fontItalicAction);

    connect(this->contextMenu, SIGNAL( triggered(QAction*) ), SLOT( slotActivated(QAction*) ) );
}

void KnockPadMainWindow::contextMenuEvent(QContextMenuEvent* mouse_pointer)
{
    this->contextMenu->exec(mouse_pointer->globalPos());
}

void KnockPadMainWindow::createNewFile()
{
    qDebug() << "createNewFile";
}

void KnockPadMainWindow::showOpenMenu()
{
    qDebug() << "showOpenMenu";
}

void KnockPadMainWindow::saveInCurrentFile()
{
    qDebug() << "saveInCurrentFile";
}

void KnockPadMainWindow::showSaveMenu()
{
    qDebug() << "showSaveMenu";
}

void KnockPadMainWindow::openRecentFile()
{
    qDebug() << "openRecentFile";
}

void KnockPadMainWindow::cutText()
{
    qDebug() << "cutText";
}

void KnockPadMainWindow::copyText()
{
    qDebug() << "copyText";
}

void KnockPadMainWindow::pasteText()
{
    qDebug() << "pasteText";
}

void KnockPadMainWindow::deleteText()
{
    qDebug() << "deleteText";
}

void KnockPadMainWindow::changeFontType()
{
    qDebug() << "changeFontType";
}

void KnockPadMainWindow::changeFontSize()
{
    qDebug() << "changeFontSize";
}

void KnockPadMainWindow::setBoldText()
{
    qDebug() << "setBoldText";
}

void KnockPadMainWindow::setItalicText()
{
    qDebug() << "setItalicText";
}

void KnockPadMainWindow::slotActivated(QAction* pAction)
{
    qDebug() << "ContextMenu activated";
}
