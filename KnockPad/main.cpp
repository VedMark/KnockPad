#include "KnockPadMainWindow.h"
#include "TextField.h"

int main(int argc, char *argv[])
{
    QApplication knock_pad(argc, argv);
    KnockPadMainWindow knock_pad_main_window;
    knock_pad_main_window.setWindowTitle("KnockPad");

    knock_pad_main_window.resize(1366, 768);
    knock_pad_main_window.show();
    return knock_pad.exec();
}
