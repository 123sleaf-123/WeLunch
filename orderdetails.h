#ifndef ORDERDETAILS_H
#define ORDERDETAILS_H

#include <QWidget>
#include <QSqlQuery>

namespace Ui {
class OrderDetails;
}

class OrderDetails : public QWidget
{
    Q_OBJECT

public:
    explicit OrderDetails(QWidget *parent = nullptr,QString id_order = nullptr, QString id_user = nullptr);
    ~OrderDetails();

    void queryAddress();
    void queryteleNum();
    void queryGrade();
    void queryComment();


    QString id_user;
    QString id_order;
    QString Id_comment;
    QString address;
    QString telenum;
    int grade;
    QString comment;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::OrderDetails *ui;
};

#endif // ORDERDETAILS_H
