#include "KnockPadMainWindow.h"

int main(int argc, char *argv[])
{
    QApplication knock_pad(argc, argv);
    KnockPadMainWindow knock_pad_main_window;
    knock_pad_main_window.setWindowTitle("KnockPad");

   /* QMenuBar mnuBar;
    QMenu* pmnu = new QMenu("&File");
    QAction *New = new QAction("&New",
                               &knock_pad
                               );
    QObject::connect(&knock_pad, SIGNAL( triggered() ), &knock_pad, SLOT(aboutQt()));
    New->setIcon(QIcon(":/images/save.png"));
    pmnu->addAction(New);
    mnuBar.addMenu(pmnu);
    mnuBar.show();*/

    knock_pad_main_window.resize(1366, 768);
    knock_pad_main_window.show();
    return knock_pad.exec();
}
