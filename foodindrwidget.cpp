#include "foodindrwidget.h"
#include "ui_foodindrwidget.h"
#include "foodinformation.h"

FoodinDRWidget::FoodinDRWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FoodinDRWidget)
{
    ui->setupUi(this);
    connect(this,&FoodinDRWidget::initEnd,this,&FoodinDRWidget::setupFoodCard);
}

FoodinDRWidget::~FoodinDRWidget()
{
    delete ui;
}

void FoodinDRWidget::setids(QString id_DR, QString id_food){
    this->id_DR = id_DR;
    this->id_food = id_food;
    emit initEnd();
}

void FoodinDRWidget::setupFoodCard(){
    queryNsetContent();
    if(status == 3){
        ui->pushButton->setEnabled(true);
        ui->number->hide();
    }
    if(status == 1){
        ui->pushButton->hide();
        ui->number->close();
    }
}

void FoodinDRWidget::queryNsetContent(){
    QSqlQuery q;
    q.prepare("select price,imagepath,foodname,sales,recommend from food where id_food = :food AND id_DR = :DR");
    q.bindValue(0,id_food);
    q.bindValue(1,id_DR);
    q.exec();
    q.next();
    this->Price = q.value("price").toFloat();
    this->ImagePath = q.value("imagepath").toString();
    this->SalesVolumn = q.value("sales").toInt();
    this->FoodName = q.value("foodname").toString();
    this->recommendCount = q.value("recommend").toInt();
    q.prepare("select * from cart where id_food = :food AND id_user = :user AND id_DR = :DR");
    q.bindValue(":food",id_food);
    q.bindValue(":user",id_user);
    q.bindValue(":DR",id_DR);
    q.exec();
    q.next();
    int number = q.value("number").toInt();
    ui->number->setValue(number);
    ui->pushButton_ImageToFood->paintPicture(ImagePath);
    ui->pushButton_TextToFood->setText(FoodName);
    ui->Price->setText(QString("%1 ￥").arg(Price));
    ui->Sales->setText(QString("%1").arg(SalesVolumn));
    ui->recommend->setText(QString("%1").arg(recommendCount));
}

void FoodinDRWidget::on_pushButton_ImageToFood_clicked()
{
    qDebug("按下了图片按钮");
    FoodInformation *w = new FoodInformation(nullptr,id_DR,id_food);
    w->setStatus(status);
    w->show();
}


void FoodinDRWidget::on_number_valueChanged(int arg1)
{
    FoodNum = arg1;
    QSqlQuery q;
    if(arg1 == 0){
        q.prepare("delete from cart where id_user = :user AND id_food = :food AND id_DR = :DR");
        q.bindValue(":food",id_food);
        q.bindValue(":DR",id_DR);
        q.bindValue(":user",id_user);
        q.exec();
    }
    if(arg1 == 1){
        q.prepare("insert into cart(id_food, id_DR, id_user, number) values(:food, :DR, :user, :number)");
        q.bindValue(":food",id_food);
        q.bindValue(":DR",id_DR);
        q.bindValue(":user",id_user);
        q.bindValue(":number",FoodNum);
    }
    else{
        q.prepare("update cart set number =:number where id_user = :user AND id_food = :food AND id_DR = :DR");
        q.bindValue(":food",id_food);
        q.bindValue(":DR",id_DR);
        q.bindValue(":user",id_user);
        q.bindValue(":number",FoodNum);
    }
    q.exec();
}


void FoodinDRWidget::on_pushButton_clicked()
{
    QSqlQuery q;
    q.prepare("update food set recommend = recommend + 1 where id_food = :food AND id_DR = :DR");
    q.bindValue(0,id_food);
    q.bindValue(1,id_DR);
    q.exec();
    ui->pushButton->setEnabled(false);
}

