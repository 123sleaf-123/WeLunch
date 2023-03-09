#ifndef ORDERLISTVIEWCONTROLLER_H
#define ORDERLISTVIEWCONTROLLER_H

#include <QWidget>
#include <QSqlQuery>
#include <QDateTime>

namespace Ui {
class OrderListViewController;
}

class OrderListViewController : public QWidget
{
    Q_OBJECT

public:
    explicit OrderListViewController(QWidget *parent = nullptr);
    ~OrderListViewController();

    void setUser(QString id_user,int status);

    QString id_user;
    int status; // 1是商家，2是用户
    int SelectMode;
    int OrderMode;
    int days;
    QString Selectstr;
    QDateTime startTime;
    QDateTime endTime;
    QSqlQuery *q;
    QString time1;
    QString time2;
    QString id_ussr;

signals:
    void initEnd();
    void comboIndexChange();

private:
    Ui::OrderListViewController *ui;

public slots:
    void setWidget();
private slots:
    void on_Sort_user_currentIndexChanged(int index);
    void on_Search_clicked();
    void on_Sort_Time_currentIndexChanged(int index);
    void on_Sort_merUpper_currentIndexChanged(int index);
};

#endif // ORDERLISTVIEWCONTROLLER_H
