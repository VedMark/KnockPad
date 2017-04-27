#ifndef EDITTOOLBAR_H
#define EDITTOOLBAR_H

#include <QComboBox>
#include <QToolBar>
#include <QSizePolicy>

#include "MenuComponents.h"

class EditToolBar : public QToolBar
{
    Q_OBJECT

public:
    explicit EditToolBar(MenuComponents * components, QWidget *parent = Q_NULLPTR);

    const QComboBox* getFontBox() const { return fontBox; }
    const QComboBox* getSizeBox() const { return sizeBox; }

    ~EditToolBar();

protected:
    void createToolBar();

private:
    MenuComponents *components;
    QComboBox *fontBox;
    QComboBox *sizeBox;
};


#endif
