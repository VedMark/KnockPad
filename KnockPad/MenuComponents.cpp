#include "MenuComponents.h"

MenuComponents::MenuComponents(QWidget *parent)
    : QWidget(parent)
{
    createFileActions();
    createEditActions();
    createFontActions();
    this->fontTypeMenu = new QMenu(tr("Font"), this);
    this->fontSizeMenu = new QMenu(tr("Size"), this);

    fonts << "Arial" << "Helvetica" << "Monospace" << "Times New Roman";

    fontSizes << "4" << "8" << "12" << "14" << "16" << "18" << "20"
              << "24" << "28" << "32" << "36" << "40" << "48" << "56"
              << "64" << "72" << "80" << "88" << "96";
}

MenuComponents::~MenuComponents()
{
}

void MenuComponents::createFileActions()
{
    this->newAction = new QAction(tr("New"), this);
    this->newAction->setIcon(QIcon(":/images/new.png"));
    this->newAction->setShortcut(QKeySequence::New);

    this->openAction = new QAction(tr("Open"), this);
    this->openAction->setIcon(QIcon(":/images/open.png"));
    this->openAction->setShortcut(QKeySequence::Open);

    this->saveAction = new QAction(tr("Save"), this);
    this->saveAction->setIcon(QIcon(":/images/save.png"));
    this->saveAction->setShortcut(Qt::CTRL + Qt::Key_S);
    this->saveAction->setStatusTip(tr("Save in current file"));

    this->saveAsAction = new QAction(tr("Save As"), this);
    this->saveAsAction->setShortcut(QKeySequence::SaveAs);

    for(int i = 0; i < MAX_RECENT_FILES; ++i)
    {
        this->recentFileActions[i] = new QAction(this);
        this->recentFileActions[i]->setVisible(false);
    }

    this->exitAction = new QAction(tr("Exit"), this);
    this->exitAction->setShortcut(QKeySequence::Quit);

}

void MenuComponents::createEditActions()
{
    this->cutAction = new QAction(tr("Cut"), this);
    this->cutAction->setIcon(QIcon(":/images/cut.png"));
    this->cutAction->setShortcut(QKeySequence::Cut);

    this->copyAction = new QAction("&Copy", this);
    this->copyAction->setIcon(QIcon(":/images/copy.png"));
    this->copyAction->setShortcut(QKeySequence::Copy);

    this->pasteAction = new QAction(tr("Paste"), this);
    this->pasteAction->setIcon(QIcon(":/images/paste.png"));
    this->pasteAction->setShortcut(Qt::CTRL + Qt::Key_V);

    this->deleteAction = new QAction(tr("Delete"), this);
    this->deleteAction->setIcon(QIcon(":/images/delete.png"));
    this->deleteAction->setShortcut(QKeySequence::Delete);
}

void MenuComponents::createFontActions()
{
    this->fontTypeAction = new QAction(tr("Font"), this);
    this->fontSizeAction = new QAction(tr("Size"), this);
    this->fontBoldAction = new QAction(tr("Bold"), this);
    this->fontItalicAction = new QAction(tr("Italics"), this);

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
