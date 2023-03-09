#ifndef FOODINORDERCARDIMAGEBUTTON_H
#define FOODINORDERCARDIMAGEBUTTON_H

#include <QPushButton>

class FoodInOrderCardImageButton : public QPushButton
{
public:
    FoodInOrderCardImageButton(QWidget *parent);
    void paintPicture(QString ImagePath);
};

#endif // FOODINORDERCARDIMAGEBUTTON_H
