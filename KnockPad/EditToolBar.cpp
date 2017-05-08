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


void EditToolBar::changeToolBarFonts(const QFont& f)
{
    sizeBox->setCurrentText(QString::number(f.pointSize()));
    fontBox->setCurrentText(f.family());
}


void EditToolBar::createToolBar()
{
    components->addFileActions(this);
    this->addSeparator();
    components->addEditActions(this);
    this->addSeparator();

    fontBox->addItems(components->getFontList());
    this->addWidget(fontBox);
    fontBox->setCurrentIndex(3);

    sizeBox->addItems(components->getFontSizeList());
    addWidget(sizeBox);
    sizeBox->setEditable(true);
    sizeBox->setCurrentIndex(3);

    addAction(components->fontBoldAction);
    addAction(components->fontItalicAction);
}
