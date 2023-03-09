#include "signupdialog.h"
#include "ui_signupdialog.h"


SignUpDialog::SignUpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUpDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("注册");

}

SignUpDialog::~SignUpDialog()
{
    delete ui;
}

int checkPassword(char *str ){
    if(strlen(str)>16||strlen(str)<5)
        return 0;
    int b=0;
    int a=0;
    while (*str!=NULL)
    {
        if ((*str<='z'&&*str>='a')||(*str>='A'&&*str<='Z')){
            str++;
            a++;
        }else if ((*str>='0'&&*str<='9')){
            str++;
            b++;
        }else
            str++;
    }
    if (a>0&&b>0)
    {
        return 1;
    }else
        return 0;
}

int checkphonenum(char*str)
{
    int i;
    for (i = 0; i <strlen(str); i++)
    {
        if (*(str+i)<'0'||*(str+i)>'9')
        {
            return 0;
        }

    }

    if (strlen(str)!=11 && strlen(str)!=13)
    {
        return 0;

    }else if(strlen(str)==13&&strstr(str,"86")!=NULL){
        if(*(str+2)=='1'){
            return 1;
        }
    }else if (strlen(str)==11)
    {
        if(*str=='1'){
            return 1;
        }
    }
    return 0;
}

int checkName(char *name){
    if(strlen(name)<=20){
        return 1;
    }
    else{
        return 0;
    }
}

int checkRealName(char *rname){

    if(strlen(rname)<=12){
        return 1;
    }
    else{
        return 0;
    }
//检查名字，如果名字超过六个字则返回0
}

//下面是检查邮箱合法
char *islegal(char *str) {
    while((*str>='a'&&*str<='z')||
        (*str>='A'&&*str<='Z')||
        (*str>='0'&&*str<='9')||
         *str=='_')
    {
        str++;
    }
    return str;
}//找到下一个@or不合法位置
char *symbol(char* str){
    char*p;
    p=strchr(str,'@');
    if(p!=NULL&& p-str<strlen(str)){
        *p=0;
        p++;
        return p;
    }else
    return NULL;
    }
    //用上面函数将@变成\0后，循环检查后面的内容直到结尾
int alllegal(char *str){
    char *p;
    while (p!=NULL){
        p=islegal(str);
        if(p==str){
            return 0;//连续两个不标准符号
        }
        else if (*p=='\0')
        {
            return 1;
        }else if (*p!='.')//对于后面的来说.后面就会变成\0了，如果合法，就是跳着找不合法
        {
            return 0;
        }
        p++;
        str=p;
    }
    return 0;
}

int checkEmail(char *str){
    char*yumin=symbol(str);
    if (yumin==NULL)
    {
        return 0;
    }
    else if(alllegal(yumin)&&alllegal(str)&&strlen(str)<256){//分成两部分
        return 1;
    }else
        return 0;
}

void SignUpDialog::paintEvent(QPaintEvent *)
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
    painter.drawRect(QRect(0, 0, 395, 600));

}

void SignUpDialog::check(){
    bool regStatus;
    QList<QCheckBox *> checkboxs = this->findChildren<QCheckBox *>(QString(""),Qt::FindDirectChildrenOnly);
    for(int i = 0 ; i < checkboxs.count() ; i++){
        QCheckBox *cb = checkboxs.at(i);
        if(cb->checkState() == false){
            return;
        }
    }
    ui->pushButton->setEnabled(true);
}

void SignUpDialog::on_lineEdit_AccountName_editingFinished()
{
    str1 = ui->lineEdit_AccountName->text();
    strcpy(username,str1.toStdString().c_str());
    nameCheck = checkName(username);
    if(nameCheck && !ui->lineEdit_AccountName->text().isEmpty()){
        ui->checkBox_name->setChecked(true);
    }
    else {
        ui->checkBox_name->setChecked(0);
    }
    check();
}


void SignUpDialog::on_lineEdit_Password_editingFinished()
{
    str2 = ui->lineEdit_Password->text();
    strcpy(password,str2.toStdString().c_str());
    pwdCheck = checkPassword(password);
    if(pwdCheck && !ui->lineEdit_Password->text().isEmpty()){
        ui->checkBox_pwd->setChecked(true);
        ui->lineEdit_CheckPwd->setEnabled(true);
    }
    else {
        ui->checkBox_pwd->setChecked(0);
        ui->checkBox_pwdSure->setEnabled(0);
    }
    check();
}


void SignUpDialog::on_lineEdit_CheckPwd_editingFinished()
{
    str6 = ui->lineEdit_CheckPwd->text();
    strcpy(chpassword,str6.toStdString().c_str());
    if(ui->lineEdit_Password->text() == ui->lineEdit_CheckPwd->text()){
        pwdSureCheck = true;
    }
    else{
        pwdSureCheck = false;
    }
    if(pwdSureCheck == true && !ui->lineEdit_CheckPwd->text().isEmpty()){
        ui->checkBox_pwdSure->setChecked(true);
    }
    else {
        ui->checkBox_pwdSure->setChecked(0);
    }
    check();
}


void SignUpDialog::on_lineEdit_Mail_editingFinished()
{
    str5 = ui->lineEdit_Mail->text();
    strcpy(email,str5.toStdString().c_str());
    mailCheck = checkEmail(email);
    if(mailCheck && !ui->lineEdit_Mail->text().isEmpty()){
        ui->checkBox_mail->setChecked(true);
    }
    else{
        ui->checkBox_mail->setChecked(0);
    }
    check();
}


void SignUpDialog::on_lineEdit_RealName_editingFinished()
{
    str4 = ui->lineEdit_RealName->text();
    strcpy(name,str4.toStdString().c_str());
    rNameCheck = checkRealName(name);
    if(rNameCheck && !ui->lineEdit_RealName->text().isEmpty()){
        ui->checkBox_rName->setChecked(true);
    }
    else{
        ui->checkBox_rName->setChecked(true);
    }
    check();
}


void SignUpDialog::on_lineEdit_PhoneNumber_editingFinished()
{
    str3 = ui->lineEdit_PhoneNumber->text();
    strcpy(phonenum,str3.toStdString().c_str());
    pwdSureCheck = checkphonenum(phonenum);
    if(pwdSureCheck){
        ui->checkBox_phoneNum->setChecked(true);
        ui->lineEdit_CheckCode->setEnabled(true);
        ui->pushButton_SendCode->setEnabled(true);
    }
    else{
        ui->checkBox_phoneNum->setChecked(0);
        ui->lineEdit_CheckCode->setEnabled(0);
        ui->pushButton_SendCode->setEnabled(0);
    }
    check();
}


void SignUpDialog::on_comboBox_user_currentIndexChanged(int index)
{
}


void SignUpDialog::on_pushButton_2_clicked()
{
    this->close();
    delete this;
}


void SignUpDialog::on_pushButton_clicked()
{
    if(ui->comboBox_user->currentIndex() == 0){
        id_user = QString("user").append(phonenum);
        userType = 2;
    }
    else{
        id_user = QString("DR").append(phonenum);
        userType = 1;
    }
    q.prepare("insert into user (Id_user, userType, username, realname, password, teleNum, mailbox) values(:a,:b,:c,:d,:e,:f,:g)");
    q.bindValue(":a",id_user);
    q.bindValue(":b",QString("%1").arg(userType).toInt());
    q.bindValue(":c",username);
    q.bindValue(":d",name);
    q.bindValue(":e",password);
    q.bindValue(":f",phonenum);
    q.bindValue(":g",ui->Mail->text());
    q.exec();
    QMessageBox::information(this,"恭喜","注册成功");
    this->close();
    delete this;
}


