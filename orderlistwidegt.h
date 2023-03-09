#ifndef ORDERLISTWIDEGT_H
#define ORDERLISTWIDEGT_H

#include <QWidget>
#include <QSqlQuery>

namespace Ui {
class OrderListWidegt;
}

class OrderListWidegt : public QWidget
{
    Q_OBJECT

public:
    explicit OrderListWidegt(QWidget *parent = nullptr);
    ~OrderListWidegt();
    // 初始化
    void setUser(QString, int status);

    // 初始化完成
    void setupOrderCard(QSqlQuery *q);

    QSqlQuery *queryOrderId_user();
    QSqlQuery *queryOrderId_DR();

    QString id_user;
    int SelectMode = 0;
    int CurrentY = 0;
    int status;

    QSqlQuery query;

signals:
    void initEnd();

private:
    Ui::OrderListWidegt *ui;

public slots:
    void setCard();
    void setSelectMode(int index);
private slots:
};

#endif // ORDERLISTWIDEGT_H
