#include "ordersubmitreceive.h"
#include "ui_ordersubmitreceive.h"

OrderSubmitReceive::OrderSubmitReceive(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OrderSubmitReceive)
{
    ui->setupUi(this);
}

OrderSubmitReceive::~OrderSubmitReceive()
{
    delete ui;
}
