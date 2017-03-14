#include "KnockPad.h"

int main(int argc, char *argv[])
{
    KnockPad knock_pad(argc, argv);
    return knock_pad.exec();
}
