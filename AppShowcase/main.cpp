#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    int r_val = 0;

    if (w.init()) {
        w.show();

        r_val = a.exec();
    }


    return r_val;
}
