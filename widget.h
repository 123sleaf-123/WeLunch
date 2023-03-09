#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSqlTableModel>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void setUser(QString id_user, int status);
    void setupTable();

    QString id_user;
    int status;
    QString id_DR;

signals:
    void initEnd();

private slots:
    void on_BtnAdd_clicked();

    void on_BtnSure_clicked();

    void on_BtnCancel_clicked();

    void on_BtnDel_clicked();

    void on_BtnFind_clicked();

    void on_FindSort_activated(const QString &arg1);

private:
    Ui::Widget *ui;
    QSqlTableModel *mod;
};
#endif // WIDGET_H
