#include "KnockPad.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    KnockPad knock_pad;
    knock_pad.show();

    return app.exec();
}
