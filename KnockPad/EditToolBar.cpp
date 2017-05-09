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
    components->fontBoldAction->setChecked(f.bold());
    components->fontItalicAction->setChecked(f.italic());
}

void EditToolBar::createToolBar()
{
    components->addFileActions(this);
    addSeparator();
    components->addEditActions(this);
    addSeparator();

    fontBox->addItems(components->getFontList());
    addWidget(fontBox);
    fontBox->setCurrentText("Monospace");

    sizeBox->addItems(components->getFontSizeList());
    addWidget(sizeBox);
    sizeBox->setEditable(true);
    sizeBox->setCurrentText("14");

    addAction(components->fontBoldAction);
    addAction(components->fontItalicAction);
}
