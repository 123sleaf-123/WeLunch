#include "ResaurantInformation.h"
#include "ui_ResaurantInformation.h"
#include <QDate>

int i1=1,i2=1,i3=1,i4=1;
ResaurantInformation::ResaurantInformation(QWidget *parent,QString id_DR,QString id_user)
    : QWidget(parent)
    , ui(new Ui::ResaurantInformation)
{
    ui->setupUi(this);
    setFixedSize(700,541);
    if(id_user.contains("user")){
        status = 2;
    }
    else{
        status = 1;
    }
    this->DRID = id_DR;
    queryDRname();
    queryCity();
    querycreateTime();
    querylongitude();
    querylatitude();
    queryopenTime();
    querycloseTime();
    queryCapacity();
    queryIntroduction();
    queryImagePath();
    queryBaseFare();
    queryFare();
    querysalesVolume();
    queryrating();
    querysalesNum();
    queryconsumingTime();
    querySpeed();
    queryCompensate();
    queryredPacket();
    queryRebate();
    queryFreeShipping();
    ui->lineEdit->setText(this->DRName);
    ui->lineEdit_3->setText(longitude);
    ui->lineEdit_4->setText(opentime);
    ui->lineEdit_5->setText(QString("%1").arg(BaseFare));
    ui->lineEdit_6->setText(QString("%1").arg(salesvolume));
    ui->lineEdit_7->setText(QString("%1").arg(salesnum));
    ui->lineEdit_8->setText(QString("%1").arg(capacity));
    ui->lineEdit_9->setText(city);
    ui->lineEdit_10->setText(createtime);
    ui->lineEdit_11->setText(latitude);
    ui->lineEdit_12->setText(closetime);
    ui->lineEdit_13->setText(QString("%1").arg(Fare));
    ui->lineEdit_14->setText(QString("%1").arg(rating));
    ui->lineEdit_16->setText(speed);
    ui->textEdit->setText(introduction);
    ui->pushButton_5->paintPicture(ImagePath);
}

ResaurantInformation::~ResaurantInformation()
{
    delete ui;
}


void ResaurantInformation::on_xiu_clicked()
{
    if(status == 1){
        ui->lineEdit->setEnabled(true);
        ui->lineEdit_3->setEnabled(true);
        ui->lineEdit_4->setEnabled(true);
        ui->lineEdit_5->setEnabled(true);
        ui->lineEdit_8->setEnabled(true);
        ui->lineEdit_9->setEnabled(true);
        ui->lineEdit_10->setEnabled(true);
        ui->lineEdit_11->setEnabled(true);
        ui->lineEdit_12->setEnabled(true);
        ui->lineEdit_13->setEnabled(true);
        ui->lineEdit_14->setEnabled(true);
        ui->textEdit->setEnabled(true);
//        ui->pushButton->setEnabled(1);
//        ui->pushButton_2->setEnabled(1);
//        ui->pushButton_3->setEnabled(1);
//        ui->pushButton_4->setEnabled(1);
    }
    else{
        ui->xiu->hide();
    }
}


void ResaurantInformation::on_wan_clicked()
{
    ui->lineEdit->setEnabled(0);
    ui->lineEdit_3->setEnabled(0);
    ui->lineEdit_4->setEnabled(0);
    ui->lineEdit_5->setEnabled(0);
    ui->lineEdit_6->setEnabled(0);
    ui->lineEdit_7->setEnabled(0);
    ui->lineEdit_8->setEnabled(0);
    ui->lineEdit_9->setEnabled(0);
    ui->lineEdit_10->setEnabled(0);
    ui->lineEdit_11->setEnabled(0);
    ui->lineEdit_12->setEnabled(0);
    ui->lineEdit_13->setEnabled(0);
    ui->lineEdit_14->setEnabled(0);
    ui->lineEdit_16->setEnabled(0);
    ui->textEdit->setEnabled(0);
//    ui->pushButton->setEnabled(0);
//    ui->pushButton_2->setEnabled(0);
//    ui->pushButton_3->setEnabled(0);
//    ui->pushButton_4->setEnabled(0);

    this->DRName = ui->lineEdit->text();
    longitude = ui->lineEdit_3->text();
    opentime = ui->lineEdit_4->text();
    BaseFare = ui->lineEdit_5->text().toFloat();
    capacity = ui->lineEdit_8->text().toInt();
    city = ui->lineEdit_9->text();
    latitude = ui->lineEdit_11->text();
    closetime = ui->lineEdit_12->text();
    Fare = ui->lineEdit_13->text().toFloat();
    introduction = ui->textEdit->toPlainText();

    queryreDRname();
    queryreCity();
    queryrelongitude();
    queryrelatitude();
    queryreopenTime();
    queryrecloseTime();
    queryreCapacity();
    queryreIntroduction();
//    queryreImagePath();
    queryreBaseFare();
    queryreFare();
//    queryresalesVolume();
//    queryrerating();
//    queryresalesNum();
//    queryreconsumingTime();
//    queryreSpeed();
    queryreCompensate();
    queryreredPacket();
    queryreRebate();
    queryreFreeShipping();
}


//void ResaurantInformation::on_pushButton_clicked()
//{
//    i1=-i1;
//    if(i1==-1)
//        ui->pushButton->setText(" ");
//    else
//        ui->pushButton->setText("√");
//}


//void ResaurantInformation::on_pushButton_2_clicked()
//{
//    i2=-i2;
//    if(i2==-1)
//        ui->pushButton_2->setText(" ");
//    else
//        ui->pushButton_2->setText("√");
//}


//void ResaurantInformation::on_pushButton_3_clicked()
//{
//    i3=-i3;
//    if(i3==-1)
//        ui->pushButton_3->setText(" ");
//    else
//        ui->pushButton_3->setText("√");
//}


//void ResaurantInformation::on_pushButton_4_clicked()
//{
//    i4=-i4;
//    if(i4==-1)
//        ui->pushButton_4->setText(" ");
//    else
//        ui->pushButton_4->setText("√");
//}

//查询餐厅名
void ResaurantInformation::queryDRname(){
    QSqlQuery query;
    query.prepare("select DRName from DRinfo where DRID = :a");
    query.bindValue(0,DRID);
    query.exec();
    query.next();
    DRName = query.value(0).toString();
    this->setWindowTitle(DRName);
    query.clear();
}
//查询创建时间
void ResaurantInformation::querycreateTime(){
    QSqlQuery query;
    query.prepare("select createTime from DRinfo where DRID = :a");
    query.bindValue(0,DRID);
    query.exec();
    query.next();
    QDate date = query.value(0).toDate();
    createtime = date.toString("yyyy-MM-dd");
    query.clear();
}
//查询城市
void ResaurantInformation::queryCity(){
    QSqlQuery query;
    query.prepare("select city from DRinfo where DRID = :a");
    query.bindValue(0,DRID);
    query.exec();
    query.next();
    city = query.value(0).toString();
    query.clear();
}
//查询经度
void ResaurantInformation::querylongitude(){
    QSqlQuery query;
    query.prepare("select longitude from DRinfo where DRID = :a");
    query.bindValue(0,DRID);
    query.exec();
    query.next();
    longitude = query.value(0).toString();
    query.clear();
}
//查询纬度
void ResaurantInformation::querylatitude(){
    QSqlQuery query;
    query.prepare("select latitude from DRinfo where DRID = :a");
    query.bindValue(0,DRID);
    query.exec();
    query.next();
    latitude = query.value(0).toString();
    query.clear();
}
//开始营业时间
void ResaurantInformation::queryopenTime(){
    QSqlQuery query;
    query.prepare("select openTime from DRinfo where DRID = :a");
    query.bindValue(0,DRID);
    query.exec();
    query.next();
    opentime = query.value(0).toString();
    query.clear();
}
//结束营业时间
void ResaurantInformation::querycloseTime(){
    QSqlQuery query;
    query.prepare("select closeTime from DRinfo where DRID = :a");
    query.bindValue(0,DRID);
    query.exec();
    query.next();
    closetime = query.value(0).toString();
    query.clear();
}
//接待能力上限
void ResaurantInformation::queryCapacity(){
    QSqlQuery query;
    query.prepare("select capacity from DRinfo where DRID = :a");
    query.bindValue(0,DRID);
    query.exec();
    query.next();
    capacity = query.value(0).toInt();
    query.clear();
}
//简介
void ResaurantInformation::queryIntroduction(){
    QSqlQuery query;
    query.prepare("select introduction from DRinfo where DRID = :a");
    query.bindValue(0,DRID);
    query.exec();
    query.next();
    introduction = query.value(0).toString();
    query.clear();
}
//图片路径
void ResaurantInformation::queryImagePath(){
    QSqlQuery query;
    query.prepare("select ImagePath from DRinfo where DRID = :a");
    query.bindValue(0,DRID);
    query.exec();
    query.next();
    ImagePath = query.value(0).toString();
    QPixmap pix;
    pix.load(ImagePath);
    this->setWindowIcon(QIcon(pix));
    query.clear();
}
//起送价
void ResaurantInformation::queryBaseFare(){
    QSqlQuery query;
    query.prepare("select BaseFare from DRinfo where DRID = :a");
    query.bindValue(0,DRID);
    query.exec();
    query.next();
    BaseFare = query.value(0).toInt();
    query.clear();
}
//配送费
void ResaurantInformation::queryFare(){
    QSqlQuery query;
    query.prepare("select Fare from DRinfo where DRID = :a");
    query.bindValue(0,DRID);
    query.exec();
    query.next();
    Fare = query.value(0).toFloat();
    query.clear();
}
//销量
void ResaurantInformation::querysalesVolume(){
    QSqlQuery query;
    query.prepare("select salesVolume from DRinfo where DRID = :a");
    query.bindValue(0,DRID);
    query.exec();
    query.next();
    salesvolume = query.value(0).toInt();
    query.clear();
}
//评分
void ResaurantInformation::queryrating(){
    QSqlQuery query;
    query.prepare("select rating from DRinfo where DRID = :a");
    query.bindValue(0,DRID);
    query.exec();
    query.next();
    rating = query.value(0).toFloat();
    query.clear();
}
//外卖订单数量
void ResaurantInformation::querysalesNum(){
    QSqlQuery query;
    query.prepare("select salesNum from DRinfo where DRID = :a");
    query.bindValue(0,DRID);
    query.exec();
    query.next();
    salesnum = query.value(0).toInt();
    query.clear();
}
//外卖订单总耗时
void ResaurantInformation::queryconsumingTime(){
    QSqlQuery query;
    query.prepare("select consumingTime from DRinfo where DRID = :a");
    query.bindValue(0,DRID);
    query.exec();
    query.next();
    consumingtime = query.value(0).toFloat();
    query.clear();
}
//配送速度
void ResaurantInformation::querySpeed(){
    QSqlQuery query;
    query.prepare("select speed from DRinfo where DRID = :a");
    query.bindValue(0,DRID);
    query.exec();
    query.next();
    speed = query.value(0).toString();
    query.clear();
}
//补偿
void ResaurantInformation::queryCompensate(){
    QSqlQuery query;
    query.prepare("select compensate from DRinfo where DRID = :a");
    query.bindValue(0,DRID);
    query.exec();
    query.next();
    compensate = query.value(0).toBool();
    query.clear();
}
// 红包
void ResaurantInformation::queryredPacket(){
    QSqlQuery query;
    query.prepare("select redPacket from DRinfo where DRID = :a");
    query.bindValue(0,DRID);
    query.exec();
    query.next();
    redpacket = query.value(0).toBool();
    query.clear();
}
//返券
void ResaurantInformation::queryRebate(){
    QSqlQuery query;
    query.prepare("select rebate from DRinfo where DRID = :a");
    query.bindValue(0,DRID);
    query.exec();
    query.next();
    rebate = query.value(0).toBool();
    query.clear();
}
//配送费
void ResaurantInformation::queryFreeShipping(){
    QSqlQuery query;
    query.prepare("select freeShipping from DRinfo where DRID = :a");
    query.bindValue(0,DRID);
    query.exec();
    query.next();
    freeshipping = query.value(0).toBool();
    query.clear();
}

//修改名字
void ResaurantInformation::queryreDRname(){
    QSqlQuery query;
    query.prepare( "update DRinfo SET DRName=:a  where DRID = :b");
    query.bindValue(0,DRName);
    query.bindValue(1,DRID);
    query.exec();
    query.clear();
}
//修改城市
void ResaurantInformation::queryreCity(){
    QSqlQuery query;
    query.prepare( "update DRinfo SET city=:a  where DRID = :b");
    query.bindValue(0,city);
    query.bindValue(1,DRID);
    query.exec();
    query.clear();
}
//修改创建时间
void ResaurantInformation::queryrecreateTime(){
    QSqlQuery query;
    query.prepare( "update DRinfo SET createTime=:a  where DRID = :b");
    query.bindValue(0,createtime);
    query.bindValue(1,DRID);
    query.exec();
    query.clear();
}
//修改经度
void ResaurantInformation::queryrelongitude(){
    QSqlQuery query;
    query.prepare( "update DRinfo SET longitude=:a  where DRID = :b");
    query.bindValue(0,longitude);
    query.bindValue(1,DRID);
    query.exec();
    query.clear();
}
//修改纬度
void ResaurantInformation::queryrelatitude(){
    QSqlQuery query;
    query.prepare( "update DRinfo SET latitude=:a  where DRID = :b");
    query.bindValue(0,latitude);
    query.bindValue(1,DRID);
    query.exec();
    query.clear();
}
//修改开始营业时间
void ResaurantInformation::queryreopenTime(){
    QSqlQuery query;
    query.prepare( "update DRinfo SET openTime=:a  where DRID = :b");
    query.bindValue(0,opentime);
    query.bindValue(1,DRID);
    query.exec();
    query.clear();
}
//修改结束营业时间
void ResaurantInformation::queryrecloseTime(){
    QSqlQuery query;
    query.prepare( "update DRinfo SET closeTime=:a  where DRID = :b");
    query.bindValue(0,closetime);
    query.bindValue(1,DRID);
    query.exec();
    query.clear();
}
//修改容纳量
void ResaurantInformation::queryreCapacity(){
    QSqlQuery query;
    query.prepare( "update DRinfo SET capacity=:a  where DRID = :b");
    query.bindValue(0,capacity);
    query.bindValue(1,DRID);
    query.exec();
    query.clear();
}
//修改简介
void ResaurantInformation::queryreIntroduction(){
    QSqlQuery query;
    query.prepare( "update DRinfo SET introduction=:a  where DRID = :b");
    query.bindValue(0,introduction);
    query.bindValue(1,DRID);
    query.exec();
    query.clear();
}
//修改图片路径
void ResaurantInformation::queryreImagePath(){
    QSqlQuery query;
    query.prepare( "update DRinfo SET ImagePath=:a  where DRID = :b");
    query.bindValue(0,ImagePath);
    query.bindValue(1,DRID);
    query.exec();
    query.clear();
}
//修改最低起送价
void ResaurantInformation::queryreBaseFare(){
    QSqlQuery query;
    query.prepare( "update DRinfo SET BaseFare=:a  where DRID = :b");
    query.bindValue(0,BaseFare);
    query.bindValue(1,DRID);
    query.exec();
    query.clear();
}
//修改配送费
void ResaurantInformation::queryreFare(){
    QSqlQuery query;
    query.prepare( "update DRinfo SET Fare=:a  where DRID = :b");
    query.bindValue(0,Fare);
    query.bindValue(1,DRID);
    query.exec();
    query.clear();
}
//修改销量
void ResaurantInformation::queryresalesVolume(){
    QSqlQuery query;
    query.prepare( "update DRinfo SET salesVolume=:a  where DRID = :b");
    query.bindValue(0,salesvolume);
    query.bindValue(1,DRID);
    query.exec();
    query.clear();
}
//修改评分
void ResaurantInformation::queryrerating(){
    QSqlQuery query;
    query.prepare( "update DRinfo SET rating=:a  where DRID = :b");
    query.bindValue(0,rating);
    query.bindValue(1,DRID);
    query.exec();
    query.clear();
}
//修改订单量
void ResaurantInformation::queryresalesNum(){
    QSqlQuery query;
    query.prepare( "update DRinfo SET salesNum=:a  where DRID = :b");
    query.bindValue(0,salesnum);
    query.bindValue(1,DRID);
    query.exec();
    query.clear();
}
//修改耗时
void ResaurantInformation::queryreconsumingTime(){
    QSqlQuery query;
    query.prepare( "update DRinfo SET consumingTime=:a  where DRID = :b");
    query.bindValue(0,consumingtime);
    query.bindValue(1,DRID);
    query.exec();
    query.clear();
}
//修改速度
void ResaurantInformation::queryreSpeed(){
    QSqlQuery query;
    query.prepare( "update DRinfo SET speed=:a  where DRID = :b");
    query.bindValue(0,speed);
    query.bindValue(1,DRID);
    query.exec();
    query.clear();
}
//修改赔付
void ResaurantInformation::queryreCompensate(){
    QSqlQuery query;
    query.prepare( "update DRinfo SET compensate=:a  where DRID = :b");
    query.bindValue(0,compensate);
    query.bindValue(1,DRID);
    query.exec();
    query.clear();
}
//修改红包
void ResaurantInformation::queryreredPacket(){
    QSqlQuery query;
    query.prepare( "update DRinfo SET redPacket=:a  where DRID = :b");
    query.bindValue(0,redpacket);
    query.bindValue(1,DRID);
    query.exec();
    query.clear();
}
//修改返券
void ResaurantInformation::queryreRebate(){
    QSqlQuery query;
    query.prepare( "update DRinfo SET rebate=:a  where DRID = :b");
    query.bindValue(0,rebate);
    query.bindValue(1,DRID);
    query.exec();
    query.clear();
}
//修改免配送费
void ResaurantInformation::queryreFreeShipping(){
    QSqlQuery query;
    query.prepare( "update DRinfo SET freeShipping=:a  where DRID = :b");
    query.bindValue(0,freeshipping);
    query.bindValue(1,DRID);
    query.exec();
    query.clear();
}
