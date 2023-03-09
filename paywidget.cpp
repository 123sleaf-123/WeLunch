#include "paywidget.h"
#include "ui_paywidget.h"
#include <QSqlQuery>
#include <QMessageBox>

PayWidget::PayWidget(QWidget *parent, QString id_user,QString id_order,QString id_DR) :
    QWidget(parent),
    ui(new Ui::PayWidget)
{
    ui->setupUi(this);
    this->setWindowTitle("付款");
    this->id_user = id_user;
    this->id_order = id_order;
    this->id_DR = id_DR;
}

PayWidget::~PayWidget()
{
    delete ui;
}

void PayWidget::setupWidget(){
    if(less[1] == true){
        ui->comboBox->setEnabled(true);
    }
    if(less[0] == true){
        sum -= 5;
    }
    if(less[2] == false){
        sum += Fare;
    }
    ui->price->setText(QString("%1").arg(sum));
    ui->money->setText(QString("%1").arg(money));
}

void PayWidget::on_pay_clicked()
{
    if(password == ui->password->text()){
        if(money < sum){
            QMessageBox::critical(nullptr,"付款失败","余额不足");
            return;
        }
        money -= sum;
        QSqlQuery q;
        q.prepare("update orders set pay = :pay, OrderPayCondition = 1, OrderPayTime = now() where orderid = :order");
        q.bindValue(":pay",sum);
        q.bindValue(":order",id_order);
        q.exec();
        q.prepare("update user set money = :money where id_user = :user");
        q.bindValue(":money",money);
        q.bindValue(":user",id_user);
        q.exec();
        this->QWidget::close();
        delete this;
    }
    else{
        QMessageBox::critical(nullptr,"付款失败","密码错误,请重新输入");
        return;
    }
}


void PayWidget::on_comboBox_currentIndexChanged(int index)
{
    if(index == 0){
        sum += 5;
    }
    if(index == 1){
        sum -= 5;
    }
    ui->price->setText(QString("%1").arg(sum));
}

