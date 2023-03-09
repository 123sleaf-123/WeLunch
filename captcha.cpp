#include "captcha.h"
#include <QPaintEvent>
#include <QPainter>
#include <QTime>

CAPTCHA::CAPTCHA(QWidget *parent)
    : QLabel(parent)
{
    //生成随机种子

}

//重写绘制事件,以此来生成验证码
void CAPTCHA::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPoint p;
    //背景设为白色
    painter.fillRect(this->rect(), Qt::white);
    //产生4个不同的字符
    produceCaptcha();
    //产生4个不同的颜色
    produceRandomColor();
    //绘制验证码
    for (int i  =  0; i < letter_number; ++i)
    {
        p.setX(i*(this->width() / letter_number)+this->width()/8);
        p.setY(this->height() / 2);
        painter.setPen(colorArray[i]);
        painter.drawText(p, QString(Captcha[i]));
    }
    //绘制噪点
    for (int j  =  0; j < noice_point_number; ++j)
    {
        p.setX(rand() % this->width());
        p.setY(rand() % this->height());
        painter.setPen(colorArray[j % 4]);
        painter.drawPoint(p);
    }
    return;
}

//这是一个用来生成验证码的函数
void CAPTCHA::produceCaptcha() const
{
    for (int i  =  0; i < letter_number; ++i)
        Captcha[i]  =  produceRandomLetter();
    return;
}

//产生一个随机的字符
QChar CAPTCHA::produceRandomLetter() const
{
    srand( (unsigned)time( NULL ) );
    int num = rand();
}

//产生随机的颜色
void CAPTCHA::produceRandomColor() const
{
    for (int i  =  0; i < letter_number; ++i)
        colorArray[i] = QColor(rand() % 255, rand() % 255, rand() % 255);
    return;
}

//返回一个字符串（字母一律都按照大写返回）
QString CAPTCHA::getCaptcha() const
{
    QString s;
    QChar cTemp;
    for (int i  =  0; i < letter_number; ++i)
    {
        cTemp  =  Captcha[i];
//        s += (cTemp > 97) ?cTemp.toUpper():cTemp;
    }
    return s;
}

//刷新验证码，在用户不确定的时候进行相应刷新
void CAPTCHA::slt_reflushVerification()
{
    repaint();
}

CAPTCHA::~CAPTCHA()
{

}
