#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPushButton>
#include <QWidget>
#include "cart.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    this->setWindowTitle("微餐");

    connect(this->ui->toolbar,&User_ToolBar::pushButton_food_clicked,
            this,&MainWindow::setupFoodShopWidget);
    connect(this->ui->toolbar,&User_ToolBar::pushButton_Order_clicked,
            this,&MainWindow::setupOrderWidget);
    connect(this->ui->toolbar,&User_ToolBar::pushButton_Comments_clicked,
            this,&MainWindow::setupCommentsWidget);
    connect(this->ui->toolbar,&User_ToolBar::pushButton_Avatar_clicked,
            this,&MainWindow::setupMyInfoWidget);
    connect(this->ui->toolbar,&User_ToolBar::pushButton_Mine_clicked,
            this,&MainWindow::setupMyInfoWidget);
    connect(this->ui->toolbar,&User_ToolBar::pushButton_MYCart_clicked,
            this,&MainWindow::setupCartWidget);

//    connect(this,&QPushButton::clicked,this,&MainWindow::changeShowPage);
}

void MainWindow::setupMyInfoWidget(){
    piw = new PeopleInformation(nullptr,id_user);
    piw->show();
}


void MainWindow::setupOrderWidget(){
    changeShowPage();
    ow = new OrderWidget(this->ui->scrollAreaWidgetContents);
    ow->setUser(id_user,status);
    ow->show();
}

void MainWindow::setupFoodShopWidget(){
    changeShowPage();
    if(status == 2)
    {
        fsw = new FoodShopWidegt(this->ui->scrollAreaWidgetContents,id_user);
        fsw->show();
    }
    if(status == 1){
        DRWidget *dw = new DRWidget(this->ui->scrollAreaWidgetContents,id_user);
        dw->show();
    }
}

void MainWindow::setupCommentsWidget(){
    changeShowPage();
    cw = new Widget(this->ui->scrollAreaWidgetContents);
    cw->setUser(id_user,status);
    cw->show();
}

void MainWindow::setupCartWidget(){
    changeShowPage();
    Cart *cw = new Cart(this->ui->scrollAreaWidgetContents);
    cw->setWindowTitle("购物车");
    cw->id_user = id_user;
    cw->queryCards();
    cw->setupCartCards();
    cw->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 关闭子窗口
void MainWindow::changeShowPage(){
    QWidget *widegt = ui->scrollAreaWidgetContents->findChild<QWidget *>("DRWidget",Qt::FindDirectChildrenOnly);
    if(widegt != NULL && widegt->isActiveWindow()){
        widegt->close();
        delete widegt;
    }
//    widegt = ui->scrollAreaWidgetContents->findChild<QWidget *>("OrderListWidegt",Qt::FindDirectChildrenOnly);
//    if(widegt != NULL && widegt->isActiveWindow()){
//        widegt->close();
//        delete widegt;
//    }
    widegt = ui->scrollAreaWidgetContents->findChild<QWidget *>(QString(),Qt::FindDirectChildrenOnly);
    if(widegt != NULL && widegt->isActiveWindow())
    {
        widegt->close();
        delete widegt;
    }
//    QList<QWidget *> widgets = ui->scrollAreaWidgetContents->findChildren<QWidget *>(,Qt::FindChildrenRecursively);
//    for (int i = 0 ; i < widgets.count() ; i++ ) {
//        QWidget *w = widgets.at(i);
//        delete w;
//    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    // 反走样
    painter.setRenderHint(QPainter::Antialiasing, true);

    // 设置渐变色,设置起点、终点
    QLinearGradient linear(0, 0, 900, 600);
    linear.setColorAt(0, QColor("#B993D6"));
    linear.setColorAt(1, QColor("#8CA6DB"));

    // 设置显示模式
    linear.setSpread(QGradient::PadSpread);

    // 设置画笔颜色、宽度
    painter.setPen(QPen(QColor(255, 255, 255, 0), 1));

    // 设置画刷填充
    painter.setBrush(QBrush(linear));

    // 绘制矩形
    painter.drawRect(QRect(0, 0, 900, 600));

}

void MainWindow::setUser(QString id_user){
    this->id_user = id_user;
    if(id_user.contains("user",Qt::CaseInsensitive)){
        status = 2; // 用户
    }
    else if(id_user.contains("DR",Qt::CaseInsensitive)){
        status = 1; // 商家
    }
    ui->toolbar->status = status;
    ui->toolbar->setUser(id_user);
    setupFoodShopWidget();
}
