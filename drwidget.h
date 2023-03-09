#ifndef DRWIDGET_H
#define DRWIDGET_H

#include <QWidget>
#include <QSqlQuery>

namespace Ui {
class DRWidget;
}

class DRWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DRWidget(QWidget *parent = nullptr,QString id_user = nullptr);
    ~DRWidget();

    void setupFoodCard(QSqlQuery *);
    QSqlQuery *queryFood();
    void setDRid(QString id_DR);

    QString id_DR;
    QString id_user;

    int status;

signals:
    void initEnd();

public slots:
    void setupDRWideget();

private slots:
    void on_info_clicked();

    void on_pushButton_add_clicked();

    void on_pushButton_clicked();

private:
    Ui::DRWidget *ui;
};

#endif // DRWIDGET_H
