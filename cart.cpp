#include "cart.h"
#include "ui_cart.h"

Cart::Cart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Cart)
{
    ui->setupUi(this);
    this->resize(600,1000);
}

Cart::~Cart()
{
    delete ui;
}

void Cart::queryCards(){
    QSqlQuery *q = new QSqlQuery;
    q->prepare("select id_DR from cart where id_user = :user group by id_DR");
    q->bindValue(":user",id_user);
    q->exec();
    this->q = q;
}

void Cart::setupCartCards(){
    int i;
//    QRect rect;
//    QSize size;
    int y = 50;
    for(i = 0 ; q->next() ; i++){
        CartCard *Ccard = new CartCard(this);
        Ccard->setUser(id_user);
        QString id_DR = q->value("id_DR").toString();
        Ccard->id_DR = id_DR;
        Ccard->queryDRName();
        Ccard->queryFood();
        Ccard->setupFood();
        Ccard->move(10,y);
        Ccard->show();
        y += Ccard->height();
    }
    if(i == 0){
        ui->createOrder->setEnabled(false);
    }
    this->resize(this->width(),y + 100);
    ui->createOrder->move(this->width() - 100, this->height() - 50);
}

void Cart::on_createOrder_clicked()
{
    QSqlQuery q;

    // 查找订单
    q.prepare("select id_DR from cart where id_user = :user AND selectMode = 1 group by id_DR");
    q.bindValue(":user",id_user);
    q.exec();

    // 创建订单
    for (OrderCount = 0; q.next() ; OrderCount++ ) {
        DRs[OrderCount] = q.value(0).toString();
        QSqlQuery query;
        query.prepare("insert into orders (Id_DR, Id_user) values (:DR,:user)");
        query.bindValue(":DR",DRs[OrderCount]);
        query.bindValue(":user",id_user);
        query.exec();

        // 查询购物车
        QSqlQuery q1;
        q1.prepare("select * from cart where id_user = :user AND selectMode = 1 AND id_DR = :DR");
        q1.bindValue(":user",id_user);
        q1.bindValue(":DR",DRs[OrderCount]);
        q1.exec();
        while (q1.next()) {
            // 查询订单号
            QSqlQuery q3;
            q3.prepare("select orderid from orders where Id_user = :user AND Id_DR = :DR order by OrderCreateTime desc");
            q3.bindValue(":DR",DRs[OrderCount]);
            q3.bindValue(":user",id_user);
            q3.exec();
//            int i = 0;
//            while (q3.next()) {
//                i++;
//            }
            q3.next();
            QString id_order = q3.value("orderid").toString();

            // 填入订单内容
            QString id_DR = q1.value("id_DR").toString();
            QString id_food = q1.value("id_food").toString();
            int number = q1.value("number").toInt();
            QSqlQuery q2;
            q2.prepare("insert into ordertofood (Id_order, Id_DR, Id_food, number) values (:a,:b,:c,:d)");
            q2.bindValue(":a",id_order);
            q2.bindValue(":b",id_DR);
            q2.bindValue(":c",id_food);
            q2.bindValue(":d",number);
            q2.exec();
        }
    }

    q.prepare("delete from cart where id_user = :user AND selectMode = 1");
    q.bindValue(":user",id_user);
    q.exec();
}

void Cart::createCheck(QString id_DR){
//    QSqlQuery q;
//    float money;
//    float Fare;
//    QTime *cur;
//    QTime *open,*close;

//    // 创建检查
//    q.prepare("select openTime,closeTime,capacity,BaseFare,Fare from DRINFo where DRID = :DR");
//    q.bindValue(":DR",id_DR);
//    q.exec();
//    q.next();
//    open = new QTime(q.value("openTime").toTime());
//    close = new QTime(q.value("closeTime").toTime());
//    cur = new QTime(QTime::currentTime());
//    Fare = q.value("Fare").toFloat();
//    float BaseFare = q.value("basefare").toFloat();
//    if(cur < open && cur > close){
//        QMessageBox::critical(nullptr,"创建订单失败","不在营业时间内");
//        return;
//    }
//    int capapcity = q.value("capacity").toInt();
//    int people;
//    q.prepare("select * from orders where id_DR = :DR");
//    q.bindValue(":DR",id_DR);
//    q.exec();
//    q.next();
//    for(people = 0; q.next();){
//        bool pay = q.value("OrderPayCondition").toBool();
//        bool receive = q.value("OrderReceiveCondition").toBool();
//        bool cancel = q.value("OrderCancelCondition").toBool();
//        if(pay && !receive && !cancel){
//            people++;
//        }
//    }
//    if(people >= capapcity){
//        QMessageBox::critical(nullptr,"创建订单失败","餐厅接待能力已到达上限");
//        return;
//    }
//    q.prepare("select money,password from user where id_user = :user");
//    q.bindValue(":user",id_user);
//    q.exec();
//    q.next();
//    money = q.value("money").toFloat();

//    if(sum < BaseFare){
//        QMessageBox::critical(nullptr,"创建订单失败","未达到起送价");
//        return;
//    }
}
