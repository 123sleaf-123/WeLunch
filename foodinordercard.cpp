#include "foodinordercard.h"
#include "ui_foodinordercard.h"
#include <QSqlQuery>
#include "orderdetails.h"

foodinordercard::foodinordercard(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::foodinordercard)
{
    ui->setupUi(this);
//    设置卡片大小
    this->resize(600,150);

}

float foodinordercard::setText(QString id_user, QString id_order, QString id_DR, QString id_food){
    QSqlQuery q;

    this->id_user = id_user;
    this->id_order = id_order;
    this->id_food =id_food;
    this->id_DR =id_DR;

    // 查询图片存储路径
    QString ImagePath;
    q.prepare("select foodname,imagepath from food where id_food = :food AND id_DR = :DR");
    q.bindValue(":food",id_food);
    q.bindValue(":DR",id_DR);
    q.exec();
    q.next();
    ImagePath = q.value("imagepath").toString();

    // 设置按钮图片
    this->ui->pushButton->paintPicture(ImagePath);

    // 查询菜品名
    QString FoodName = q.value("foodname").toString();
    this->ui->pushButton_TextToFood->setText(FoodName);

    // 查询菜品数量
    int FoodNum;
    q.prepare("select number from ordertofood where id_order = :order AND id_food  = :food"); // 从ordertofood表中查询
    q.bindValue(":order",id_order);
    q.bindValue(":food",id_food);
    q.exec();
    q.next();
    FoodNum = q.value(0).toInt();
    q.clear();

    this->ui->FoodNumber->setText(QString("%1").arg(FoodNum));

    // 查询菜品价格
    float FoodPrice;
    q.prepare("select price from food where id_food = :food AND id_DR = :DR"); // 从food中查询
    q.bindValue(":food", id_food);
    q.bindValue(":DR", id_DR);
    q.exec();
    q.next();
    FoodPrice = q.value("price").toFloat();
    q.clear();

    // 设置该菜品价格
    this->ui->PricePer->setText(QString("%1 ￥").arg(FoodPrice));

    // 查询订单地址
    QString Address;
    q.prepare("select address from user where id_user = :user");
    q.bindValue(":user",id_user);
    q.exec();
    q.next();
    Address = q.value("address").toString();

    this->ui->address->setText(Address);

    return FoodNum * FoodPrice;
}

foodinordercard::~foodinordercard()
{
    delete ui;
}

void foodinordercard::on_pushButton_clicked()
{
    qDebug("按下了图片按钮");
    OrderDetails *w = new OrderDetails(nullptr,id_order, id_user);
    w->show();
}

//void foodinordercard::queryPrice(QString price){
//    this->ui->PricePer->setText(price);
//}

