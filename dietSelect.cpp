#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

//����ڵ����Ͷ���
struct LinkNode
{
    int date;
    struct LinkNode *next;

};  

//������֪�����������
struct LinkNode *create()
{
    struct LinkNode *phead; //����ͷ���
    
    phead =(struct LinkNode *)malloc(sizeof(struct LinkNode *));//�����ڴ�ռ�
    phead->date=0;
    phead->next=NULL;//��ָ��

    struct LinkNode *hear= phead; //βָ��

    int val =-1;
    while (true)
    {
        printf("������������:\n");
        scanf("%d",&val);
        if (val==-1)
        {
            break;
        }           
    }
    //Ϊ�½ڵ㸳ֵ
    struct LinkNode *newnode= (struct LinkNode *)malloc(sizeof(struct LinkNode *));
    newnode->date= val;
    newnode->next=NULL;
    //����β��ָ��ָ��
    hear->next =newnode;
    hear=newnode;
    return newnode;
}

//�����жϺ���
struct LinkNode text2 (struct LinkNode * LNode,int i/*�����ƷID��i*/)  //���ݿ⴫������ͷָ��,���Ǹ�����
{

    // if (NULL==LNode)
    // {
    //     return;
    // }
    //�����µ�����
    struct LinkNode *header= (struct LinkNode *)malloc(sizeof(struct LinkNode *));
    header->date=0;
    header->next=NULL;
    struct LinkNode *weibu= header;//����β��ָ��

    //������������ĸ���ָ��pCurrent
    struct LinkNode *pCurrent = LNode->next;
    while (pCurrent != NULL)
    {
        if (pCurrent->date=i)
        {
            header->date=pCurrent->date;
            header->next=NULL;
            weibu->next=header;
            weibu =header;
            printf("%d\t",header->date);//�����Ƿ�ֺ�
        }
        
        pCurrent= pCurrent->next;
    }
    
    return*header;



}


int main()
{
    int j;
    struct LinkNode *hahaha;
    printf("��ѡ����Ҫ����Ĳ�ϵ��\n");
    printf("0.³��\t1.����\t2.����\n");
    scanf("%d",&j);
    hahaha=create();
    text2(hahaha,j);

    return 0;
}