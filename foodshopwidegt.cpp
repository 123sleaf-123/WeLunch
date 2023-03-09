#include "foodshopwidegt.h"
#include "ui_foodshopwidegt.h"
#include "drcard.h"
#include "smartorder.h"
#include "drwidget.h"


FoodShopWidegt::FoodShopWidegt(QWidget *parent,QString id_user) :
    QWidget(parent),
    ui(new Ui::FoodShopWidegt)
{
    ui->setupUi(this);
    this->resize(700,1300);
    this->id_user = id_user;
    if(id_user.contains("user")){
        status = 2;
    }
    else{
        if(!id_user.isNull()){
            status = 1;
        }
    }
    if(status == 2){
        ui->DRCardWidget->resize(600,1200);
        this->ui->horizontalLayoutWidget->resize(600,30);
        // 图片 店名 id 评分 经度 纬度 送餐速度 销量   菜系 赔付 红包 免配送费
        this->SelectMode_DRType = 0;
        this->SelectMode_Addition = 0;
        this->SortMode_DeFault = 0;
        this->SortMode_Distance = 0;
        FSWLLManager = new FoodShopWidgetLinkedListDeal;
        setupDRCard(FSWLLManager->head);
    }
    else{
        ui->horizontalLayoutWidget->close();
        ui->DRCardWidget->close();
        ui->layoutWidget->close();
        DRWidget *drw = new DRWidget(this,id_user);
        drw->show();
    }
}

void FoodShopWidegt::OrderByGrade_LinkedList(){

}

FoodShopWidegt::~FoodShopWidegt()
{
    delete ui;
}

// 选择菜系框
void FoodShopWidegt::on_comboBox_4_currentIndexChanged(int index)
{
    SelectMode_DRType = index;
}


void FoodShopWidegt::on_comboBox_3_currentIndexChanged(int index)
{
    SortMode_Distance = index;
}


void FoodShopWidegt::on_comboBox_currentIndexChanged(int index)
{
    SortMode_DeFault = index;
}



void FoodShopWidegt::on_comboBox_2_currentIndexChanged(int index)
{
    SelectMode_Addition = index;
}

void FoodShopWidegt::setupDRCard(DRList head){
    DRList PtrL = head;
    for(int count = 0 ; PtrL ; count++, PtrL = PtrL->next){
        // 设置食物卡片位置
        DRCard *card = new DRCard(this->ui->DRCardWidget);
        card->id_user = id_user;
        card->setDRID(PtrL->Id_DR);
        card->setImagePath(PtrL->DRImagePath);
        card->setDRName(PtrL->DRName);
        card->setDRRatings(PtrL->DRgrade);
        card->setDRSpeed(PtrL->DRAvgDeliveryTime);
        card->setDistance(PtrL->Disatance);
        card->setSales(PtrL->DRSales);
        card->move(10,this->ui->horizontalLayoutWidget->height()+count*100);
        card->resize(600,100);
    }
    // count--;
}

void FoodShopWidegt::changeShowPage(){
    ui->DRCardWidget->close();
    DRCardWidgetrect = ui->DRCardWidget->geometry();
    delete ui->DRCardWidget;
    ui->DRCardWidget = new QWidget(this);
    ui->DRCardWidget->resize(600,1200);
    ui->DRCardWidget->setGeometry(DRCardWidgetrect);
}

void FoodShopWidegt::sortDefault(){
    switch (SortMode_DeFault) {
    case 0:
        qDebug("选择了智能排序");
        this->FSWLLManager->ShowListHead = smartOrder(this->FSWLLManager->ShowListHead,
                                                      int(this->FSWLLManager->sales/this->FSWLLManager->length),
                                                      this->FSWLLManager->score/this->FSWLLManager->length,
                                                      int(this->FSWLLManager->speed/this->FSWLLManager->length));
        break;
    case 1:
        qDebug("选择了销量排序");
        this->FSWLLManager->ShowListHead = this->FSWLLManager->orderbySales(this->FSWLLManager->ShowListHead);
        break;
    case 2:
        qDebug("选择了评分排序");
        this->FSWLLManager->ShowListHead = orderbyScore(this->FSWLLManager->ShowListHead);
        break;
    case 3:
        qDebug("选择了送餐速度排序");
        this->FSWLLManager->ShowListHead = this->FSWLLManager->orderbySpeed(this->FSWLLManager->ShowListHead);
        break;
    default:
        break;
    }
}




void FoodShopWidegt::on_pushButton_Search_clicked()
{
    changeShowPage();
    this->FSWLLManager->ShowListHead = this->FSWLLManager->createLinkedList(this->FSWLLManager->queryDRInfo());

    // 搜索筛选
    if(!ui->Search->text().isEmpty()){
        this->SearchContent = ui->Search->text();
        char SearchContent[50];
        strcpy(SearchContent,this->SearchContent.toStdString().c_str());
        this->FSWLLManager->ShowListHead
                = searchGoodName(SearchContent, this->FSWLLManager->ShowListHead);
    }
    if(this->FSWLLManager->ShowListHead == NULL){
        return;
    }

    // 菜系筛选
    this->FSWLLManager->ShowListHead
            = dietSelect(this->FSWLLManager->ShowListHead,SelectMode_DRType);

    // 距离筛选
    double distance = 0.0;
    switch(SortMode_Distance){
    case 0:
        break;
    case 1:
        distance = 500.0;
        break;
    case 2:
        distance = 1000.0;
        break;
    case 3:
        distance = 3000.0;
        break;
    case 4:
        distance = 5000.0;
        break;
    case 5:
        distance = 10000.0;
        break;
    }
    if(SortMode_Distance != 0){
        this->FSWLLManager->ShowListHead = searchInDistance(distance,this->FSWLLManager->ShowListHead);
        this->FSWLLManager->ShowListHead = orderbyDistance(this->FSWLLManager->ShowListHead);
    }

    // 四种排序
    sortDefault();

    // 四种筛选
    switch (SelectMode_Addition) {
    case 0:
        break;
    case 1:
        this->FSWLLManager->ShowListHead = CompensateOnly(this->FSWLLManager->ShowListHead);
        break;
    case 2:
        this->FSWLLManager->ShowListHead = rebateOnly(this->FSWLLManager->ShowListHead);
        break;
    case 3:
        this->FSWLLManager->ShowListHead = ReadpacketOnly(this->FSWLLManager->ShowListHead);
        break;
    case 4:
       this->FSWLLManager->ShowListHead = FreeFareOnly(this->FSWLLManager->ShowListHead);
        break;
    }

    setupDRCard(this->FSWLLManager->ShowListHead);
    ui->DRCardWidget->show();
}

