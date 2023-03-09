#ifndef PAYWIDGET_H
#define PAYWIDGET_H

#include <QWidget>
#include <QTime>

namespace Ui {
class PayWidget;
}

class PayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PayWidget(QWidget *parent = nullptr, QString id_user = nullptr ,QString id_order = nullptr,QString id_DR = nullptr);
    ~PayWidget();
    void setupWidget();

    QString id_user;
    QString id_order;
    QString id_DR;
    QString password;
    float money;
    float sum;
    float Fare;
    bool less[3];
    QTime *cur;
    QTime *open,*close;

private slots:
    void on_pay_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::PayWidget *ui;
};

#endif // PAYWIDGET_H
