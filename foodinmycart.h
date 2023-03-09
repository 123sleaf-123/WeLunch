#ifndef FOODINMYCART_H
#define FOODINMYCART_H

#include <QWidget>
#include <QSqlQuery>

namespace Ui {
class FoodInMyCart;
}

class FoodInMyCart : public QWidget
{
    Q_OBJECT

public:
    explicit FoodInMyCart(QWidget *parent = nullptr);
    ~FoodInMyCart();
    void setCard();
    void queryFoodInfo();

    QString id_food;
    QString id_DR;
    QString id_user;
    int number;
    bool select;
    float price;
    QString imagePath;
    QString FoodName;
    QString id_cart;

signals:
    void selected();
    void noselected();

private slots:
    void on_select_clicked();

    void on_pushButton_ImageToFood_clicked();

    void on_number_valueChanged(int arg1);

    void on_select_toggled(bool checked);

private:
    Ui::FoodInMyCart *ui;
};

#endif // FOODINMYCART_H
