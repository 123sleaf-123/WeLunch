#ifndef CART_H
#define CART_H

#include <QWidget>
#include "cartcard.h"
#include <QTime>
#include <QMessageBox>

namespace Ui {
class Cart;
}

class Cart : public QWidget
{
    Q_OBJECT

public:
    explicit Cart(QWidget *parent = nullptr);
    ~Cart();
    void queryCards();
    void setupCartCards();
    void createCheck(QString id_DR);

    QSqlQuery *q;
    QString id_user;
    int OrderCount;
    QString DRs[100];
    float sum;

private slots:
    void on_createOrder_clicked();

private:
    Ui::Cart *ui;
};

#endif // CART_H
