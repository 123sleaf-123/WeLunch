#include "drcard.h"
#include "ui_drcard.h"
#include "drwidget.h" // 暂时

DRCard::DRCard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DRCard)
{
    ui->setupUi(this);
}


void DRCard::setDRID(QString id_DR){
    this->id_DR = id_DR;
}

void DRCard::setImagePath(QString ImagePath){
    this->ImagePath = ImagePath;
    ui->pushButton_PicToDR->paintPicture(ImagePath);
}

void DRCard::setDRName(QString DRName){
    this->DRName = DRName;
    ui->pushButton_TextToDR->setText(DRName);
}

void DRCard::setDRRatings(float DRRatings){
    this->DRRatings = DRRatings;
    ui->Ratings->setText(QString("%1").arg(DRRatings));
}

void DRCard::setDRSpeed(QString DRSpeed){
    this->DRSpeed = DRSpeed;
    ui->Speed->setText(DRSpeed);
}

void DRCard::setDistance(float Distance){
    this->Distance = Distance;
    ui->Distance->setText(QString("%1米").arg(Distance));
}

void DRCard::setSales(int DRSales){
    this->DRSales = DRSales;
    this->ui->SalesVolumn->setText(QString("%1").arg(DRSales));
}

DRCard::~DRCard()
{
    delete ui;
}

void DRCard::on_pushButton_PicToDR_clicked()
{
    DRWidget *w = new DRWidget(this->parentWidget()->parentWidget()->parentWidget());
    w->id_user = id_user;
    w->setDRid(id_DR);
    this->parentWidget()->parentWidget()->hide();
    QPushButton *Returnbtn = new QPushButton(w);
    Returnbtn->setText("返回");
    w->show();
    Returnbtn->show();
    connect(Returnbtn, &QPushButton::clicked, [=](){
       w->close();
       this->parentWidget()->parentWidget()->show();
       delete w;
    });
}

