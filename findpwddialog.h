#ifndef FINDPWDDIALOG_H
#define FINDPWDDIALOG_H

#include <QDialog>

namespace Ui {
class FindPwdDialog;
}

class FindPwdDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindPwdDialog(QWidget *parent = nullptr);
    ~FindPwdDialog();

private:
    Ui::FindPwdDialog *ui;
};

#endif // FINDPWDDIALOG_H
