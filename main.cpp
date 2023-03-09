#include "mainwindow.h"

#include "systemdatabase.h"
#include "logindialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SystemDataBase db;
    LoginDialog lg;
    if(lg.exec() == QDialog::Rejected){
        exit(0);
    }
    MainWindow w;
    w.setUser(lg.id_user);
    w.show();
    return a.exec();
}
