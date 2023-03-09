#include "foodinordercardimagebutton.h"
#include <QSqlQuery>
#include <QMessageBox>

FoodInOrderCardImageButton::
FoodInOrderCardImageButton(QWidget *parent):
QPushButton(parent)
{
}

void FoodInOrderCardImageButton::paintPicture(QString ImagePath){
    QPixmap pix;
    bool ret = pix.load(ImagePath);
    if(!ret){
        qDebug("图片加载失败");
//        QMessageBox::warning(this,"图片加载失败","找不到正确路径");
        this->setText("没有找到图片");
    }

    // 设置按钮固定大小
    this->setFixedSize(this->size());

    // 设置按钮为不规则样式
    this->setStyleSheet("QPushButton{border:0px;}");

    // 设置图标
    this->setIcon(pix);

    // 设置图标大小
    this->setIconSize(this->size());
}
