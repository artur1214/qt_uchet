#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //a.setStyle("Fusion");
    DBManager::instance("db.sqlite");
    MainWindow w;
    w.show();

    //a.setStyleSheet();
    return a.exec();
}
