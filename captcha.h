#ifndef CAPTCHA_H
#define CAPTCHA_H

#include <QLabel>

class CAPTCHA : public QLabel
{
public:
    CAPTCHA(QWidget *parent = nullptr);
    ~CAPTCHA();
    Q_OBJECT
    //返回一个字符串（字母一律都按照大写返回）
    QString getCaptcha() const;

public slots:
    //刷新验证码，在用户不确定的时候进行相应刷新
    void slt_reflushVerification();

protected:
    //重写绘制事件,以此来生成验证码
    void paintEvent(QPaintEvent *event);

private:
    const int letter_number = 4;//产生字符的数量
    int noice_point_number;//噪点的数量
    enum {
        NUMBER_FLAG,
        UPLETTER_FLAG,
        LOWLETTER_FLAG
    };
    //这是一个用来生成验证码的函数
    void produceCaptcha() const;
    //产生一个随机的字符
    QChar produceRandomLetter() const;
    //产生随机的颜色
    void produceRandomColor() const;

    QChar *Captcha;
    QColor *colorArray;
};

#endif // CAPTCHA_H
