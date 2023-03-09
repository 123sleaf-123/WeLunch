#include "LoginInputCheck.h"


int checkId(char* temid, char* tempassword,struct Account* head)
{
    char *p1=NULL;
    char *p2=NULL;
    int answer = false;
    struct Account *pmove = head;
    while (pmove != NULL)
    {
        p1=&(pmove->id[0]);
        p2=&(pmove->password[0]);
        if (strcmp(temid,p1)==0 && strcmp(tempassword,p2)==0)
            answer = true;
        pmove = pmove->next;
    };
    return answer;
}

QSqlQuery *getDataFromDatabase(QString id_user){
    QSqlQuery q;
    q.prepare("select realname,pwd from user where id_user = :user");
    q.bindValue(":user",id_user);
    q.exec();
    q.next();

}


