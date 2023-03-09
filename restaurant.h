#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <QString>
#include <QDate>
#include <QTime>

class Restaurant
{
public:
    Restaurant();
    bool IsCoupon(); // 是否有红包
    bool IsCouponAfterPurchased(); // 是否有返券
    bool IsReduceCarriage(); // 是否减免配送费

    // 获取值
    QString getDRId();
    QString getDRName();
    QString getDRType();
    QString getDateCreated();
    QString getDRCity();
    QString getDRLog();
    QString getDRLat();
    QString getTimeOpen();
    QString getTimeClose();
    int getCapacity();
    QString getDRIntroduction();
    QString getDRImagePath();
    int getBaseFare();
    int getDeliveryFee();
    int getDRSales();
    float getDRRating();
    int getDRTotalTakeOutOrderNum();
    int getDRTotalTakeOutOrderTime();
    int getDRAvgDeliveryTime();
    QString getId_Owner();

    // 设置值
    void setDRId(QString);
    void setDRName(QString);
    void setDRType(QString);
    void setDateCreated(QString);
    void setDRCity(QString);
    void setDRLog(QString);
    void setDRLat(QString);
    void setTimeOpen(QString);
    void setTimeClose(QString);
    void setCapacity(int);
    void setDRIntroduction(QString);
    void setDRImagePath(QString);
    void setBaseFare(int);
    void setDeliveryFee(int);
    void setDRSales(int);
    void setDRRating(float);
    void setDRTotalTakeOutOrderNum(int);
    void setDRTotalTakeOutOrderTime(int);
    void setDRAvgDeliveryTime(int);
    void setId_Owner(QString);

    // QString 转化为 char*
    char* QStringToChar(QString);

    // 设置展示卡片内容
    void setCard();

    // 绘制展示卡片
    void showCard();

    // 设置餐厅页面内容

protected:
    QString Id_DR;
    QString DRName;
    QString DRType;
    QString DateCreated;
    QString DRCity;
    QString DRLog;
    QString DRLat;
    QString TimeOpen;
    QString TimeClose;
    int Capacity; // 接待能力
    QString DRIntroduction;
    QString DRImagePath;
    int BaseFare; // 起送价
    int DeliveryFee; // 配送费
    int DRSales; // 餐厅销量
    float DRRating; // 餐厅评分
    int DRTotalTakeOutOrderNum; // 餐厅外卖订单总量
    int DRTotalTakeOutOrderTime; // 餐厅外卖订单总耗时
    int DRAvgDeliveryTime; // 餐厅配送速度
    QString Id_Owner;
    // RestaurantSearchCard *DisplayCard;
};
/*
    typedef struct DRNode *DRList;
    struct DRNode{
        Restaurant DR;
        struct DRNode *next;
    }
*/

#endif // RESTAURANT_H
