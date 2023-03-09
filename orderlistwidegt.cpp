#include "orderlistwidegt.h"
#include "ui_orderlistwidegt.h"
#include "ordercard.h"
#include <QRect>


OrderListWidegt::OrderListWidegt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderListWidegt)
{
    ui->setupUi(this);

    connect(this,&OrderListWidegt::initEnd,this,&OrderListWidegt::setCard);

}

void OrderListWidegt::setUser(QString id_user, int status){
    this->id_user = id_user;
    this->status = status;
    emit initEnd();
}

QSqlQuery * OrderListWidegt::queryOrderId_user(){
    QSqlQuery *query = new QSqlQuery;
    if(status == 2){
        query->prepare("select orderid from orders where id_user = :user order by OrderCreateTime desc");
        query->bindValue(":user",id_user);
        query->exec();
    }
    if(status == 1){
        QString id_DR;
        query->prepare("select DRID from drinfo where id_user = :user");
        query->bindValue(":user",id_user);
        query->exec();
        query->next();
        id_DR = query->value("DRID").toString();
        query->prepare("select orderid from orders where id_DR = :DR order by OrderPayTime desc");
        query->bindValue(":DR",id_DR);
        query->exec();
    }
    return query;
}


void OrderListWidegt::setupOrderCard(QSqlQuery *q){
    for (int i = 0 ; q->next() ; i++) {
        OrderCard *card = new OrderCard(this);
        card->setOrder(q->value("orderid").toString());
        card->resize(600,card->height());
        card->setUser(id_user);
        card->move(0,CurrentY);
        CurrentY += card->CardHeight;
    }
    this->resize(this->width(),CurrentY + 100);
}

void OrderListWidegt::setCard(){
    setupOrderCard(queryOrderId_user());
}

void OrderListWidegt::setSelectMode(int index){
    this->SelectMode = index;
}

OrderListWidegt::~OrderListWidegt()
{
    delete ui;
}


