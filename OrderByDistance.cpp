#include "OrderByDistance.h"

struct DRNode *orderbyDistance(struct DRNode* head) //按餐馆分数从高到低排序
{
    struct DRNode*p3=head;
    int i,j,n,t,q;
    q=0;
    n = 1; //记录店铺总数；
    for (;p3->next!=NULL;p3=p3->next )
    {
        n++;
    }//计算n个数；
    struct DRNode *header=(struct DRNode*)malloc(sizeof(struct DRNode));
    struct DRNode *s=header;
    struct DRNode *node;

    for (int i = 0; i < n; i++) {
        node = (struct DRNode*)malloc(sizeof(struct DRNode));
        *node = *head;
        head=head->next;
        s->next=node;
        node->next=NULL;
        s = node;

    }//结束创建
    header=header->next;
    struct DRNode*p=header;
    struct DRNode*L=header;
    struct DRNode*p1;
    struct DRNode*p4=(struct DRNode*)malloc(sizeof(struct DRNode));
    struct DRNode*dz1=(struct DRNode*)malloc(sizeof(struct DRNode));
    struct DRNode*dz2=(struct DRNode*)malloc(sizeof(struct DRNode));

    for (i = 1; i < n; i++)
    {
        p=L;
        for (j = 0; j < n - i; j++)
        {
            p1=p->next;
            if (p->Disatance > p1->Disatance)
            {
                dz1->next=p->next;
                dz2->next=p1->next;
                *p4=*p;
                *p=*p1;
                *p1=*p4;
                p->next=dz1->next;
                p1->next=dz2->next;
            }
            p=p->next;
        }
    }
    return header;
}
