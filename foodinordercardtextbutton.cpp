#include "foodinordercardtextbutton.h"

FoodInOrderCardTextButton::
FoodInOrderCardTextButton(QWidget *parent)
    :QPushButton(parent)
{
    // 设置按钮为不规则样式
    this->setStyleSheet("QPushButton{border:0px;}");
}
