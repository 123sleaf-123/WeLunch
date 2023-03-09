#include "widget.h"
#include "./ui_widget.h"
#include <QtSql>
#include <QMessageBox>
#include <QSqlTableModel>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle(QString("我的评论"));
    this->resize(700,541);
    connect(this,&Widget::initEnd,this,&Widget::setupTable);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_BtnAdd_clicked()
{
    QSqlRecord record = mod->record(); // 添加并获取空记录

    // 获取行号
    int row = mod->rowCount();

    // 插入记录
    mod->insertRecord(row, record);
}


void Widget::on_BtnSure_clicked()
{
    mod->submitAll();
}


void Widget::on_BtnCancel_clicked()
{
    mod->revertAll();
    mod->submitAll();
}


void Widget::on_BtnDel_clicked()
{
    // 获取选中模型
    QItemSelectionModel *SMod = ui->tableView->selectionModel();
    // 取出模型中的索引
    QModelIndexList List = SMod->selectedRows();
    // 删除所有选中行
    for(int i = 0; i < List.size(); i++){
        mod->removeRow(List.at(i).row());
    }
}


void Widget::on_BtnFind_clicked()
{
    QString str, str_ser, str_sort;
    str_ser = ui->lineEdit->text();
    str_sort = ui->FindSort->currentText();
    if(str_sort == "全部"){
        mod->setFilter("");
        mod->select();
    }
    else{
        if(str_sort == "真实姓名")
            str = QString ("realname = '%1'").arg(str_ser);
        else if(str_sort == "用户名")
            str = QString ("username = '%1'").arg(str_ser);
        else if(str_sort == "学号/教工号")
            str = QString ("id = '%1'").arg(str_ser);
        else if(str_sort == "用户权限")
            str = QString ("power = '%1'").arg(str_ser);
        else if(str_sort == "密码")
            str = QString ("password = '%1'").arg(str_ser);
        mod->setFilter(str);
        mod->select();
    }
}


void Widget::on_FindSort_activated(const QString &arg1)
{
    ui->BtnFind->setFocus();
}

void Widget::setUser(QString id_user, int status){
    this->id_user = id_user;
    this->status = status;
    emit initEnd();
}

void Widget::setupTable(){
    QSqlQuery q;
    QString filter;
    if(id_DR.isEmpty())
    {
        if(status == 1){
            ui->BtnAdd->setEnabled(false);
            ui->BtnDel->setEnabled(false);
            ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
            q.prepare("selecet id_DR from orders where id_user = :a");
            q.bindValue(":a",id_user);
            q.exec();
            q.next();
            id_DR = q.value("id_DR").toString();
        }
        if(status == 2){
            ui->BtnAdd->setEnabled(false);
            ui->BtnDel->setEnabled(false);
        }
        if(status == 1){
            filter = QString("id_DR = '%1'").arg(id_DR);
        }
        if(status == 2){
            filter = QString("id_user = '%1'").arg(id_user);
        }
    }
    else{
        filter = QString("id_DR = '%1'").arg(id_DR);
    }
    // 设置模型
    mod = new QSqlTableModel(this);
    mod->setTable("comment");

    // 把模型放在view
    ui->tableView->setModel(mod);

    mod->setFilter(filter);

    // 显示模型里的数据
    mod->select();

    QStringList tables;
    tables << "" << "评论内容" << "订单编号" << "用户ID" << "评论时间" << "评分" ;
    for(int i = 0 ; i < tables.count(); i++){
        mod->setHeaderData(i,Qt::Horizontal,tables[i]);//设置显示框表头显示
    }
    mod->setSort(0,Qt::AscendingOrder);//设置按照第0列升序排序，DescendingOrder降序
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置单元格不可编辑
    ui->tableView->horizontalHeader()->setStretchLastSection(true);//设置最后一列填充后面表格
    ui->tableView->setColumnHidden(0,true);//设置第0行隐藏
//    ui->tableView->setColumnHidden(5,true);//设置第5行隐藏
    ui->tableView->setColumnHidden(6,true);//设置第6行隐藏
    ui->tableView->setColumnWidth(1,200);//设置列宽，界面看起来更舒适
    ui->tableView->setColumnWidth(2,100);//设置列宽，界面看起来更舒适
    ui->tableView->setColumnWidth(3,150);//设置列宽，界面看起来更舒适
    ui->tableView->setColumnWidth(4,150);//设置列宽，界面看起来更舒适
    ui->tableView->verticalHeader()->setDefaultSectionSize(30);
    // 设置为手动提交
    mod->setEditStrategy(QSqlTableModel::OnManualSubmit);
}

