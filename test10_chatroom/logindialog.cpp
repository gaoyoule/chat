#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    //实例化对象
    socket = MySocket::getIns();

    //连接函数， 连接成功套接字发送信号
    connect(socket, SIGNAL(connected()), this, SLOT(onConnect()));

    //接收信息的时候套接字发送readyRead()信号；
    connect(socket, SIGNAL(readyRead()), this, SLOT(onLoginRead()));
}

void LoginDialog::closeEvent(QCloseEvent *)
{
    //断开连接
    disconnect(socket, SIGNAL(readyRead()), this, SLOT(onLoginRead()));
}

void LoginDialog::dealUserLoginSuc(QString json)
{
    //定义结构体类型 -》保存自己的信息
    UserData hostData;

    //解析json串
   vector<UserData> friends =  MsgBuilder::parseLoginSucReturnMsg(hostData, json);

   //关闭页面
   this->close();

   //页面跳转
    friendsDialog *f = new friendsDialog(hostData, friends);
    f->show();

}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushButton_register_clicked()
{
    //页面切换
    RegisterDialog *r = new RegisterDialog(this);

    //断开连接， 断开readyRead()信号， 断开inLoginRead槽函数
    disconnect(socket, SIGNAL(readyRead()), this, SLOT(onLoginRead()));

    //阻塞效果显示页面；
    r->exec();

    //接收信号的时候套接字发送readyRead信号
    connect(socket, SIGNAL(readyRead()), this, SLOT(onLoginRead()));

}

void LoginDialog::on_pushButton_connect_clicked()
{
    //获取文本内容
    QString ip = ui->lineEdit_ip->text();
    //连接服务器
    socket->connectToHost(QHostAddress(ip),11111);
}

void LoginDialog::onConnect()
{
    qDebug() << "连接成功";

    //把失活的控件变成活性
    ui->lineEdit_id->setEnabled(true);
    ui->lineEdit_pass->setEnabled(true);
    ui->pushButton_login->setEnabled(true);
    ui->pushButton_register->setEnabled(true);
}

void LoginDialog::on_pushButton_login_clicked()
{
    //获取文本内容
    QString id = ui->lineEdit_id->text();
    QString pass = ui->lineEdit_pass->text();

    //构建json串
    QString jsonStr = MsgBuilder::buildLoginMsg(id.toInt(), pass);
    qDebug() << jsonStr;

    //发送给服务器
    socket->write(jsonStr.toLocal8Bit());


}

void LoginDialog::onLoginRead()
{
    //获取接收信息
    QByteArray data = socket->readAll();
    // QByteArray -> QString
    QString jsonStr = QString::fromLocal8Bit(data);

    qDebug() << jsonStr;
   //获取消息类型
    int type = MsgBuilder::msgType(jsonStr);
    //判断消息类型哪一个
    switch (type) {
    case MsgBuilder::loginSucReturn: //登录成功 type : 3
        dealUserLoginSuc(jsonStr);// 处理用户登录成功
        break;
    case MsgBuilder::loginLoseReturn: //登录失败 type : 4
        //消息提示框， 提示登陆失败
        QMessageBox::information(this, "通知", "登录失败" );
        break;
    default:
        break;
    }
}
