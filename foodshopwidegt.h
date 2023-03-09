#ifndef FOODSHOPWIDEGT_H
#define FOODSHOPWIDEGT_H

#include <QWidget>
#include "FoodShopWidgetOrderByScore.h"
#include "foodshopwidgetlinkedlistdeal.h"
#include <QSqlQuery>

namespace Ui {
class FoodShopWidegt;
}

class FoodShopWidegt : public QWidget
{
    Q_OBJECT

public:
    explicit FoodShopWidegt(QWidget *parent = nullptr,QString id_user = nullptr);
    ~FoodShopWidegt();

    void OrderByGrade_LinkedList();
    void setupDRCard(DRList head);
    void changeShowPage();
    void sortDefault();

    FoodShopWidgetLinkedListDeal *FSWLLManager;

    int status;
    QString id_user;
    int SelectMode_DRType;
    int SelectMode_Addition;
    int SortMode_Distance;
    int SortMode_DeFault;
    QRect DRCardWidgetrect;
    QString SearchContent;

private slots:
    void on_comboBox_4_currentIndexChanged(int index);

    void on_comboBox_3_currentIndexChanged(int index);

    void on_comboBox_currentIndexChanged(int index);

    void on_comboBox_2_currentIndexChanged(int index);
    void on_pushButton_Search_clicked();

private:
    Ui::FoodShopWidegt *ui;
};

#endif // FOODSHOPWIDEGT_H
