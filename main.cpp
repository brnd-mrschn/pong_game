#include "menuwindow.h"

    int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MenuWindow menuWindow;
    menuWindow.show();
    return a.exec();
}
