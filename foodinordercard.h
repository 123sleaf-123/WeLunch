#ifndef FOODINORDERCARD_H
#define FOODINORDERCARD_H

#include <QFrame>
#include <QString>

namespace Ui {
class foodinordercard;
}

class foodinordercard : public QFrame
{
    Q_OBJECT

public:
    explicit foodinordercard(QWidget *parent = nullptr);
    ~foodinordercard();

    float setText(QString id_user, QString id_order, QString id_DR, QString);

    QString id_user;
    QString id_DR;
    QString id_order;
    QString id_food;
private slots:
    void on_pushButton_clicked();

private:
    Ui::foodinordercard *ui;
};

#endif // FOODINORDERCARD_H
