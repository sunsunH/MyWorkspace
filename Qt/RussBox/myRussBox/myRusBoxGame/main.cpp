#include "russboxwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RussBoxWidget w;
    w.show();

    return a.exec();
}
