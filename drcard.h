#ifndef DRCARD_H
#define DRCARD_H

#include <QWidget>

namespace Ui {
class DRCard;
}

class DRCard : public QWidget
{
    Q_OBJECT

public:
    explicit DRCard(QWidget *parent = nullptr);
    ~DRCard();
    void setDRID(QString id_DR);
    void setImagePath(QString ImagePath);
    void setDRName(QString DRName);
    void setDRRatings(float DRRatings);
    void setDRSpeed(QString DRSpeed);
    void setDistance(float Distance);
    void setSales(int DRSales);

    QString id_user;
    QString id_DR;
    QString ImagePath;
    QString DRName;
    float DRRatings;
    QString DRSpeed;
    float Distance;
    int DRSales;

private slots:
    void on_pushButton_PicToDR_clicked();

private:
    Ui::DRCard *ui;
};

#endif // DRCARD_H
