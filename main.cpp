#include "pongwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PongWindow w;
    w.show();
    return a.exec();
}
