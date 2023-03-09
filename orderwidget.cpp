#include "orderwidget.h"
#include "ui_orderwidget.h"

OrderWidget::OrderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderWidget)
{
    ui->setupUi(this);
    this->resize(700,6000);
    connect(this,&OrderWidget::initEnd,this,&OrderWidget::setWidget);
    ui->StartTime->setDateTime(QDateTime::currentDateTime().addDays(-2));
    ui->EndTime->setDateTime(QDateTime::currentDateTime().addDays(1));
}

OrderWidget::~OrderWidget()
{
    delete ui;
}

void OrderWidget::setUser(QString id_user,int status){
    this->id_user = id_user;
    this->status = status;
    if(status == 2){
        ui->Sort_merUpper->hide();
    }
    emit initEnd();
}

void OrderWidget::setWidget(){
    olw = new OrderListWidegt(this);
    olw->move(10,200);
    olw->setUser(id_user,status);
}


void OrderWidget::on_Sort_user_currentIndexChanged(int index)
{
    selectMode_order = index;
}

void OrderWidget::on_Search_clicked()
{
    query = new QSqlQuery;
    QString Selectstr;
    QString id_DR;
    if(status == 1){
        query->prepare("select DRID from drinfo where id_user = :user");
        query->bindValue(":user",id_user);
        query->exec();
        query->next();
        id_DR = query->value("DRID").toString();
        Selectstr = QString("select orderid from orders where id_DR = '%1'").arg(id_DR);
    }
    if(status == 2){
        Selectstr = QString("select orderid from orders where id_user = '%1'").arg(id_user);
    }
    switch(selectMode_order){
    case 5:
        Selectstr = QString(Selectstr + " and OrderCancelCondition = 1");
        break;
    case 4:
        Selectstr = QString(Selectstr + " and OrderFinishCondition = 1");
        break;
    case 3:
        Selectstr = QString(Selectstr + " and OrderPayCondition = 1 and OrderReceiveCondition = 1 and OrderFinishCondition = 0");
        break;
    case 2:
        Selectstr = QString(Selectstr + " and OrderPayCondition = 1 and OrderReceiveCondition = 0");
        break;
    case 1:
        Selectstr = QString(Selectstr + " and OrderPayCondition = 0 and OrderCancelCondition = 0");
        break;
    case 0:
        break;
    }
    if(status == 1)
    {
        Selectstr = QString(Selectstr + " AND " +
                            "OrderPayTime between '%1' AND '%2'")
                .arg(ui->StartTime->date().toString("yyyyMMdd")).arg(ui->EndTime->date().toString("yyyyMMdd"));
    }
    if(status == 2){
        Selectstr = QString(Selectstr + " AND " +
                            "OrderCreateTime between '%1' AND '%2'")
                .arg(ui->StartTime->date().toString("yyyyMMdd")).arg(ui->EndTime->date().toString("yyyyMMdd"));
    }
    if(status == 1){
        switch(sortMode_order){
        case 3:
            Selectstr = QString(Selectstr + " order by OrderPayTime desc");
            break;
        case 2:
            Selectstr = QString(Selectstr + " order by OrderReceiveTime desc");
            break;
        case 1:
            Selectstr = QString(Selectstr + " order by price desc");
            break;
        case 0:
            Selectstr = QString(Selectstr + " order by rating desc");
            break;
        }
    }
    else{
        Selectstr = QString(Selectstr + " order by OrderCreateTime desc");
    }
    query->exec(Selectstr);
    changeShowPage();
}


void OrderWidget::on_OrderCode_editingFinished()
{
    searchOrderId = ui->Search->text();
}


void OrderWidget::on_StartTime_userDateChanged(const QDate &date)
{
    date_Start = date;
    date_End = ui->EndTime->date();
}


void OrderWidget::on_EndTime_userDateChanged(const QDate &date)
{
    date_Start = ui->StartTime->date();
    date_End = date;
}


void OrderWidget::on_Sort_Time_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        days = 3;
        break;
    case 1:
        days = 7;
        break;
    case 2:
        days = 30;
        break;
    case 3:
        days = 90;
        break;
    case 4:
        days = 365;
        break;
    }
    ui->StartTime->setDateTime(ui->EndTime->dateTime().addDays(qint64(-days)));
}


void OrderWidget::on_Sort_merUpper_currentIndexChanged(int index)
{
    sortMode_order = index;
}

void OrderWidget::changeShowPage(){
    olw->close();
    QRect rect = olw->geometry();
    delete olw;
    olw = new OrderListWidegt(this);
    olw->setGeometry(rect);
    olw->id_user = id_user;
    olw->status = status;
    olw->setupOrderCard(query);
    olw->show();
}

