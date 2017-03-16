#include "EditToolBar.h"

EditToolBar::EditToolBar(MenuComponents *components, QWidget *parent)
    : QToolBar(parent)
{
    this->components = components;

    createToolBar();
}

EditToolBar::~EditToolBar()
{
}

void EditToolBar::createToolBar()
{
    components->addFileActions(this);
    this->addSeparator();
    components->addEditActions(this);
    this->addSeparator();
    components->addFontActions(this);
}
