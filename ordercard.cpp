#include "ordercard.h"
#include "ui_ordercard.h"
#include "foodinordercard.h"
#include "systemdatabase.h"
#include <QDateTime>
#include "addcomment.h"
#include "paywidget.h"
#include <QTime>
#include <QMessageBox>

OrderCard::OrderCard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderCard)
{    
    ui->setupUi(this);
    sum = 0.0;
    connect(this,&OrderCard::initEnd,this,&OrderCard::setCard);

}

// 设置订单卡片所属订单id
void OrderCard::setOrder(QString id_order){
    this->id_order = id_order;
    if(!id_user.isEmpty()){
        emit initEnd();
    }
}

void OrderCard::setUser(QString id_user){
    this->id_user = id_user;
    if(id_user.contains("user")){
        status = 2;
    }
    else{
        status = 1;
        ui->horizontalLayoutWidget_2->hide();
    }
    if(!id_order.isEmpty()){
        emit initEnd();
    }
}

// 将bool类型存储的状态具体化成中文表达的状态
void OrderCard::setOrderCondition(){
    if(OrderConditions[3] == true){
        OrderCondition = "已取消";
    }
    else{
        if(OrderConditions[2] == true){
            OrderCondition = "已完成";
        }
        else{
            if(OrderConditions[1] == true){
                OrderCondition = "已收货";
            }
            else{
                if(OrderConditions[0] == true){
                    OrderCondition = "待收货";
                }
                else{
                    OrderCondition = "待付款";
                }
            }
        }
    }
}

// 设置订单卡片内容
void OrderCard::setText(){   

    // 设置订单号
    this->ui->orderCode->setText(id_order);

    // 设置订单创建时间
     this->ui->datetime->setText(OrderCreateTime);

    // 设置订单总金额
     this->ui->orderPayment->setText(QString("%1 ￥").arg(sum));

    // 设置餐厅店名
    this->ui->DRName->setText(DRName);

    // 设置订单状态
    this->ui->OrderCondition->setText(OrderCondition);
}

// 设置订单包含食物卡片
void OrderCard::setupFoodCard(QSqlQuery *query){
    for(count = 0 ; query->next() ; count++){
        // 设置食物卡片位置
        foodinordercard *card = new foodinordercard(this);
        card->move(10,100+count*150);

        // 设置卡片内容，并计算订单总金额
        sum += card->setText(id_user, id_order,id_DR, query->value(0).toString());
    }
    // count--;
    delete query;
}

// 设置是否关闭支付按钮
void OrderCard::isClosePayBtn(){
    if(!OrderConditions[0] && !OrderConditions[3]){
        this->ui->GoTPayBtn->setEnabled(true);
        this->ui->cancel->setEnabled(true);
    }
    else if(!OrderConditions[3] && !OrderConditions[1]){
        ui->receive->setEnabled(true);
    }
    else if(!OrderConditions[3] && !OrderConditions[2]){
        ui->finish->setEnabled(true);
    }
    int y = this->ui->horizontalLayoutWidget->height() + count * 150 + 40;
    CardHeight = y + 80;
    this->ui->horizontalLayoutWidget_2->move(300,y);
}

// 查询餐厅id
void OrderCard::queryDRId(){
//    QString str = QString("select id_DR from orders where orderid = %1").arg(id_order);
    query.prepare("select id_DR from orders where orderid = :a");
    query.bindValue(0,id_order);
    query.exec();
    query.next();
    id_DR = query.value(0).toString();
    query.clear();
}

// 查询餐厅名
void OrderCard::queryDRName(){

    query.prepare("select DRName from DRinfo where DRID = :a");
    query.bindValue(0,id_DR);
    query.exec();
    query.next();
    DRName = query.value(0).toString();
    query.clear();
}

// 查询菜品id
QSqlQuery *OrderCard::queryFoodId(){
    QSqlQuery *query = new QSqlQuery;
    query->prepare("select id_food from ordertofood where id_order = :a");
    query->bindValue(0,id_order);
    query->exec();
    return query;
}

void OrderCard::queryFoodName(){

}

// 查询订单创建时间
void OrderCard::queryOrderCreateTime(){
    query.prepare("select OrderCreateTime from orders where orderid = :a");
    query.bindValue(0,id_order);
    query.exec();
    query.next();
    QDateTime time = query.value(0).toDateTime();
    OrderCreateTime = time.toString("yyyy-MM-dd hh:mm:ss");
    query.clear();
}

void OrderCard::queryOrderCondition(){
    query.prepare("select OrderPayCondition, OrderReceiveCondition, OrderFinishCondition, OrderCancelCondition from orders where orderid = :order");
    query.bindValue(":order",id_order);
    query.exec();
    query.next();
    for ( int i = 0 ; i < 4 ; i++ ) {
        OrderConditions[i] = query.value(i).toBool();
    }
    query.clear();
}

void OrderCard::queryOwnerName(){
    query.prepare("select realname from user where id_user = :user");
    query.bindValue(":user",id_user);
    query.exec();
    query.next();
    Realname = query.value("realname").toString();
    this->ui->RealName->setText(Realname);
}

void OrderCard::queryUpdatePrice(){
    query.prepare("update orders set price = :sum where orderid = :order");
    query.bindValue(":sum",sum);
    query.bindValue(":order",id_order);
    query.exec();
}

void OrderCard::setCard(){
    // 设置订单卡片大小
//    this->resize(parent->size());
//    this->ui->horizontalLayoutWidget->move(0,0);
    this->ui->horizontalLayoutWidget->resize(this->width(),150);

    x = this->QWidget::x();
    y = ui->horizontalLayoutWidget->y() + ui->horizontalLayoutWidget->height();


    // 查询内容
    // queryOrderId();
    if(status == 2){
        queryDRId();
        queryDRName();
        queryFoodName();
        queryOrderCreateTime();
        queryOrderCondition();
        queryOwnerName();
    }
    if(status == 1){
        queryDRId();
        queryDRName();
        queryFoodName();
        queryOrderCreateTime();
        queryOrderCondition();
        queryOwnerName();
    }


    setOrderCondition();
    setupFoodCard(queryFoodId());
    queryUpdatePrice();
    isClosePayBtn();

    // 设置餐厅名文本格式

    setText();

    // 重新设置卡片尺寸
    this->resize(700,CardHeight);
}

OrderCard::~OrderCard()
{
    delete ui;
}

void OrderCard::on_GoTPayBtn_clicked()
{
    PayWidget *pw = new PayWidget(nullptr,id_user,id_order,id_DR);
    QSqlQuery q;
    q.prepare("select compensate, redPacket, freeShipping from drinfo where DRID = :DR");
    q.bindValue(":DR",id_DR);
    q.exec();
    q.next();
    pw->less[0] = q.value("compensate").toBool();
    pw->less[1] = q.value("redPacket").toBool();
    pw->less[2] = q.value("freeShipping").toBool();
    pw->sum = this->sum;
    q.prepare("select openTime,closeTime,capacity,BaseFare,Fare from DRINFo where DRID = :DR");
    q.bindValue(":DR",id_DR);
    q.exec();
    q.next();
    pw->open = new QTime(q.value("openTime").toTime());
    pw->close = new QTime(q.value("closeTime").toTime());
    pw->cur = new QTime(QTime::currentTime());
    pw->Fare = q.value("Fare").toFloat();
    float BaseFare = q.value("basefare").toFloat();
    if(pw->cur < pw->open && pw->cur > pw->close){
        QMessageBox::critical(nullptr,"创建订单失败","不在营业时间内");
        return;
    }
    int capapcity = q.value("capacity").toInt();
    int people;
    q.prepare("select * from orders where id_DR = :DR");
    q.bindValue(":DR",id_DR);
    q.exec();
    q.next();
    for(people = 0; q.next();){
        bool pay = q.value("OrderPayCondition").toBool();
        bool receive = q.value("OrderReceiveCondition").toBool();
        bool cancel = q.value("OrderCancelCondition").toBool();
        if(pay && !receive && !cancel){
            people++;
        }
    }
    if(people >= capapcity){
        QMessageBox::critical(nullptr,"创建订单失败","餐厅接待能力已到达上限");
        return;
    }
    q.prepare("select money,password from user where id_user = :user");
    q.bindValue(":user",id_user);
    q.exec();
    q.next();
    pw->password = q.value("password").toString();
    pw->money = q.value("money").toFloat();

    if(sum < BaseFare){
        QMessageBox::critical(nullptr,"创建订单失败","未达到起送价");
        return;
    }
    pw->setupWidget();
    pw->show();
}

void OrderCard::on_finish_clicked()
{
    AddComment *acw = new AddComment(nullptr,id_order,id_user);
    acw->id_DR = id_DR;
    acw->show();
}


void OrderCard::on_receive_clicked()
{
    OrderSubmitReceive *dw = new OrderSubmitReceive(this);
    dw->show();
    connect(dw,&QDialog::accepted,[=](){
        QSqlQuery q;
        q.prepare("update orders set OrderReceiveCondition = 1, OrderReceiveTime = now() where orderid = :order");
        q.bindValue(":order",id_order);
        q.exec();
        q.prepare("select sum(timediff(OrderReceiveTime,OrderPayTime)) from orders where id_DR = :DR and OrderReceiveCondition = 1 group by id_DR");
        q.bindValue(":DR",id_DR);
        q.exec();
        q.next();
        int speed = q.value(0).toInt();
        q.prepare("select * from orders where orderid = :order");
        q.bindValue(":order",id_order);
        q.exec();
        int size = 0;
        while (q.next()) {
            size++;
        }
        speed = int((float)speed/(float)size);
        QTime *time1 = new QTime(0,0,0);
        time = new QTime(time1->addSecs(speed));
        q.prepare("update drinfo set speed = :speed where DRID = :DR");
        q.bindValue(":speed",time->toString("hh:mm:ss"));
        q.bindValue(":DR",id_DR);
        q.exec();
    });
}


void OrderCard::on_cancel_clicked()
{
    QSqlQuery q;
    q.prepare("update orders set OrderCancelCondition = 1 where orderid = :order");
    q.bindValue(":order",id_order);
    q.exec();
}

