#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "registerdialog.h"
#include <QHostAddress>
#include <QMessageBox> //消息提示框的头文件
#include "friendsdialog.h"
#include <QCloseEvent>

//#include "mysocket.h"
//#include <QDebug>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);

    void closeEvent(QCloseEvent *);//重写关闭事件

    void dealUserLoginSuc(QString json);//处理用户登录成功;

    ~LoginDialog();

private slots:
    void on_pushButton_register_clicked();

    void on_pushButton_connect_clicked();

    //连接成功的反馈
    void onConnect();

    void on_pushButton_login_clicked();

    void onLoginRead();//接收信息的槽函数；

private:
    Ui::LoginDialog *ui;

    //定义套接字指针
    MySocket *socket;
};

#endif // LOGINDIALOG_H
