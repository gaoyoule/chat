#include "friendform.h"
#include "ui_friendform.h"

FriendForm::FriendForm(UserData user, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FriendForm),user(user)
{
    ui->setupUi(this);
    //显示图片
    QPixmap p(":/head22.jpg");
    p = p.scaled(ui->label_img->size());
    ui->label_img->setPixmap(p);

    //拼接字符串
    QString str = QString("%1(%2)").arg(user.nickname).arg(user.id);
    ui->label_name->setText(str);
}

QStringList FriendForm::getWaitMsg()
{
    QStringList tmp = waitMsgs;
    waitMsgs.clear();//清空
    return tmp;
}

void FriendForm::msgTip(bool flag)
{
    //消息提示 flag：true --》（新消息）tom（100002）  false -》tom（100002）
    if(flag)
    {
        //拼接字符串
        QString str = QString("(新消息)%1(%2)").arg(user.nickname).arg(user.id);
        ui->label_name->setText(str);
    }
    else
    {
        //拼接字符串
        QString str = QString("%1(%2)").arg(user.nickname).arg(user.id);
        ui->label_name->setText(str);
    }
}

FriendForm::~FriendForm()
{
    delete ui;
}
