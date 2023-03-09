#ifndef USER_TOOLBAR_H
#define USER_TOOLBAR_H

#include <QWidget>
#include <QPainter>
#include <QSqlQuery>

namespace Ui {
class User_ToolBar;
}

class User_ToolBar : public QWidget
{
    Q_OBJECT

public:
    explicit User_ToolBar(QWidget *parent = nullptr,QString id_user = nullptr);
    ~User_ToolBar();
    void setUser(QString id_user);

    QString id_user;
    QString imagePath;
    int status;
signals:
    void pushButton_Order_clicked();

    void pushButton_food_clicked();

    void pushButton_MYCart_clicked();

    void pushButton_Comments_clicked();

    void pushButton_Mine_clicked();

    void pushButton_Settings_clicked();

    void pushButton_Avatar_clicked();

private slots:
    void on_pushButton_Order_clicked();

    void on_pushButton_food_clicked();

    void on_pushButton_MYCart_clicked();

    void on_pushButton_Comments_clicked();

    void on_pushButton_Mine_clicked();

    void on_pushButton_Settings_clicked();

    void on_pushButton_Avatar_clicked();

private:
    Ui::User_ToolBar *ui;
};

#endif // USER_TOOLBAR_H
