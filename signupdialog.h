#ifndef SIGNUPDIALOG_H
#define SIGNUPDIALOG_H

#include <QDialog>
#include <QString>
#include <QAbstractButton>
#include <QPainter>
#include <QSqlQuery>
#include <QMessageBox>
#include <QCheckBox>


int checkPassword(char *str );

namespace Ui {
class SignUpDialog;
}

class SignUpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SignUpDialog(QWidget *parent = nullptr);
    ~SignUpDialog();
    void paintEvent(QPaintEvent *);
    void check();
    QString str1,str2,str3,str4,str5,str6;
    char username[20];char password[20];char phonenum[20];char name[20]; char email[30];char chpassword[20];
    bool nameCheck, pwdCheck, phonenumCheck, rNameCheck, mailCheck, pwdSureCheck;
    QSqlQuery q;
    QString id_user;
    int userType;

private slots:

    void on_lineEdit_AccountName_editingFinished();

    void on_lineEdit_Password_editingFinished();

    void on_lineEdit_CheckPwd_editingFinished();

    void on_lineEdit_Mail_editingFinished();

    void on_lineEdit_RealName_editingFinished();

    void on_lineEdit_PhoneNumber_editingFinished();

    void on_comboBox_user_currentIndexChanged(int index);

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::SignUpDialog *ui;
};




#endif // SIGNUPDIALOG_H
