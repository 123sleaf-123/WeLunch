#ifndef ORDERCARD_H
#define ORDERCARD_H

#include <QWidget>
#include <QSqlQuery>
#include "ordersubmitreceive.h"
#include <QTime>

namespace Ui {
class OrderCard;
}

class OrderCard : public QWidget
{
    Q_OBJECT

public:
    explicit OrderCard(QWidget *parent = nullptr);
    ~OrderCard();

    // 初始化阶段，继承使用者
    void setUser(QString id_user);
    void setOrder(QString id_order);

    // 初始化结束
    void setOrderCondition();
    void setText();
    void setupFoodCard(QSqlQuery *query);
    void isClosePayBtn();

    void queryDRId();
    void queryDRName();
    QSqlQuery *queryFoodId();
    void queryFoodName();
    void queryOrderCreateTime();
    void queryOrderCondition();
    void queryOwnerName();

    void queryUpdatePrice();


    float sum;
    int x;
    int y;
    int count = 0;
    int CardHeight;
    int status;

    QString id_order;
    QString id_DR;
    QString DRName;
    QString id_food;
    QString FoodName;
    QString OrderCreateTime;
    QString id_user;
    QString Realname;

    QTime *time;

    /*
     * Each one represents:
     * OrderPayCondition
     * OrderReceiveCondition
     * OrderFinishCondition
     * OrderCancelCondition
     */
    bool OrderConditions[4];
    QString OrderCondition;

    QSqlQuery query;

signals:
    void initEnd();

private:
    Ui::OrderCard *ui;

public slots:
    void setCard();
private slots:
    void on_GoTPayBtn_clicked();
    void on_finish_clicked();
    void on_receive_clicked();
    void on_cancel_clicked();
};

#endif // ORDERCARD_H
