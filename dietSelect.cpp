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

//创建已知链表进行试验
struct LinkNode *create()
{
    struct LinkNode *phead; //创建头结点
    
    phead =(struct LinkNode *)malloc(sizeof(struct LinkNode *));//分配内存空间
    phead->date=0;
    phead->next=NULL;//空指针

    struct LinkNode *hear= phead; //尾指针

    int val =-1;
    while (true)
    {
        printf("输入插入的数据:\n");
        scanf("%d",&val);
        if (val==-1)
        {
            break;
        }           
    }
    //为新节点赋值
    struct LinkNode *newnode= (struct LinkNode *)malloc(sizeof(struct LinkNode *));
    newnode->date= val;
    newnode->next=NULL;
    //更新尾部指针指向
    hear->next =newnode;
    hear=newnode;
    return newnode;
}

//创建判断函数
struct LinkNode text2 (struct LinkNode * LNode,int i/*传入菜品ID：i*/)  //数据库传过来的头指针,这是个函数
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


int main()
{
    int j;
    struct LinkNode *hahaha;
    printf("请选择您要购买的菜系：\n");
    printf("0.鲁菜\t1.粤菜\t2.川菜\n");
    scanf("%d",&j);
    hahaha=create();
    text2(hahaha,j);

    return 0;
}