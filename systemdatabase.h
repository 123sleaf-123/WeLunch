#ifndef SYSTEMDATABASE_H
#define SYSTEMDATABASE_H

#include <QtSql>


class SystemDataBase
{
public:
    SystemDataBase();
    bool connect();
    void soureceFromSQL();
};

#endif // SYSTEMDATABASE_H
