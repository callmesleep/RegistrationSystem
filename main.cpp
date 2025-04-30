#include "mainwindow.h"
#include <QSqlQuery>
#include <QApplication>
int no=0;
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
