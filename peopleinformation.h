#ifndef PEOPLEINFORMATION_H
#define PEOPLEINFORMATION_H

#include <QWidget>
#include <QSqlQuery>

QT_BEGIN_NAMESPACE
namespace Ui { class PeopleInformation; }
QT_END_NAMESPACE

class PeopleInformation : public QWidget
{
    Q_OBJECT

public:
    PeopleInformation(QWidget *parent = nullptr,QString id_user = nullptr);
    ~PeopleInformation();
    void  changetype();

    void queryUsername();
    void queryRealname();
    void queryAdress();
    void queryLongitude();
    void queryLatitude();
    void queryPassword();
    void queryTelenum();
    void queryMailbox();
    void queryrepassword();
    void queryretelenum();
    void queryremailbox();

    QString Id_user;
    QString username;
    QString realname;
    QString address;
    QString longitude;
    QString latitude;
    QString password;
    QString teleNum;
    QString mailbox;


private slots:
    void on_change_number_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::PeopleInformation *ui;

};
#endif // PEOPLEINFORMATION_H
