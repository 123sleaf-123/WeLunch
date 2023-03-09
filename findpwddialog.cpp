#include "findpwddialog.h"
#include "ui_findpwddialog.h"

FindPwdDialog::FindPwdDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindPwdDialog)
{
    ui->setupUi(this);
}

FindPwdDialog::~FindPwdDialog()
{
    delete ui;
}
