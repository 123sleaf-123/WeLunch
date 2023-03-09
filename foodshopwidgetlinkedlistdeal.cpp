#include "foodshopwidgetlinkedlistdeal.h"

FoodShopWidgetLinkedListDeal::FoodShopWidgetLinkedListDeal()
{
    head = createLinkedList(queryDRInfo());
    ShowListHead = head;
//    head = orderbyScore(head);
}

QSqlQuery *FoodShopWidgetLinkedListDeal::queryDRInfo(){
    QSqlQuery * q = new QSqlQuery;
    q->exec("select * from DRinfo");
    return q;
}

DRList FoodShopWidgetLinkedListDeal::createLinkedList(QSqlQuery *q){
    DRList head;
    DRList cur;
    DRList pre;
    int i = 0;
    score = 0.0;
    sales = 0.0;
    speed = 0.0;
    length = 0;
    for(; q->next(); i++){
        DRList PtrL = (DRList)malloc(sizeof(struct DRNode));
        qDebug("111");
        Id_DR = q->value(0).toString();
        DRName = q->value(1).toString();
        DRType = q->value(2).toInt();
        DRLog = q->value("longitude").toString();
        DRLat = q->value("latitude").toString();
        DRImagePath = q->value("ImagePath").toString();
        DRSales = q->value("salesVolume").toInt();
        DRgrade = q->value("rating").toFloat();
        DRAvgDeliveryTime = q->value("speed").toTime();
        compensate = q->value("compensate").toBool();
        redPacket = q->value("redPacket").toBool();
        rebate = q->value("rebate").toBool();
        freeShipping = q->value("freeShipping").toBool();
        Id_Owner = q->value("Id_user").toString();

        strcpy(PtrL->Id_DR,Id_DR.toStdString().c_str());
        strcpy(PtrL->DRName,DRName.toStdString().c_str());
        PtrL->DRType = DRType;

        strcpy(PtrL->DRLog,DRLog.toStdString().c_str());
        strcpy(PtrL->DRLat,DRLat.toStdString().c_str());
        char userLog[20] = "E116.35023";
        char userLat[20] = "N39.794502";
        Distance = distance(userLat,userLog,PtrL->DRLat,PtrL->DRLog);
        PtrL->Disatance =Distance;

        strcpy(PtrL->DRImagePath,DRImagePath.toStdString().c_str());
        PtrL->DRSales = DRSales;
        PtrL->DRgrade = DRgrade;
        Speed = DRAvgDeliveryTime.toString("hh:mm");
        strcpy(PtrL->DRAvgDeliveryTime,Speed.toStdString().c_str());
        strcpy(PtrL->Id_Owner,Id_Owner.toStdString().c_str());
        PtrL->compensate = compensate;
        PtrL->redPacket = redPacket;
        PtrL->rebate = rebate;
        PtrL->freeShipping = freeShipping;
        PtrL->next = NULL;
        sales += DRSales;
        score += DRgrade;
        speed += second(PtrL->DRAvgDeliveryTime);
        if(i == 0){
            head = cur = pre = PtrL;
            length++;
        }
        else{
            cur = PtrL;
            pre->next = cur;
            pre = cur;
            length++;
        }
    }
    return head;
}

FoodShopWidgetLinkedListDeal::~FoodShopWidgetLinkedListDeal(){
    DRList PtrL;
    while(head->next){
        PtrL = head;
        head = head->next;
        free(PtrL);
    }
    free(head);
    qDebug("链表释放完毕");
}

// 输入经纬度计算距离，误差50米
double FoodShopWidgetLinkedListDeal::distance(char *latCusAngle,char *lonCusAngle,char *latResAngle,char *lonResAngle)
{
    char ch1[20],ch2[20],ch3[20],ch4[20];
    double latCustomer,lonCustomer,latRestaurant,lonRestaurant;
    const double pai=3.141593;
    double d;
    int longer1,longer2,longer3,longer4;
    longer1 = strlen(latCusAngle);
    longer2 = strlen(lonCusAngle);
    longer3 = strlen(latResAngle);
    longer4 = strlen(lonResAngle);
    int i;
    double num1,num2,num3,num4;
    for(i = 1 ; i < longer1 ; i++)
        {
        ch1[i-1]=latCusAngle[i];
        }
        num1=atof(ch1);
    for(i = 1 ; i < longer2 ; i++)
        {
        ch2[i-1]=lonCusAngle[i];
        }
        num2=atof(ch2);
    for(i = 1 ; i < longer3 ; i++)
        {
        ch3[i-1]=latResAngle[i];
        }
        num3=atof(ch3);
    for(i = 1 ; i < longer4 ; i++)
        {
        ch4[i-1]=lonResAngle[i];
        }
        num4=atof(ch4);
    if (latCusAngle[0]=='N')
       {
       latCustomer=pai*num1/180;
       }
       else
       {
       latCustomer=-pai*num1/180;
       }

    if (lonCusAngle[0]=='E')
       {
       lonCustomer=pai*num2/180;
       }
       else
       {
        lonCustomer=-pai*num2/180;
       }
    if (latResAngle[0]=='N')
        {
        latRestaurant=pai*num3/180;
        }
        else
        {
         latRestaurant=-pai*num3/180;
        }
    if  (lonResAngle[0]=='E' )
        {
        lonRestaurant=pai*num4/180;
        }
        else
        {
        lonRestaurant=-pai*num4/180;
        }
    int a=6378137;
    //地球长半轴 .
    int b=6356755;
    //地球短半轴
    double c,e,dCus,NCus,fCus,mueCus,lambdaCus,xCus,yCus,dRes,NRes,fRes,mueRes,lambdaRes,xRes,yRes,distance;
    c=pow(a,2)-pow(b,2);
    e=sqrt(c)/a;
    //椭圆第一偏心率
    dCus=1-pow(e*sin(latCustomer),2);
    NCus=a/sqrt(dCus);
    //客户点卯酉圈曲率半径
    fCus=NCus*(1-pow(e,2));
    mueCus=fCus/dCus;
    //客户点子午圈曲率半径
    lambdaCus=NCus*cos(latCustomer);
    //客户点平行圈曲率半径
    xCus=mueCus*lonCustomer;
    yCus=lambdaCus*latCustomer;
    dRes=1-pow(e*sin(latRestaurant),2);
    NRes=a/sqrt(dRes);
    //商家点卯酉圈曲率半径
    fRes=NRes*(1-pow(e,2));
    mueRes=fRes/dRes;
    //商家点子午圈曲率半径
    lambdaRes=NRes*cos(latRestaurant);
    //商家点平行圈曲率半径
    xRes=mueRes*lonRestaurant;
    yRes=lambdaRes*latRestaurant;   
    d=sqrt(abs(pow(xCus-xRes,2)-pow(yCus-yRes,2)));
    return d;
}

//struct DRNode *FoodShopWidgetLinkedListDeal::dietSelect (struct DRNode * LNode,int i/*传入菜品ID：i*/)  //数据库传过来的头指针,这是个函数
//{

//    if (NULL==LNode ||i==0)
//    {
//        return LNode;
//    }
//    //建立新的链表
//    struct DRNode *header= (struct DRNode *)malloc(sizeof(struct DRNode *));
//    // header->DRType=0;
//    header->next=NULL;
//    struct DRNode *tail= header;//建立尾部指针
//    tail->next=NULL;

//    //建立负责遍历的辅助指针pCurrent
//    struct DRNode *pCurrent = LNode;
//    //建立新节点
//    struct DRNode *newNode= (struct DRNode *)malloc(sizeof(struct DRNode *));
//    while (pCurrent != NULL)
//    {
//        if (pCurrent->DRType==i)
//        {
//            //为新节点赋值
//            newNode=pCurrent;
//            newNode->next=NULL;
//            //新节点插入到链表中
//            tail->next=newNode;
//            //更新尾部指针指向
//            tail=newNode;
//        }

//        pCurrent= pCurrent->next;
//    }

//    return header;
//}

struct DRNode *FoodShopWidgetLinkedListDeal::orderbySales(struct DRNode* head) //按餐馆分数从高到低排序
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
            if (p->DRSales < p1->DRSales)
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

int checkString(char* s1, char* s2)
{
    char* p;
    if (strlen(s1) > strlen(s2))
    {
        if ((p = strstr(s1, s2)) == NULL)
            return 0;
        else
            return 1;
    }
    else
    {
        if ((p = strstr(s2, s1)) == NULL)
            return 0;
        else
            return 1;
    }
}

struct DRNode* searchGoodName(char* good, struct DRNode* head)//输入搜索内容字符串以及储存信息链表头指针
{
    struct DRNode* pmove = head;//需要链表头指针(储存餐馆信息链表)
    struct DRNode* newhead = (struct DRNode*)malloc(sizeof(struct DRNode));
    strcpy(newhead->DRName, QString("").toStdString().c_str());
    newhead->next = NULL;
    struct DRNode* newpmove = newhead;
    int i = 0;
    while (pmove != NULL)
    {
        qDebug("循环了");
        if (checkString(pmove->DRName, good) == 1)
        {
            if(i == 0){
                newhead = pmove;
                i++;
            }
            newpmove->next=pmove;
            newpmove=newpmove->next;
            newpmove->next = NULL;
            i++;
        }
        pmove = pmove->next;
    }

    // 如果从未赋值就返回NULL
    if(i == 0){
        free(newhead);
        return NULL;
    }
    return newhead;//返会符合搜索要求的链表首个节点指针
}


int second(char *t)
{
    char ch1[3],ch2[3];
    int i,hour,minute,second;
    for(i=0;i<2;i++)
    {
        ch1[i]=t[i];
        ch2[i]=t[i+3];
    }
    ch1[i]='\0';
    ch2[i]='\0';
    hour=atoi(ch1);
    minute=atoi(ch2);
    second=hour*3600+minute*60;
    return second;
}

struct DRNode *FoodShopWidgetLinkedListDeal::orderbySpeed(struct DRNode *head) //按餐馆送餐速度从快到慢排序
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
            if (second(p->DRAvgDeliveryTime) > second(p1->DRAvgDeliveryTime))
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

DRList dietSelect (struct DRNode * LNode,int i/*传入菜品ID：i*/)
{

     if (NULL==LNode ||i==0)
     {
         return LNode;
     }
    //建立新的链表
    struct DRNode* header= (struct DRNode*)malloc(sizeof(struct DRNode));
    // header->DRType=0;
    header->next=NULL;

    //建立负责遍历的辅助指针pCurrent
    struct DRNode *pCurrent = LNode;
    int j=0;
    DRList *newNode;
    while (pCurrent != NULL)
    {
        if (pCurrent->DRType==i)
        {
            j++;
            switch (j)
            {
                case 1:
                {   *header=*pCurrent;
                    header->next=NULL;
                    j=2;
                    break;
                }
                default:
                {    //建立新节点
                    struct DRNode *newNode =(struct DRNode *)malloc(sizeof(struct DRNode));
                    *newNode=*pCurrent;
                    newNode->next=header->next;
                    header->next=newNode;
                    break;
                }
            }
        }
        pCurrent= pCurrent->next;
        if(!pCurrent){
            break;
        }

    }


    return header;


}

struct DRNode* searchInDistance(double distance, struct DRNode* LNode)//输入搜索内容字符串以及储存信息链表头指针
{
    if (NULL==LNode || distance == 0.0)
    {
        return LNode;
    }
   //建立新的链表
   struct DRNode* header= (struct DRNode*)malloc(sizeof(struct DRNode));
   // header->DRType=0;
   header->next=NULL;

   //建立负责遍历的辅助指针pCurrent
   struct DRNode *pCurrent = LNode;
   int j=0;
   DRList *newNode;
   while (pCurrent != NULL)
   {
       if (pCurrent->Disatance < distance)
       {
           j++;
           switch (j)
           {
               case 1:
               {   *header=*pCurrent;
                   header->next=NULL;
                   j=2;
                   break;
               }
               default:
               {    //建立新节点
                   struct DRNode *newNode =(struct DRNode *)malloc(sizeof(struct DRNode));
                   *newNode=*pCurrent;
                   newNode->next=header->next;
                   header->next=newNode;
                   break;
               }
           }
       }
       pCurrent= pCurrent->next;
       if(!pCurrent){
           break;
       }

   }


   return header;
}

DRList CompensateOnly (struct DRNode * LNode) //筛选是否赔付
{
     if (NULL==LNode)
     {
         return LNode;
     }
    //建立新的链表
    struct DRNode* header= (struct DRNode*)malloc(sizeof(struct DRNode));
    // header->DRType=0;
    header->next=NULL;

    //建立负责遍历的辅助指针pCurrent
    struct DRNode *pCurrent = LNode;
    int j=0;
    DRList *newNode;
    while (pCurrent != NULL)
    {
        if (pCurrent->compensate == 1)
        {
            j++;
            switch (j)
            {
                case 1:
                {   *header=*pCurrent;
                    header->next=NULL;
                    j=2;
                    break;
                }
                default:
                {    //建立新节点
                    struct DRNode *newNode =(struct DRNode *)malloc(sizeof(struct DRNode));
                    *newNode=*pCurrent;
                    newNode->next=header->next;
                    header->next=newNode;
                    break;
                }
            }
        }
        pCurrent= pCurrent->next;
        if(!pCurrent){
            break;
        }

    }
    if(j == 0){
        return NULL;
    }
    return header;
}

// 筛选是否返券
DRList rebateOnly (struct DRNode * LNode){
    if (NULL==LNode)
    {
        return LNode;
    }
   //建立新的链表
   struct DRNode* header= (struct DRNode*)malloc(sizeof(struct DRNode));
   // header->DRType=0;
   header->next=NULL;

   //建立负责遍历的辅助指针pCurrent
   struct DRNode *pCurrent = LNode;
   int j=0;
   DRList *newNode;
   while (pCurrent != NULL)
   {
       if (pCurrent->rebate == 1)
       {
           j++;
           switch (j)
           {
               case 1:
               {   *header=*pCurrent;
                   header->next=NULL;
                   j=2;
                   break;
               }
               default:
               {    //建立新节点
                   struct DRNode *newNode =(struct DRNode *)malloc(sizeof(struct DRNode));
                   *newNode=*pCurrent;
                   newNode->next=header->next;
                   header->next=newNode;
                   break;
               }
           }
       }
       pCurrent= pCurrent->next;
       if(!pCurrent){
           break;
       }
   }
   if(j == 0){
       return NULL;
   }
   return header;
}

// 筛选是否有红包
DRList ReadpacketOnly (struct DRNode * LNode){
    if (NULL==LNode)
    {
        return LNode;
    }
   //建立新的链表
   struct DRNode* header= (struct DRNode*)malloc(sizeof(struct DRNode));
   // header->DRType=0;
   header->next=NULL;

   //建立负责遍历的辅助指针pCurrent
   struct DRNode *pCurrent = LNode;
   int j=0;
   DRList *newNode;
   while (pCurrent != NULL)
   {
       if (pCurrent->redPacket == 1)
       {
           j++;
           switch (j)
           {
               case 1:
               {   *header=*pCurrent;
                   header->next=NULL;
                   j=2;
                   break;
               }
               default:
               {    //建立新节点
                   struct DRNode *newNode =(struct DRNode *)malloc(sizeof(struct DRNode));
                   *newNode=*pCurrent;
                   newNode->next=header->next;
                   header->next=newNode;
                   break;
               }
           }
       }
       pCurrent= pCurrent->next;
       if(!pCurrent){
           break;
       }

   }
   if(j == 0){
       return NULL;
   }
   return header;
}

// 筛选是否免运费
DRList FreeFareOnly (struct DRNode * LNode){
    if (NULL==LNode)
    {
        return LNode;
    }
   //建立新的链表
   struct DRNode* header= (struct DRNode*)malloc(sizeof(struct DRNode));
   // header->DRType=0;
   header->next=NULL;

   //建立负责遍历的辅助指针pCurrent
   struct DRNode *pCurrent = LNode;
   int j=0;
   DRList *newNode;
   while (pCurrent != NULL)
   {
       if (pCurrent->freeShipping == 1)
       {
           j++;
           switch (j)
           {
               case 1:
               {   *header=*pCurrent;
                   header->next=NULL;
                   j=2;
                   break;
               }
               default:
               {    //建立新节点
                   struct DRNode *newNode =(struct DRNode *)malloc(sizeof(struct DRNode));
                   *newNode=*pCurrent;
                   newNode->next=header->next;
                   header->next=newNode;
                   break;
               }
           }
       }
       pCurrent= pCurrent->next;
       if(!pCurrent){
           break;
       }

   }
   if(j == 0){
       return NULL;
   }
   return header;
}

//int second(char *t)
//{
//    char ch1[3],ch2[3];
//    int i,hour,minute,second;
//    for(i=0;i<2;i++)
//    {
//        ch1[i]=t[i];
//        ch2[i]=t[i+3];
//    }
//    ch1[i]='\0';
//    ch2[i]='\0';
//    hour=atoi(ch1);
//    minute=atoi(ch2);
//    second=hour*3600+minute*60;
//    return second;
//}

