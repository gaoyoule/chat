#include "registerdialog.h"
#include "ui_registerdialog.h"

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    //实例化套接字对象
    ui->lineEdit_nickname->setPlaceholderText("请输入昵称：");
    ui->lineEdit_pass->setPlaceholderText("请输入密码：");
    socket = MySocket::getIns();

    //接收信息套接字会发送信号readyRead();
    connect(socket, SIGNAL(readyRead()), this, SLOT(onRead()));
}

void RegisterDialog::closeEvent(QCloseEvent *)
{
    //断开连接
    disconnect(socket, SIGNAL(readyRead()), this, SLOT(onRead()));
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::on_pushButton_register_clicked()
{
    //获取文本内容
    QString nickname = ui->lineEdit_nickname->text();
    QString pass = ui->lineEdit_pass->text();

    //构建 json串
    QString jsonStr = MsgBuilder::buildRegisterUserMsg(pass, 0, nickname);
    //在控制台显示；
    qDebug() << jsonStr;

    //发送给服务器
    socket->write(jsonStr.toLocal8Bit());
}

void RegisterDialog::onRead()
{
    //获取接收的信息
    QByteArray data = socket->readAll();
    //QByteArray -> QString
    QString jsonStr = QString :: fromLocal8Bit(data);
    //解析json串
     int id = MsgBuilder::parseRegisterUserReturnMsg(jsonStr);

    //显示ui上
    ui->label_id->setNum(id);
}
