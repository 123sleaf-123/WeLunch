#include "orderdetails.h"
#include "ui_orderdetails.h"

OrderDetails::OrderDetails(QWidget *parent,QString id_order, QString id_user) :
    QWidget(parent),
    ui(new Ui::OrderDetails)
{
    ui->setupUi(this);
    setWindowTitle("订单");
    this->id_order = id_order;
    this->id_user = id_user;
    setFixedSize(700,541);
    queryAddress();
    queryteleNum();
    queryGrade();
    queryComment();
    ui->lineEdit->setText(address);
    ui->lineEdit_2->setText(telenum);
    ui->lineEdit_3->setText(QString("%1").arg(grade));
    ui->lineEdit_4->setText(comment);
}

OrderDetails::~OrderDetails()
{
    delete ui;
}

void OrderDetails::on_pushButton_clicked()
{

}


void OrderDetails::on_pushButton_2_clicked()
{
    close();
}

//查询地址
void OrderDetails::queryAddress(){
    QSqlQuery query;
    query.prepare("select address from user where Id_user = :a");
    query.bindValue(0,id_user);
    query.exec();
    query.next();
    address = query.value(0).toString();
    query.clear();
}
//查询电话
void OrderDetails::queryteleNum(){
    QSqlQuery query;
    query.prepare("select teleNum from user where Id_user = :a");
    query.bindValue(0,id_user);
    query.exec();
    query.next();
    telenum = query.value(0).toString();
    query.clear();
}
//查询评分
void OrderDetails::queryGrade(){
    QSqlQuery query;
    query.prepare("select grade from comment where id_order = :a");
    query.bindValue(0,id_order);
    query.exec();
    query.next();
    grade = query.value(0).toInt();
    query.clear();
}
//查询评价
void OrderDetails::queryComment(){
    QSqlQuery query;
    query.prepare("select contentment from comment where id_order = :a");
    query.bindValue(0,id_order);
    query.exec();
    query.next();
    comment = query.value(0).toString();
    query.clear();
}


