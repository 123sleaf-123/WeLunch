#include "foodinformation.h"
#include "ui_foodinformation.h"

FoodInformation::FoodInformation(QWidget *parent,QString id_DR,QString id_food)
    : QWidget(parent)
    , ui(new Ui::FoodInformation)
{
    ui->setupUi(this);
    setFixedSize(700,541);
    this->Id_food = id_food;
    this->id_DR = id_DR;
    if(!id_food.isEmpty())
    {
        queryFoodName();
        queryPrice();
        queryfoodDescription();
        queryfoodIngredient();
        queryfoodTaste();
        queryfoodVolume();
        queryimagepath();
        querysales();
        ui->name->setText(FoodName);
        ui->price->setText(QString("%1").arg(price));
        ui->id->setText(id_food);
        ui->weight->setText(foodVolume);
        ui->sell->setText(QString("%1").arg(sales));
        ui->textEdit->setText(foodDescription);
        ui->textEdit_2->setText(foodIngredient);
        ui->textEdit_3->setText(foodTaste);
        ui->pushButton_pictofood->paintPicture(imagepath);
        qOa = 1;
    }
    else{
        setWindowTitle("添加食品");
        qOa = 0;
    }
}

FoodInformation::~FoodInformation()
{
    delete ui;
}


void FoodInformation::on_xiu_clicked()
{
    ui->id->setEnabled(true);
    ui->name->setEnabled(true);
    ui->price->setEnabled(true);
    ui->weight->setEnabled(true);
    ui->textEdit->setEnabled(true);
    ui->textEdit_2->setEnabled(true);
    ui->textEdit_3->setEnabled(true);
}


void FoodInformation::on_wan_clicked()
{
    FoodName = ui->name->text();
    price = ui->price->text().toFloat();
    Id_food = ui->id->text();
    foodVolume = ui->weight->text();
    foodDescription = ui->textEdit->toPlainText();
    foodIngredient = ui->textEdit_2->toPlainText();
    foodTaste = ui->textEdit_3->toPlainText();
    if(qOa == 1)
    {
        queryreFoodId();
        queryreFoodName();
        queryrePrice();
        queryrefoodDescription();
        queryrefoodIngredient();
        queryrefoodTaste();
        queryrefoodVolume();
    }
    else{
        QSqlQuery q;
        q.prepare("insert into food (Id_food, FoodName, price, Id_DR, foodDescription, foodIngredient, foodTaste, foodVolume) values (:a,:b,:c,:d,:e,:f,:g,:h)");
        q.bindValue(0,Id_food);
        q.bindValue(1,FoodName);
        q.bindValue(2,price);
        q.bindValue(3,id_DR);
        q.bindValue(4,foodDescription);
        q.bindValue(5,foodIngredient);
        q.bindValue(6,foodTaste);
        q.bindValue(7,foodVolume);
        q.exec();
    }
    ui->id->setEnabled(false);
    ui->name->setEnabled(false);
    ui->price->setEnabled(false);
    ui->weight->setEnabled(false);
    ui->textEdit->setEnabled(false);
    ui->textEdit_2->setEnabled(false);
    ui->textEdit_3->setEnabled(false);
}

void FoodInformation::queryFoodName(){
    QSqlQuery query;
    query.prepare("select foodname from food where id_food = :a and id_DR= :b");
    query.bindValue(0,Id_food);
    query.bindValue(1,id_DR);
    query.exec();
    query.next();
    FoodName = query.value(0).toString();
    this->setWindowTitle(FoodName);
    query.clear();
}

//查询价格
void FoodInformation::queryPrice(){
    QSqlQuery query;
    query.prepare("select price from food where id_food = :a and id_DR= :b");
    query.bindValue(0,Id_food);
    query.bindValue(1,id_DR);
    query.exec();
    query.next();
    price = query.value(0).toFloat();
    query.clear();
}

//查询描述
void FoodInformation::queryfoodDescription(){
    QSqlQuery query;
    query.prepare("select foodDescription from food where id_food = :a and id_DR= :b");
    query.bindValue(0,Id_food);
    query.bindValue(1,id_DR);
    query.exec();
    query.next();
    foodDescription = query.value(0).toString();
    query.clear();
}

//查询用料
void FoodInformation::queryfoodIngredient(){
    QSqlQuery query;
    query.prepare("select foodIngredient from food where id_food = :a and id_DR= :b");
    query.bindValue(0,Id_food);
    query.bindValue(1,id_DR);
    query.exec();
    query.next();
    foodIngredient = query.value(0).toString();
    query.clear();
}

//查询口味
void FoodInformation::queryfoodTaste(){
    QSqlQuery query;
    query.prepare("select foodTaste from food where id_food = :a and id_DR= :b");
    query.bindValue(0,Id_food);
    query.bindValue(1,id_DR);
    query.exec();
    query.next();
    foodTaste = query.value(0).toString();
    query.clear();
}
//查询分量
void FoodInformation::queryfoodVolume(){
    QSqlQuery query;
    query.prepare("select foodVolume from food where id_food = :a and id_DR= :b");
    query.bindValue(0,Id_food);
    query.bindValue(1,id_DR);
    query.exec();
    query.next();
    foodVolume = query.value(0).toString();
    query.clear();
}

//查询图片
void FoodInformation::queryimagepath(){
    QSqlQuery query;
    query.prepare("select imagepath from food where id_food = :a and id_DR= :b");
    query.bindValue(0,Id_food);
    query.bindValue(1,id_DR);
    query.exec();
    query.next();
    imagepath = query.value(0).toString();
    QPixmap pix;
    pix.load(imagepath);
    this->setWindowIcon(pix);
    query.clear();
}

//查询销量
void FoodInformation::querysales(){
    QSqlQuery query;
    query.prepare("select sales from food where id_food = :a and id_DR= :b");
    query.bindValue(0,Id_food);
    query.bindValue(1,id_DR);
    query.exec();
    query.next();
    sales = query.value(0).toInt();
    query.clear();
}

void FoodInformation::setStatus(int status){
    this->status = status;
    if(status == 2){
        ui->xiu->hide();
        ui->wan->hide();
    }
}

void FoodInformation::queryreFoodId(){
    QSqlQuery query;
    query.prepare( "update food SET id_food=:a  where Id_food = :b");
    query.bindValue(0,Id_food);
    query.bindValue(1,Id_food);
    query.exec();
    query.clear();
}

//修改菜名
void FoodInformation::queryreFoodName(){
    QSqlQuery query;
    query.prepare( "update food SET foodname=:a  where Id_food = :b");
    query.bindValue(0,FoodName);
    query.bindValue(1,Id_food);
    query.exec();
    query.clear();
}
//修改价格
void FoodInformation::queryrePrice(){
    QSqlQuery query;
    query.prepare( "update food SET price=:a  where Id_food = :b");
    query.bindValue(0,price);
    query.bindValue(1,Id_food);
    query.exec();
    query.clear();
}
//修改描述
void FoodInformation::queryrefoodDescription(){
    QSqlQuery query;
    query.prepare( "update food SET foodDescription=:a  where Id_food = :b");
    query.bindValue(0,foodDescription);
    query.bindValue(1,Id_food);
    query.exec();
    query.clear();
}
//修改用料
void FoodInformation::queryrefoodIngredient(){
    QSqlQuery query;
    query.prepare( "update food SET foodIngredient=:a  where Id_food = :b");
    query.bindValue(0,foodIngredient);
    query.bindValue(1,Id_food);
    query.exec();
    query.clear();
}
//修改口味
void FoodInformation::queryrefoodTaste(){
    QSqlQuery query;
    query.prepare( "update food SET foodTaste=:a  where Id_food = :b");
    query.bindValue(0,foodTaste);
    query.bindValue(1,Id_food);
    query.exec();
    query.clear();
}
//修改分量
void FoodInformation::queryrefoodVolume(){
    QSqlQuery query;
    query.prepare( "update food SET foodVolume=:a  where Id_food = :b");
    query.bindValue(0,foodVolume);
    query.bindValue(1,Id_food);
    query.exec();
    query.clear();
}

void FoodInformation::querynewFoodId(){
    QSqlQuery query;
    query.prepare( "update food SET id_food=:a  where Id_food = :b");
    query.bindValue(0,Id_food);
    query.bindValue(1,Id_food);
    query.exec();
    query.clear();
}

//修改菜名
void FoodInformation::querynewFoodName(){
    QSqlQuery query;
    query.prepare( "update food SET foodname=:a  where Id_food = :b");
    query.bindValue(0,FoodName);
    query.bindValue(1,Id_food);
    query.exec();
    query.clear();
}
//修改价格
void FoodInformation::querynewPrice(){
    QSqlQuery query;
    query.prepare( "update food SET price=:a  where Id_food = :b");
    query.bindValue(0,price);
    query.bindValue(1,Id_food);
    query.exec();
    query.clear();
}
//修改描述
void FoodInformation::querynewfoodDescription(){
    QSqlQuery query;
    query.prepare( "update food SET foodDescription=:a  where Id_food = :b");
    query.bindValue(0,foodDescription);
    query.bindValue(1,Id_food);
    query.exec();
    query.clear();
}
//修改用料
void FoodInformation::querynewfoodIngredient(){
    QSqlQuery query;
    query.prepare( "update food SET foodIngredient=:a  where Id_food = :b");
    query.bindValue(0,foodIngredient);
    query.bindValue(1,Id_food);
    query.exec();
    query.clear();
}
//修改口味
void FoodInformation::querynewfoodTaste(){
    QSqlQuery query;
    query.prepare( "update food SET foodTaste=:a  where Id_food = :b");
    query.bindValue(0,foodTaste);
    query.bindValue(1,Id_food);
    query.exec();
    query.clear();
}
//修改分量
void FoodInformation::querynewfoodVolume(){
    QSqlQuery query;
    query.prepare( "update food SET foodVolume=:a  where Id_food = :b");
    query.bindValue(0,foodVolume);
    query.bindValue(1,Id_food);
    query.exec();
    query.clear();
}
