#include "orderlistviewcontroller.h"
#include "ui_orderlistviewcontroller.h"

OrderListViewController::OrderListViewController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderListViewController)
{
    ui->setupUi(this);
    this->ui->horizontalLayoutWidget->move(0,0);
    this->ui->horizontalLayoutWidget_2->move(0,this->ui->horizontalLayoutWidget->height());
    connect(this,&OrderListViewController::initEnd,this,&OrderListViewController::setWidget);
    SelectMode = 0;
    OrderMode = 0;
}

void OrderListViewController::setUser(QString id_user, int status){
    this->id_user = id_user;
    this->status = status;
    emit initEnd();
}

void OrderListViewController::setWidget(){
    switch (status) {
    case 0:
        break;
    case 1:
        this->ui->Sort_user->setEnabled(false);
        break;
    case 2:
        this->ui->Sort_merUpper->setEnabled(false);
        this->ui->horizontalLayoutWidget_2->close();
        break;
    }
}

OrderListViewController::~OrderListViewController()
{
    delete ui;
}

void OrderListViewController::on_Sort_user_currentIndexChanged(int index)
{
    SelectMode = index;
    emit comboIndexChange();
}


void OrderListViewController::on_Search_clicked()
{
    q = new QSqlQuery;
    QString searchOrderCode;
    QString strMode;
//    QDateTime strTimeStart,strTimeEnd;
//    Selectstr = QString("select orderid from orders where id_user = '%1'").arg(id_user);
    Selectstr = QString("select orderid from orders where id_user = '%1'").arg(id_user);

    switch(SelectMode){
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

    Selectstr = QString(Selectstr + " AND " +
                   "OrderPayTime between '%1' AND '%2'")
            .arg(ui->StartTime->date().toString("yyyyMMdd")).arg(ui->EndTime->date().toString("yyyyMMdd"));
//    if(!ui->Search->text().isEmpty()){
//        searchOrderCode = QString("orderid = '%1'").arg(ui->Search->text().toInt());
//        Selectstr.append(" AND ").append(searchOrderCode);
//    }
//    strTimeStart = ui->StartTime->dateTime();
//    strTimeEnd = ui->EndTime->dateTime();
//    QString time1 = strTimeStart.toString("yyyy-MM-dd hh:mm:ss"), time2 = strTimeEnd.toString("yyyy-MM-dd hh:mm:ss");
//    QString TimeSelectstr = QString("OrderPayTime between '%1' and '%2'").arg(time1).arg(time2);

//    Selectstr = QString(Selectstr + " and " + TimeSelectstr);
//    q->prepare(Selectstr);
    q->exec();
//    Selectstr = QString("select orderid from orders where OrderPayTime between ':a' and ':b'");
//    q->prepare(Selectstr);
//    q->bindValue(":user",id_user);
//    q->bindValue(":b",time2);
//    q->exec();
//    while(q->next()){
//        QString test = q->value(0).toString();
//        qDebug("222");
//    }
}


void OrderListViewController::on_Sort_Time_currentIndexChanged(int index)
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


void OrderListViewController::on_Sort_merUpper_currentIndexChanged(int index)
{
    OrderMode = index;
}

