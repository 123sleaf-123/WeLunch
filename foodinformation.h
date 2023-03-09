#ifndef FOODINFORMATION_H
#define FOODINFORMATION_H

#include <QWidget>
#include <QSqlQuery>

QT_BEGIN_NAMESPACE
namespace Ui { class FoodInformation; }
QT_END_NAMESPACE

class FoodInformation : public QWidget
{
    Q_OBJECT

public:
    FoodInformation(QWidget *parent = nullptr,QString id_DR = nullptr,QString id_food = nullptr);
    ~FoodInformation();

    void queryFoodName();
    void queryPrice();
    void queryfoodDescription();
    void queryfoodIngredient();
    void queryfoodTaste();
    void queryfoodVolume();
    void queryimagepath();
    void querysales();
    void setStatus(int status);

    void queryreFoodId();
    void queryreFoodName();
    void queryrePrice();
    void queryrefoodDescription();
    void queryrefoodIngredient();
    void queryrefoodTaste();
    void queryrefoodVolume();

    void querynewFoodId();
    void querynewFoodName();
    void querynewPrice();
    void querynewfoodDescription();
    void querynewfoodIngredient();
    void querynewfoodTaste();
    void querynewfoodVolume();

    QString Id_food;
    QString id_DR;
    QString FoodName;
    float price;
    QString foodDescription;
    QString foodIngredient;
    QString foodTaste;
    QString foodVolume;
    QString imagepath;
    int sales;

    int status;
    int qOa;


private slots:
    void on_xiu_clicked();

    void on_wan_clicked();

private:
    Ui::FoodInformation *ui;
};
#endif // FOODINFORMATION_H
