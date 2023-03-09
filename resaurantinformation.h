#ifndef RESAURANTINFORMATION_H
#define RESAURANTINFORMATION_H

#include <QWidget>
#include <QSqlQuery>

QT_BEGIN_NAMESPACE
namespace Ui { class ResaurantInformation; }
QT_END_NAMESPACE

class ResaurantInformation : public QWidget
{
    Q_OBJECT

public:
    ResaurantInformation(QWidget *parent = nullptr,QString DRID = nullptr,QString id_user = nullptr);
    ~ResaurantInformation();
    void queryDRname();
    void queryCity();
    void querycreateTime();
    void querylongitude();
    void querylatitude();
    void queryopenTime();
    void querycloseTime();
    void queryCapacity();
    void queryIntroduction();
    void queryImagePath();
    void queryBaseFare();
    void queryFare();
    void querysalesVolume();
    void queryrating();
    void querysalesNum();
    void queryconsumingTime();
    void querySpeed();
    void queryCompensate();
    void queryredPacket();
    void queryRebate();
    void queryFreeShipping();

    void queryreDRname();
    void queryreCity();
    void queryrecreateTime();
    void queryrelongitude();
    void queryrelatitude();
    void queryreopenTime();
    void queryrecloseTime();
    void queryreCapacity();
    void queryreIntroduction();
    void queryreImagePath();
    void queryreBaseFare();
    void queryreFare();
    void queryresalesVolume();
    void queryrerating();
    void queryresalesNum();
    void queryreconsumingTime();
    void queryreSpeed();
    void queryreCompensate();
    void queryreredPacket();
    void queryreRebate();
    void queryreFreeShipping();

    QString DRID;
    QString DRName;
    QString createtime;
    QString city;
    QString longitude;
    QString latitude;
    QString opentime;
    QString closetime;
    int capacity;
    QString introduction;
    QString ImagePath;
    int BaseFare;
    float Fare;
    int salesvolume;
    float rating;
    int salesnum;
    float consumingtime;
    QString speed;
    bool compensate;
    bool redpacket;
    bool rebate;
    bool freeshipping;

    int status;

private slots:
    void on_xiu_clicked();

    void on_wan_clicked();

//    void on_pushButton_clicked();

//    void on_pushButton_2_clicked();

//    void on_pushButton_3_clicked();

//    void on_pushButton_4_clicked();

private:
    Ui::ResaurantInformation *ui;
};
#endif // RESAURANTINFORMATION_H
