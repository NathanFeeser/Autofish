#include "autofish.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AutoFish w;
    w.show();

    return a.exec();
}
