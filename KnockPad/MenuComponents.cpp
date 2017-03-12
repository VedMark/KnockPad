#include "MenuComponents.h"

MenuComponents::MenuComponents(QWidget *parent)
    : QWidget(parent)
{
    createFileActions();
    createEditActions();
    createFontActions();
    this->fontTypeMenu = new QMenu("&Font", this);
    this->fontSizeMenu = new QMenu("&Size", this);
}

MenuComponents::~MenuComponents()
{
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

    delete fontTypeMenu;
    delete fontSizeMenu;

    delete fontTypeAction;
    delete fontSizeAction;
    delete fontBoldAction;
    delete fontItalicAction;

}

void MenuComponents::createFileActions()
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

void MenuComponents::createEditActions()
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
    this->pasteAction->setShortcut(Qt::CTRL + Qt::Key_V);
    connect(this->saveAction, SIGNAL( triggered() ), SLOT( pasteText() ) );

    this->deleteAction = new QAction("&Delete", this);
    this->deleteAction->setIcon(QIcon(":/images/delete.png"));
    this->deleteAction->setShortcut(QKeySequence::Delete);
    connect(this->deleteAction, SIGNAL( triggered() ), SLOT( deleteText() ) );
}

void MenuComponents::createFontActions()
{
    this->fontTypeAction = new QAction("&Font", this);
    connect(this->fontTypeAction, SIGNAL( triggered() ), SLOT( changeFontType() ) );

    this->fontSizeAction = new QAction("&Size", this);
    connect(this->fontSizeAction, SIGNAL( triggered() ), SLOT( changeFontSize() ) );

    this->fontBoldAction = new QAction("&Bold", this);
    connect(this->fontBoldAction, SIGNAL( triggered() ), SLOT( setBoldText() ) );

    this->fontItalicAction = new QAction("&Italics", this);
    connect(this->fontItalicAction, SIGNAL( triggered() ), SLOT( setItalicText() ) );

}

void MenuComponents::addFileActions(QWidget *menu)
{
    menu->addAction(this->newAction);
    menu->addAction(this->openAction);
    menu->addAction(this->saveAction);
    menu->addAction(this->saveAsAction);
}

void MenuComponents::addEditActions(QWidget *menu)
{
    menu->addAction(this->cutAction);
    menu->addAction(this->copyAction);
    menu->addAction(this->pasteAction);
    menu->addAction(this->deleteAction);
}

void MenuComponents::addFontActions(QWidget *menu)
{
    menu->addAction(this->fontTypeAction);
    menu->addAction(this->fontSizeAction);
    menu->addAction(this->fontBoldAction);
    menu->addAction(this->fontItalicAction);
}

void MenuComponents::addDropDawnFontActions(QMenu *menu)
{
    menu->addMenu(this->fontTypeMenu);
    menu->addMenu(this->fontSizeMenu);
    menu->addAction(this->fontBoldAction);
    menu->addAction(this->fontItalicAction);
}

void MenuComponents::addRecentFilesActions(QWidget *menu)
{
    for(int i = 0; i < MAX_RECENT_FILES; ++i)
        menu->addAction(this->recentFileActions[i]);
}

void MenuComponents::addExitAction(QWidget *menu)
{
    menu->addAction(this->exitAction);
}
void MenuComponents::createNewFile()
{
    qDebug() << "createNewFile";
}

void MenuComponents::showOpenMenu()
{
    qDebug() << "showOpenMenu";
}

void MenuComponents::saveInCurrentFile()
{
    qDebug() << "saveInCurrentFile";
}

void MenuComponents::showSaveMenu()
{
    qDebug() << "showSaveMenu";
}

void MenuComponents::openRecentFile()
{
    qDebug() << "openRecentFile";
}

void MenuComponents::cutText()
{
    qDebug() << "cutText";
}

void MenuComponents::copyText()
{
    qDebug() << "copyText";
}

void MenuComponents::pasteText()
{
    qDebug() << "pasteText";
}

void MenuComponents::deleteText()
{
    qDebug() << "deleteText";
}

void MenuComponents::changeFontType()
{
    qDebug() << "changeFontType";
}

void MenuComponents::changeFontSize()
{
    qDebug() << "changeFontSize";
}

void MenuComponents::setBoldText()
{
    qDebug() << "setBoldText";
}

void MenuComponents::setItalicText()
{
    qDebug() << "setItalicText";
}

