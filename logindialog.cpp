#include "logindialog.h"
#include "ui_logindialog.h"
#include <QPainter>
#include <QSqlQuery>
#include <QMessageBox>
#include "signupdialog.h"
#include "findpwddialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("登陆");
    ui->captcha->hide();
    ui->captchasymbol->hide();
    ui->lineEdit_captcha->hide();
    ui->pushButto_change->hide();
    FailTime = 0;
}

void LoginDialog::ShowPicture(){
    QPixmap pix;
    QPainter * painter;
    pix.load(":/image/Ireina.png");
    painter->drawPixmap(0,0,pix.width()*0.1,pix.height()*0.1,pix);
}

void LoginDialog::LoginCheck(){
    id_user = this->ui->id_user->text();
    pwd_user = this->ui->pwd_user->text();
    if(id_user.isEmpty()){
        QMessageBox::critical(NULL,"登陆失败","账号不能为空");
    }
    else if(pwd_user.isEmpty()){
        QMessageBox::critical(NULL,"登陆失败","密码不能为空");
    }
    else{
        UserList head = createLinkedList(queryPwd());
        int check = checkId(ui->id_user->text(),ui->pwd_user->text(),head);
        if(FailTime < 2){
            ui->captcha->hide();
            ui->captchasymbol->hide();
            ui->lineEdit_captcha->hide();
            ui->pushButto_change->hide();
        }
        else {
            ui->captcha->show();
            ui->captchasymbol->show();
            ui->lineEdit_captcha->show();
            ui->pushButto_change->show();
            if(FailTime == 2){
                captchaCreate();
                FailTime++;
            }
            else if(ui->lineEdit_captcha->text() != ui->captcha->text()){
                QMessageBox::critical(NULL,"登陆失败","验证码错误");
                captchaCreate();
                return;
            }
        }
        if(check == 2){
            FailTime = 0;
            QMessageBox::information(NULL,"登陆成功",QString("欢迎回来，用户%1").arg(UserName));
            emit accept();
        }
        if(check == 1){
            if(FailTime < 3)
            {
                FailTime ++;
                QMessageBox::critical(NULL,"登陆失败",
                                      QString("密码错误%1次，请重新输入").arg(FailTime));
            }
            else{
                QMessageBox::critical(NULL,"登陆失败",
                                      QString("密码错误"));
                captchaCreate();
            }
        }
        if(check == 0){
            QMessageBox::critical(NULL,"登陆失败","账号不存在，请重新输入");
        }
    }
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_buttonBox_accepted()
{
    LoginCheck();
}

QSqlQuery * LoginDialog::queryPwd(){
    QSqlQuery *q = new QSqlQuery;
    q->prepare("select id_user,password,username from user");
    q->exec();
    return q;
}

UserList LoginDialog::createLinkedList(QSqlQuery *q){
    UserList head;
    UserList cur;
    UserList pre;
    int i = 0;
    for(; q->next(); i++){
        UserList PtrL = (UserList)malloc(sizeof(struct UserNode));
        qDebug("111");
        QString id_user = q->value(0).toString();
        QString password = q->value(1).toString();
        QString UserName = q->value(2).toString();
        strcpy(PtrL->id_user, id_user.toStdString().c_str());
        strcpy(PtrL->Password, password.toStdString().c_str());
        strcpy(PtrL->UserName,UserName.toStdString().c_str());
        PtrL->next = NULL;
        if(i == 0){
            head = cur = pre = PtrL;
        }
        else{
            cur = PtrL;
            pre->next = cur;
            pre = cur;
        }
    }
    return head;
}

int LoginDialog::checkId(QString temid, QString tempassword, struct UserNode* head)
{
    struct UserNode* pmove;
    int answer = 0;
    pmove = head;
    while (pmove != NULL)
    {
        if (temid == pmove->id_user)
        {
            answer = 1;
            if (tempassword == pmove->Password)
            {
                answer = 2;
                id_user = pmove->id_user;
                UserName = pmove->UserName;
                break;
            }
        }
        pmove = pmove->next;
    };
    return answer;
}

void LoginDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    // 反走样
    painter.setRenderHint(QPainter::Antialiasing, true);

    // 设置渐变色,设置起点、终点
    QLinearGradient linear(0, 0, 395, 251);
    linear.setColorAt(0, QColor("#DAD299"));
    linear.setColorAt(1, QColor("#B0DAB9"));

    // 设置显示模式
    linear.setSpread(QGradient::PadSpread);

    // 设置画笔颜色、宽度
    painter.setPen(QPen(QColor(255, 255, 255, 0), 1));

    // 设置画刷填充
    painter.setBrush(QBrush(linear));

    // 绘制矩形
    painter.drawRect(QRect(0, 0, 395, 251));

}

void LoginDialog::on_regist_clicked()
{
    SignUpDialog *sud = new SignUpDialog(this);
    sud->show();
    connect(sud,&QDialog::accepted,sud,&QWidget::close);
}


void LoginDialog::on_finpwd_clicked()
{
    FindPwdDialog *fpd = new FindPwdDialog(this);
    fpd->show();
    connect(fpd,&QDialog::accepted,fpd,&QWidget::close);
}

void LoginDialog::captchaCreate(){
    captcha.clear();
    int length = 0;
    while(length < 4){
        int pos = rand() * rand() % 89;
        char ch = seed[pos];
        captcha.append(ch);
        length++;
    }
    ui->captcha->setText(captcha);
}

void LoginDialog::on_pushButto_change_clicked()
{
    captchaCreate();
}

