#include "EditToolBar.h"

EditToolBar::EditToolBar(MenuComponents *components, QWidget *parent)
    : QToolBar(parent)
{
    this->components = components;
    fontBox = new QComboBox(this);
    sizeBox = new QComboBox(this);

    createToolBar();
}

EditToolBar::~EditToolBar()
{
    delete components;
    delete fontBox;
    delete sizeBox;
}

void EditToolBar::createToolBar()
{
    components->addFileActions(this);
    this->addSeparator();
    components->addEditActions(this);
    this->addSeparator();

    fontBox->addItems(components->getFontList());
    this->addWidget(fontBox);

    sizeBox->addItems(components->getFontSizeList());
    addWidget(sizeBox);
    sizeBox->setEditable(true);

    addAction(components->fontBoldAction);
    addAction(components->fontItalicAction);
}
