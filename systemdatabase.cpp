#include "systemdatabase.h"
#include <QMessageBox>

SystemDataBase::SystemDataBase()
{
    SystemDataBase::connect();
}

bool SystemDataBase::connect(){
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("ofms");
    db.setUserName("MSINB");
    db.setPassword("123456");
    db.setPort(3306);

    if (db.open() == true)
    {
        qDebug("数据库OFMS.db连接成功");
        return true;
    }
    else
    {
        QMessageBox::critical(0, QObject::tr("数据库连接失败"), db.lastError().text());
        return false;
    }
}

void SystemDataBase::soureceFromSQL(){
    QSqlQuery q;
}
