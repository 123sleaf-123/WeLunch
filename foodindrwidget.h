#ifndef FOODINDRWIDGET_H
#define FOODINDRWIDGET_H

#include <QWidget>
#include <QSqlQuery>

namespace Ui {
class FoodinDRWidget;
}

class FoodinDRWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FoodinDRWidget(QWidget *parent = nullptr);
    ~FoodinDRWidget();

    void setids(QString id_DR, QString id_food);
    void queryNsetContent();

    QString id_DR;
    QString id_food;
    QString id_user;
    QString ImagePath;
    QString FoodName;
    float Price;
    int SalesVolumn;
    int recommendCount;
    int status;
    int FoodNum;

signals:
    void initEnd();

public slots:
    void setupFoodCard();

private slots:
    void on_pushButton_ImageToFood_clicked();

    void on_number_valueChanged(int arg1);

    void on_pushButton_clicked();

private:
    Ui::FoodinDRWidget *ui;
};

#endif // FOODINDRWIDGET_H
