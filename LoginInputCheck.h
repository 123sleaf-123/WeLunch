#ifndef LOGININPUTCHECK_H
#define LOGININPUTCHECK_H

#include"LinkedListOptSet.h"
#include <QSqlQuery>
#include <string>

struct Account
{
    char id[20];
    char password[20];
    QString UserName;
    struct Account* next;
};

struct Account* getData(struct Account*);
int checkId(char* temid, char* tempassword);
QSqlQuery *getDataFromDatabase(QString);
List MakeList(QSqlQuery *);

#endif // LOGININPUTCHECK_H
