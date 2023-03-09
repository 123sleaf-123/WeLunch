#include "peopleinformation.h"
#include "ui_peopleinformation.h"

PeopleInformation::PeopleInformation(QWidget *parent,QString id_user)
    : QWidget(parent)
    , ui(new Ui::PeopleInformation)
{
    ui->setupUi(this);
    setFixedSize(700,541);
    this->Id_user = id_user;
    queryUsername();
    queryRealname();
    queryAdress();
    queryLongitude();
    queryLatitude();
    queryPassword();
    queryTelenum();
    queryMailbox();
    ui->lineEdit_id->setText(id_user);
    ui->lineEdit_name->setText(realname);
    ui->lineEdit_username->setText(username);
    ui->lineEdit_where->setText(address);
    ui->lineEdit_round->setText("北京");
    ui->lineEdit->setText(longitude);
    ui->lineEdit_2->setText(latitude);
    ui->lineEdit_number->setText(teleNum);
    ui->lineEdit_email->setText(mailbox);
    ui->lineEdit_password->setText(password);
}

PeopleInformation::~PeopleInformation()
{
    delete ui;
}


void PeopleInformation::on_change_number_clicked()
{
    ui->lineEdit_number->setEnabled(true);
    ui->lineEdit_email->setEnabled(true);
    ui->lineEdit_password->setEnabled(true);
    ui->change_number->setEnabled(false);
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
}


void PeopleInformation::on_pushButton_clicked()
{
    this->close();
}


void PeopleInformation::on_pushButton_2_clicked()
{
    this->close();
}


void PeopleInformation::on_pushButton_3_clicked()
{
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->change_number->setEnabled(true);
    ui->lineEdit_number->setEnabled(false);
    ui->lineEdit_email->setEnabled(false);
    ui->lineEdit_password->setEnabled(false);
    teleNum = ui->lineEdit_number->text();
    password = ui->lineEdit_password->text();
    mailbox = ui->lineEdit_email->text();
    queryrepassword();
    queryretelenum();
    queryremailbox();
}

//查询用户名
void PeopleInformation::queryUsername(){
    QSqlQuery query;
    query.prepare("select username from user where Id_user = :a");
    query.bindValue(0,Id_user);
    query.exec();
    query.next();
    username = query.value(0).toString();
    query.clear();
}
//查询姓名
void PeopleInformation::queryRealname(){
    QSqlQuery query;
    query.prepare("select realname from user where Id_user = :a");
    query.bindValue(0,Id_user);
    query.exec();
    query.next();
    realname = query.value(0).toString();
    query.clear();
}
//查询地址
void PeopleInformation::queryAdress(){
    QSqlQuery query;
    query.prepare("select address from user where Id_user = :a");
    query.bindValue(0,Id_user);
    query.exec();
    query.next();
    address = query.value(0).toString();
    query.clear();
}
//查询手机号
void PeopleInformation::queryTelenum(){
    QSqlQuery query;
    query.prepare("select teleNum from user where Id_user = :a");
    query.bindValue(0,Id_user);
    query.exec();
    query.next();
    teleNum = query.value(0).toString();
    query.clear();
}
//查询密码
void PeopleInformation::queryPassword(){
    QSqlQuery query;
    query.prepare("select password from user where Id_user = :a");
    query.bindValue(0,Id_user);
    query.exec();
    query.next();
    password = query.value(0).toString();
    query.clear();
}
//查询邮箱
void PeopleInformation::queryMailbox(){
    QSqlQuery query;
    query.prepare("select mailbox from user where Id_user = :a");
    query.bindValue(0,Id_user);
    query.exec();
    query.next();
    mailbox = query.value(0).toString();
    query.clear();
}
//查询经度
void PeopleInformation::queryLongitude(){
    QSqlQuery query;
    query.prepare("select user_longitude from user where Id_user = :a");
    query.bindValue(0,Id_user);
    query.exec();
    query.next();
    longitude = query.value(0).toString();
    query.clear();
}

void PeopleInformation::queryLatitude(){
    QSqlQuery query;
    query.prepare("select user_latitude from user where Id_user = :a");
    query.bindValue(0,Id_user);
    query.exec();
    query.next();
    latitude = query.value(0).toString();
    query.clear();
}

//修改密码
void PeopleInformation::queryrepassword(){
    QSqlQuery query;
    query.prepare( "update user SET password=:a  where Id_user = :b");
    query.bindValue(0,password);
    query.bindValue(1,Id_user);
    query.exec();
    query.clear();
}
//修改手机
void PeopleInformation::queryretelenum(){
    QSqlQuery query;
    query.prepare( "update user SET teleNum=:a  where Id_user = :b");
    query.bindValue(0,teleNum);
    query.bindValue(1,Id_user);
    query.exec();
    query.clear();
}
//修改邮箱
void PeopleInformation::queryremailbox(){
    QSqlQuery query;
    query.prepare( "update user SET mailbox=:a  where Id_user = :b");
    query.bindValue(0,mailbox);
    query.bindValue(1,Id_user);
    query.exec();
    query.clear();
}
