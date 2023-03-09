#include "user_toolbar.h"
#include "ui_user_toolbar.h"

User_ToolBar::User_ToolBar(QWidget *parent,QString id_user) :
    QWidget(parent),
    ui(new Ui::User_ToolBar)
{
    ui->setupUi(this);
}

User_ToolBar::~User_ToolBar()
{
    delete ui;
}



void User_ToolBar::on_pushButton_Order_clicked()
{
    emit pushButton_Order_clicked();
}


void User_ToolBar::on_pushButton_food_clicked()
{
    emit pushButton_food_clicked();
}


void User_ToolBar::on_pushButton_MYCart_clicked()
{
    emit pushButton_MYCart_clicked();
}


void User_ToolBar::on_pushButton_Comments_clicked()
{
    emit pushButton_Comments_clicked();
}


void User_ToolBar::on_pushButton_Mine_clicked()
{
    emit pushButton_Mine_clicked();
}


void User_ToolBar::on_pushButton_Settings_clicked()
{
    emit pushButton_Settings_clicked();
}

void User_ToolBar::setUser(QString id_user){
    this->id_user = id_user;
    if(status == 1){
        ui->pushButton_MYCart->hide();
        ui->pushButton_food->setText("我的餐厅");
    }
    QSqlQuery q;
    q.prepare("select imagepath from user where id_user = :user");
    q.bindValue(0,id_user);
    q.exec();
    q.next();
    imagePath = q.value(0).toString();
    ui->pushButton_Avatar->paintPicture(imagePath);
}


void User_ToolBar::on_pushButton_Avatar_clicked()
{
    emit pushButton_Avatar_clicked();
}

