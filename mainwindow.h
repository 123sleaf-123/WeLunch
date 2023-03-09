#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "orderwidget.h"
#include "foodshopwidegt.h"
#include "widget.h"
#include "peopleinformation.h"
#include "drwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *);
    void setUser(QString id_user);
    OrderWidget *ow;
    FoodShopWidegt *fsw;
    PeopleInformation *piw;
    Widget *cw;

    QRect scrollAreaWidgetContentsrect;
    QSize scrollAreaWidgetContentsSize;
    QString id_user;
    int status;

public slots:
    void setupOrderWidget();
    void setupFoodShopWidget();
    void setupCommentsWidget();
    void setupMyInfoWidget();
    void setupCartWidget();
    void changeShowPage();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
