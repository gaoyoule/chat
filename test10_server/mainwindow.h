#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QTcpServer>
#include "myserver.h"
//#include <QTcpSocket>
#include "socketthread.h"

#include <QDebug>
#include <QHostAddress> //主机信息
#include <QHostInfo> //主机地址

//#include "MsgBuilder.h"
//#include "userdao.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void initIp();//初始化ip
//    void dealUserRegister(QString json);//处理用户注册的函数

//    void dealUserLogin(QString json); //处理用户登录的函数
    ~MainWindow();

private slots:
    /*void newConnect(); *///客户端连接的槽函数；

    void onsigSendsd(qintptr sd);//接收sd标志的自定义信号的槽函数；

//    void onReadyRead();//接收信息的槽函数

    //接收登录成功自定义信号的槽函数；
    void onUserLoginSuc(UserData user, SocketThread *t);

    //接收用户下线的自定义槽函数
    void onUserOffline(UserData user);

    //接收用户发送消息的自定义信号的槽函数
    void onUserSendMsg(UserData from, UserData to, QString msg);



private:
    Ui::MainWindow *ui;
    //套接字指针
//   QTcpSocket *socket;
 //   Myserver *socket;
    //服务器指针
//    QTcpServer *server;
    Myserver *server;

    //定义统计在线人员的容器
    map<UserData, SocketThread*> users;
};


#endif // MAINWINDOW_H
