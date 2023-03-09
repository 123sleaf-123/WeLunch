#ifndef ORDERSUBMITRECEIVE_H
#define ORDERSUBMITRECEIVE_H

#include <QDialog>

namespace Ui {
class OrderSubmitReceive;
}

class OrderSubmitReceive : public QDialog
{
    Q_OBJECT

public:
    explicit OrderSubmitReceive(QWidget *parent = nullptr);
    ~OrderSubmitReceive();

private:
    Ui::OrderSubmitReceive *ui;
};

#endif // ORDERSUBMITRECEIVE_H
