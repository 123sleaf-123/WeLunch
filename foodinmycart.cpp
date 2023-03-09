#include "foodinmycart.h"
#include "ui_foodinmycart.h"
#include "foodinformation.h"

FoodInMyCart::FoodInMyCart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FoodInMyCart)
{
    ui->setupUi(this);
//    this->setStyleSheet("background:transparent;border:0.5px solid black;");
}

FoodInMyCart::~FoodInMyCart()
{
    delete ui;
}

void FoodInMyCart::on_select_clicked()
{

}

void FoodInMyCart::queryFoodInfo(){
    QSqlQuery q;
    q.prepare("select price,imagepath,foodname from food where id_food = :food AND id_DR = :DR");
    q.bindValue(0,id_food);
    q.bindValue(1,id_DR);
    q.exec();
    q.next();
    this->price = q.value("price").toFloat();
    this->imagePath = q.value("imagepath").toString();
    this->FoodName = q.value("foodname").toString();
}

void FoodInMyCart::setCard(){
    ui->Price->setText(QString("%1 ￥").arg(price));
    ui->number->setValue(number);
    ui->pushButton_ImageToFood->paintPicture(imagePath);
    ui->pushButton_TextToFood->setText(FoodName);
    ui->select->setChecked(select);
    this->resize(450,160);
    this->show();
}

void FoodInMyCart::on_pushButton_ImageToFood_clicked()
{
    qDebug("按下了图片按钮");
    FoodInformation *w = new FoodInformation(nullptr,id_DR,id_food);
    w->setStatus(2);
    w->show();
}


void FoodInMyCart::on_number_valueChanged(int arg1)
{
    QSqlQuery q;
    if(arg1 == 0){
        q.prepare("delete from cart where id_user = :user AND id_food = :food AND id_DR = :DR");
        q.bindValue(":food",id_food);
        q.bindValue(":DR",id_DR);
        q.bindValue(":user",id_user);
        q.exec();
    }
    else{
        q.prepare("update cart set number =:number where id_user = :user AND id_food = :food AND id_DR = :DR");
        q.bindValue(":food",id_food);
        q.bindValue(":DR",id_DR);
        q.bindValue(":user",id_user);
        q.bindValue(":number",arg1);
    }
    q.exec();
}


void FoodInMyCart::on_select_toggled(bool checked)
{
    QSqlQuery q;
    if(ui->select->isChecked()){
        q.prepare("update cart set selectmode = 1 where id_cart = :cart");
//        qDebug("check");
        q.bindValue(":cart",id_cart);
        q.exec();
        emit selected();
    }
    else{
        qDebug("nocheck");
        q.prepare("update cart set selectMode = 0 where id_cart = :cart");
        q.bindValue(":cart",id_cart);
        q.exec();
        emit noselected();
    }
}

