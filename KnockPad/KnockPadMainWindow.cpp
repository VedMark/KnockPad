
#include "KnockPadMainWindow.h"

KnockPadMainWindow::KnockPadMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->createMenu();
    this->createToolBar();
    this->createContextMenu();
    //this->createTextField();


    //this->setWindowIcon();
}

KnockPadMainWindow::~KnockPadMainWindow()
{
    delete fileMenu;
    delete contextMenu;
    delete editMenu;

    delete toolBar;

    //delete textField;
}

void KnockPadMainWindow::createMenu()
{
    this->fileMenu = menuBar()->addMenu("&file");
    menuComponents.addFileActions(this->fileMenu);

    this->fileMenu->addSeparator();
    menuComponents.addRecentFilesActions(this->fileMenu);
    this->fileMenu->addSeparator();
    menuComponents.addExitAction(this->fileMenu);

    this->editMenu = menuBar()->addMenu("&edit");
    menuComponents.addEditActions(this->editMenu);
    this->fileMenu->addSeparator();
    menuComponents.addDropDawnFontActions(this->editMenu);

}

void KnockPadMainWindow::createToolBar()
{
    this->toolBar = new QToolBar(this);
    this->toolBar->resize(600, 50);

    menuComponents.addFileActions(this->toolBar);
    this->toolBar->addSeparator();
    menuComponents.addEditActions(this->toolBar);
    this->toolBar->addSeparator();
    menuComponents.addFontActions(this->toolBar);

}

void KnockPadMainWindow::createContextMenu()
{
    this->contextMenu = new QMenu(this);

    menuComponents.addFileActions(this->contextMenu);
    this->contextMenu->addSeparator();
    menuComponents.addEditActions(this->contextMenu);
    this->contextMenu->addSeparator();
    menuComponents.addDropDawnFontActions(this->contextMenu);
}

void KnockPadMainWindow::createTextField()
{
    this->textField = new TextField(this, 0, 0, 1366, 768);
    QPalette palette = textField->palette();
    palette.setColor(QPalette::Active, QPalette::Base, Qt::cyan);
    palette.setColor(QPalette::Active, QPalette::Text, Qt::black);
    textField->setPalette(palette);
}

void KnockPadMainWindow::contextMenuEvent(QContextMenuEvent* mouse_pointer)
{
    this->contextMenu->exec(mouse_pointer->globalPos());
}
