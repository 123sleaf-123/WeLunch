#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define true 1
#define false 0
struct Account
{
    char id[20];
    char password[20];
    struct Account* next;
};

struct Account* getData()//将数据库以以上结构体链表形式储存，且head为表头指针
{
    struct Account* head;
    head = 
    return head;
}

int main()
{
    char temid[20]={0}, tempassword[20]={0};
    int checkId(char*, char*);
    printf("id:\n");
    scanf("%s", temid);//输入账号
    printf("password:\n");
    scanf("%s", tempassword);//输入密码
    printf("%d",checkId(temid, tempassword));
    return checkId(temid, tempassword);//合法返回1.非法返回0
}

int checkId(char* temid, char* tempassword)
{   
    char *p1=NULL;
    char *p2=NULL;
    struct Account* pmove;
    int answer = false;
    pmove =getData();
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



