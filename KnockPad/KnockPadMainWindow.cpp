
#include "KnockPadMainWindow.h"

KnockPadMainWindow::KnockPadMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //this->setWindowIcon();
}

KnockPadMainWindow::~KnockPadMainWindow()
{
    delete fileMenu;
    delete contextMenu;
    delete editMenu;

    delete toolBar;

}

void KnockPadMainWindow::createMenu(MenuComponents *menuComponents)
{
    this->fileMenu = menuBar()->addMenu("&file");
    menuComponents->addFileActions(this->fileMenu);

    this->fileMenu->addSeparator();
    menuComponents->addRecentFilesActions(this->fileMenu);
    this->fileMenu->addSeparator();
    menuComponents->addExitAction(this->fileMenu);

    this->editMenu = menuBar()->addMenu("&edit");
    menuComponents->addEditActions(this->editMenu);
    this->fileMenu->addSeparator();
    menuComponents->addDropDawnFontActions(this->editMenu);

}

void KnockPadMainWindow::createToolBar(MenuComponents *menuComponents)
{
    this->toolBar = new QToolBar(this);
    this->toolBar->resize(600, 50);

    menuComponents->addFileActions(this->toolBar);
    this->toolBar->addSeparator();
    menuComponents->addEditActions(this->toolBar);
    this->toolBar->addSeparator();
    menuComponents->addFontActions(this->toolBar);

}

void KnockPadMainWindow::createContextMenu(MenuComponents *menuComponents)
{
    this->contextMenu = new QMenu(this);

    menuComponents->addFileActions(this->contextMenu);
    this->contextMenu->addSeparator();
    menuComponents->addEditActions(this->contextMenu);
    this->contextMenu->addSeparator();
    menuComponents->addDropDawnFontActions(this->contextMenu);

    //connect(this->contextMenu, SIGNAL( triggered(QAction*) ), SLOT( slotActivated(QAction*) ) );
}

void KnockPadMainWindow::createTextField(TextField *textField)
{
    textField = new TextField(this);
    /*QPalette palette = palette(textField);
    palette.setColor(QPalette::Active, QPalette::Base, Qt::cyan);
    palette.setColor(QPalette::Active, QPalette::Text, Qt::black);
    textField->setPalette(palette);*/
}

void KnockPadMainWindow::contextMenuEvent(QContextMenuEvent* mouse_pointer)
{
    this->contextMenu->exec(mouse_pointer->globalPos());
}
/*
void KnockPadMainWindow::slotActivated(QAction* pAction)
{
    qDebug() << "ContextMenu activated";
}
*/
