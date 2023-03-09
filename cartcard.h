#ifndef CARTCARD_H
#define CARTCARD_H

#include <QWidget>
#include "foodinmycart.h"
#include <QSqlQuery>
#include "foodinmycart.h"

namespace Ui {
class CartCard;
}

class CartCard : public QWidget
{
    Q_OBJECT

public:
    explicit CartCard(QWidget *parent = nullptr);
    ~CartCard();
    void setUser(QString id_user);
    void queryDRName();
    void queryFood();
    void setupFood();

    QSqlQuery *q;
    QString id_user;
    QString id_DR;
    QString DRName;
    float sum;

private slots:
    void on_select_clicked();

private:
    Ui::CartCard *ui;
};

#endif // CARTCARD_H
