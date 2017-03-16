#ifndef EDITTOOLBAR_H
#define EDITTOOLBAR_H

#include <QToolBar>
#include <QSizePolicy>

#include "MenuComponents.h"

class EditToolBar : public QToolBar
{
    Q_OBJECT

public:
    explicit EditToolBar(MenuComponents * components, QWidget *parent = Q_NULLPTR);
    ~EditToolBar();

protected:
    void createToolBar();

private:
    //QToolBar *toolBar;
    MenuComponents *components;

};


#endif
