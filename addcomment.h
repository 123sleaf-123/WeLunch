#ifndef ADDCOMMENT_H
#define ADDCOMMENT_H

#include <QWidget>

namespace Ui {
class AddComment;
}

class AddComment : public QWidget
{
    Q_OBJECT

public:
    explicit AddComment(QWidget *parent = nullptr,QString id_user = nullptr,QString id_order = nullptr);
    ~AddComment();
    QString CommetnContent;
    QString id_user;
    QString id_order;
    QString id_DR;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_recomm_clicked();

private:
    Ui::AddComment *ui;
};

#endif // ADDCOMMENT_H
