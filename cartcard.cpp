#include "cartcard.h"
#include "ui_cartcard.h"

CartCard::CartCard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CartCard)
{
    ui->setupUi(this);
//    this->resize(600,1000);
//    this->setStyleSheet("background:transparent;border:1px solid black;");
}

void CartCard::setUser(QString id_user){
    this->id_user = id_user;
}

void CartCard::queryDRName(){
    QSqlQuery q;
    q.prepare("select DRName from DRinfo where DRID  = :DR");
    q.bindValue(":DR",id_DR);
    q.exec();
    q.next();
    DRName = q.value(0).toString();
    ui->DRName->setText(DRName);
}

void CartCard::queryFood(){
    this->q = new QSqlQuery;
    q->prepare("select * from cart where 'select' = 0 AND id_user = :user AND id_DR = :DR");
    q->bindValue(":user",id_user);
    q->bindValue(":DR",id_DR);
    q->exec();
}

void CartCard::setupFood(){
    int i = 0;
    for(; q->next() ; i++){
        FoodInMyCart *fcw = new FoodInMyCart(this);
        fcw->move(50,50 + i * 160);
        fcw->id_cart = q->value("id_cart").toString();
        fcw->id_food = q->value("id_food").toString();
        fcw->id_DR = id_DR;
        fcw->id_user = id_user;
        fcw->select = q->value("selectMode").toBool();
        fcw->number = q->value("number").toInt();
        fcw->queryFoodInfo();
        fcw->setCard();
        fcw->show();
        connect(fcw,&FoodInMyCart::selected,[=](){
           this->sum += fcw->price;
        });
        connect(fcw,&FoodInMyCart::noselected,[=](){
           this->sum -= fcw->price;
        });
    }
    this->resize(700,100 + i * 160);
}

CartCard::~CartCard()
{
    delete ui;
}

void CartCard::on_select_clicked()
{
    QList<QRadioButton *> RBtns = this->findChildren<QRadioButton *>(QString(),Qt::FindChildrenRecursively);
    for (int i = 1 ; i < RBtns.count() ; i++) {
        if(RBtns.at(i)->isChecked() != ui->select->isChecked()){
            RBtns.at(i)->toggle();
        }
    }
}

