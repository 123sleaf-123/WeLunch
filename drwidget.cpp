#include "drwidget.h"
#include "ui_drwidget.h"
#include "foodindrwidget.h"
#include "resaurantinformation.h"
#include "foodinformation.h"
#include "widget.h"

DRWidget::DRWidget(QWidget *parent,QString id_user) :
    QWidget(parent),
    ui(new Ui::DRWidget)
{
    ui->setupUi(this);
    ui->horizontalLayoutWidget->hide();
    this->resize(600,1000);
    connect(this,&DRWidget::initEnd,this,&DRWidget::setupDRWideget);

    if(!id_user.isNull()){
        this->id_user = id_user;
        if(id_user.contains("user")){
            status = 3; // 推荐模式
            ui->pushButton_add->hide();
        }
        else if(id_user.contains("DR")){
            status = 1; // 商家模式
            QSqlQuery q;
            q.prepare("select DRID from DRinfo where id_user = :user");
            q.bindValue(":user",id_user);
            q.exec();
            q.next();
//            id_DR = q.value("DRID").toString();
            setDRid(q.value("DRID").toString());
        }
    }
    else{
        status = 2; // 顾客模式
        ui->pushButton_add->hide();
    }

}

DRWidget::~DRWidget()
{
    delete ui;
}

void DRWidget::setupFoodCard(QSqlQuery *q){
    int count = 0;
    for( ; q->next(); count++){
        // 设置食物卡片位置
        FoodinDRWidget *card = new FoodinDRWidget(this);
        card->status = this->status;
        card->id_user = this->id_user;
        card->setids(id_DR,q->value(0).toString());
        card->move(10,130 + count * 150);
        card->resize(600,150);
        card->show();
    }
    this->resize(600,230 + count * 150);
    delete q;
}

void DRWidget::setDRid(QString id_DR){
    this->id_DR = id_DR;
    emit initEnd();
}

void DRWidget::setupDRWideget(){
    setupFoodCard(queryFood());
    ui->horizontalLayoutWidget->show();
}

QSqlQuery *DRWidget::queryFood(){
    QSqlQuery *q = new QSqlQuery;
    q->prepare("select id_food from food where id_DR = :a");
    q->bindValue(0,id_DR);
    q->exec();
    return q;
}

void DRWidget::on_info_clicked()
{
    ResaurantInformation *rw = new ResaurantInformation(nullptr,id_DR,id_user);
    rw->show();
}



void DRWidget::on_pushButton_add_clicked()
{
    FoodInformation *fiw = new FoodInformation(nullptr,id_DR);
    fiw->setStatus(status);
    fiw->show();
}


void DRWidget::on_pushButton_clicked()
{
    Widget *w = new Widget(nullptr);
    w->id_DR = id_DR;
    w->setUser(id_user,status);
    w->show();
}

