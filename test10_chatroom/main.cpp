#include "mainwindow.h"
#include <QApplication>
#include "logindialog.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    LoginDialog l;
    l.show();
    return a.exec();
}
