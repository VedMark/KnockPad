#include "Menu.h"

Menu::Menu(MenuComponents *components, QWidget *parent)
    : QMenuBar(parent)
{
    this->components = components;
    fileMenu = new QMenu(tr("file"), this) ;
    editMenu = new QMenu(tr("edit"), this);
    contextMenu = new QMenu(this);
    createMenu();
    createContextMenu();
}

Menu::~Menu()
{
    delete fileMenu;
    delete editMenu;
    delete contextMenu;
}

void Menu::createMenu()
{
    components->addFileActions(fileMenu);
    fileMenu->addSeparator();
    components->addRecentFilesActions(fileMenu);
    fileMenu->addSeparator();
    components->addExitAction(fileMenu);
    this->addMenu(fileMenu);

    components->addEditActions(editMenu);
    editMenu->addSeparator();
    components->addDropDawnFontActions(editMenu);
    this->addMenu(editMenu);
}

void Menu::createContextMenu()
{
    components->addFileActions(contextMenu);
    contextMenu->addSeparator();
    components->addEditActions(contextMenu);
    contextMenu->addSeparator();
    components->addDropDawnFontActions(contextMenu);
}

QMenu* Menu::getContextMenu() const
{
    return contextMenu;
}
