#include<stdio.h>
#include<stdlib.h>
#include"smartorder.h"
struct DRNode *smartOrder(struct DRNode* head,int sale,float score,int speed) //智能排序
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
    float w,w1;
    for (i = 1; i < n; i++)
    {   
        p=L;
        for (j = 0; j < n - i; j++)
        {
            p1=p->next;
            w=p->DRSales*40/sale+p->DRgrade*40/score+(second(p->DRAvgDeliveryTime)-speed)*(-20)/speed;
                       w1=p1->DRSales*40/sale+p1->DRgrade*40/score+(second(p1->DRAvgDeliveryTime)-speed)*(-20)/speed;
            if (w < w1) 
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
