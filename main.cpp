#include "mainwindow.h"
#include "intro.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    Intro i(&w);
    w.show();
    i.show();
    return a.exec();
}
