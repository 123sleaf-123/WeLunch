#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

//链表节点类型定义
struct LinkNode
{
    int date;
    struct LinkNode *next;

};  

//创建判断函数
struct LinkNode text2 (struct LinkNode * LNode,int i//传入菜品ID：i)  //数据库传过来的头指针,这是个函数
{

    // if (NULL==LNode)
    // {
    //     return;
    // }
    //建立新的链表
    struct LinkNode *header= (struct LinkNode *)malloc(sizeof(struct LinkNode *));
    header->date=0;
    header->next=NULL;
    struct LinkNode *weibu= header;//建立尾部指针

    //建立负责遍历的辅助指针pCurrent
    struct LinkNode *pCurrent = LNode->next;
    while (pCurrent != NULL)
    {
        if (pCurrent->date=i)
        {
            header->date=pCurrent->date;
            header->next=NULL;
            weibu->next=header;
            weibu =header;
            printf("%d\t",header->date);//检验是否分好
        }
        
        pCurrent= pCurrent->next;
    }
    
    return*header;



}
