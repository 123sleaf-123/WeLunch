#ifndef FOODSHOPWIDGETLINKEDLISTDEAL_H
#define FOODSHOPWIDGETLINKEDLISTDEAL_H

#include <QSqlQuery>
#include <QTime>
#include <QChar>
#include "FoodShopWidgetOrderByScore.h"
#include "OrderByDistance.h"
#include "smartorder.h"

int second(char *t);
int checkString(char* s1,char* s2);
struct DRNode *searchGoodName(char *good,struct DRNode *head);
DRList dietSelect (DRList LNode,int i);
struct DRNode* searchInDistance(double distance, struct DRNode* head);
DRList CompensateOnly (struct DRNode * LNode);
DRList rebateOnly (struct DRNode * LNode);
DRList ReadpacketOnly (struct DRNode * LNode);
DRList FreeFareOnly (struct DRNode * LNode);

class FoodShopWidgetLinkedListDeal
{
public:
    FoodShopWidgetLinkedListDeal();
    ~FoodShopWidgetLinkedListDeal();
    QSqlQuery *queryDRInfo();
    DRList createLinkedList(QSqlQuery *q);
    double distance(char *latCusAngle,char *lonCusAngle,char *latResAngle,char *lonResAngle);
    struct DRNode *dietSelect (struct DRNode * LNode,int i/*传入菜品ID：i*/);
    struct DRNode *orderbySpeed(struct DRNode* head);
    struct DRNode *orderbySales(struct DRNode* head);
    struct DRNode *selectDistance(struct DRNode* head);
    int checkString(char* s1,char* s2);
    struct DRNode * searchGoodName(char *good,struct DRNode *head);

    QString Id_DR;
    QString DRName;
    int DRType;

    QString DRLog;
    QString DRLat;
    double Distance;

    QString DRImagePath;
    int DRSales;
    float DRgrade;

    QTime DRAvgDeliveryTime;
    QString Speed;

    QString Id_Owner;
    bool compensate;
    bool redPacket;
    bool rebate;
    bool freeShipping;

    DRList head;
    DRList ShowListHead;

    float score;
    float sales;
    float speed;
    int length;
};

#endif // FOODSHOPWIDGETLINKEDLISTDEAL_H
