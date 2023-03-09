#include "addcomment.h"
#include "ui_addcomment.h"
#include <QSqlQuery>
#include "drwidget.h"

AddComment::AddComment(QWidget *parent,QString id_order,QString id_user) :
    QWidget(parent),
    ui(new Ui::AddComment)
{
    ui->setupUi(this);
    this->setWindowTitle("评论");
    this->id_order = id_order;
    this->id_user = id_user;
}

AddComment::~AddComment()
{
    delete ui;
}

void AddComment::on_pushButton_2_clicked()
{
    this->close();
    delete this;
}


void AddComment::on_pushButton_clicked()
{
    CommetnContent = ui->plainTextEdit->toPlainText();
    QSqlQuery q;
    int grade = ui->spinBox->value();
    q.prepare("update orders set rating = :a where orderid  = :b");
    q.bindValue(":a",grade);
    q.bindValue(":b",id_order);
    q.exec();
//    q.prepare("select id_DR from orders where orderid = :a");
//    q.bindValue(0,id_order);
//    q.exec();
//    q.next();
//    id_DR = q.value(0).toString();
    q.prepare("insert into comment (contentment, Id_order, Id_user, grade, Id_DR) values(:comment,:order,:user,:grade,:DR)");
    q.bindValue(":comment",CommetnContent);
    q.bindValue(":order",id_order);
    q.bindValue(":user",id_user);
    q.bindValue(":grade",grade);
    q.bindValue(":DR",id_DR);
    q.exec();
    q.prepare("update orders set OrderFinishTime = now(),OrderFinishCondition = 1 where orderid = :a");
    q.bindValue(0,id_order);
    q.exec();
    q.prepare("select id_food from ordertofood where id_order = :a");
    q.bindValue(0,id_order);
    q.exec();
    int i;
    for (i = 0; q.next() ; i++) {
        QSqlQuery query;
        int number;
        QString id_food = q.value("id_food").toString();
        query.prepare("select number from ordertofood where id_order = :order AND id_food  = :food"); // 从ordertofood表中查询
        query.bindValue(":order",id_order);
        query.bindValue(":food",id_food);
        query.exec();
        query.next();
        number = query.value(0).toInt();
        query.prepare("update food set sales = sales + :c where id_food = :a AND id_DR = :b");
        query.bindValue(":a",id_food);
        query.bindValue(":b",id_DR);
        query.bindValue(":c",number);
        query.exec();
        query.prepare("update DRinfo set salesVolume = salesVolume + :c where DRID = :b");
        query.bindValue(":b",id_DR);
        query.bindValue(":c",number);
        query.exec();
    }
    QSqlQuery q1;
    q1.prepare("select sum(grade) from comment where Id_DR = :DR");
    q1.bindValue(":DR",id_DR);
    q1.exec();
    q1.next();
    q.prepare("select * from comment where Id_DR = :DR");
    q.bindValue(":DR",id_DR);
    q.exec();

    for(i = 0 ; q.next() ; i++);
    float Tgrade = q1.value(0).toFloat();
    q.prepare("update DRinfo set rating = :a, salesnum = salesnum + 1 where DRID = :b");
    q.bindValue(":a",Tgrade/i);
    q.bindValue(":b",id_DR);
    q.exec();
    this->close();
    delete this;
}


void AddComment::on_recomm_clicked()
{
    DRWidget *dw = new DRWidget(nullptr,id_user);
    dw->setDRid(id_DR);
    dw->show();
//    this->setEnabled(false);
}

