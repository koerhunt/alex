#include "mainwindow.h"
#include <QApplication>

//funcion principal
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();

}
