#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QSqlQuery>

typedef struct UserNode
{
    char id_user[20];
    char Password[20];//加一个密码字符数组
    char UserName[20];
    struct UserNode* next;
} *UserList;

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();
    void ShowPicture();
    QSqlQuery * queryPwd();
    void checkPwd();
    UserList createLinkedList(QSqlQuery *q);
    int checkId(QString temid, QString tempassword, struct UserNode* head);
    void paintEvent(QPaintEvent *);
    void captchaCreate();

    QString id_user;
    QString UserName;
    int FailTime;
    char seed[90] = "123456789abcdefg123456789hijklmnopqrstuvwxyz123456789ABCDEFG123456789HIJKLMNOPQRSTUVWXYZ";

private:
    Ui::LoginDialog *ui;
    QString pwd_user;
    QString captcha;
public slots:
    void LoginCheck();
private slots:
    void on_buttonBox_accepted();
    void on_regist_clicked();
    void on_finpwd_clicked();
    void on_pushButto_change_clicked();
};

#endif // LOGINDIALOG_H
