#ifndef ORDERWIDGET_H
#define ORDERWIDGET_H

#include <QWidget>
#include "orderlistwidegt.h"
#include "orderlistviewcontroller.h"

namespace Ui {
class OrderWidget;
}

class OrderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OrderWidget(QWidget *parent = nullptr);
    ~OrderWidget();

    // 初始化
    void setUser(QString, int status);

    // 初始化完成
    void changeShowPage();

    QSqlQuery *query;
    OrderListWidegt *olw;
//    OrderListViewController *olvc;
    QString id_user;
    int status;
    int selectMode_order;
    int sortMode_order;
    QString searchOrderId;
    QDate date_Start;
    QDate date_End;
    int days;

signals:
    void initEnd();

private:
    Ui::OrderWidget *ui;

public slots:
    void setWidget();
private slots:
    void on_Sort_user_currentIndexChanged(int index);
    void on_Search_clicked();
    void on_OrderCode_editingFinished();
    void on_StartTime_userDateChanged(const QDate &date);
    void on_EndTime_userDateChanged(const QDate &date);
    void on_Sort_Time_currentIndexChanged(int index);
    void on_Sort_merUpper_currentIndexChanged(int index);
};

#endif // ORDERWIDGET_H
