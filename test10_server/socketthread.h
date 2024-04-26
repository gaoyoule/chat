#ifndef SOCKETTHREAD_H
#define SOCKETTHREAD_H
#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include "MsgBuilder.h"
#include "userdao.h"
#include <QMutex>//互斥锁
#include <queue>//队列
class SocketThread : public QThread
{
    Q_OBJECT
public:
    SocketThread(qintptr sd);

    //线程的执行逻辑
    void run();

    void dealUserRegister(QString json);//处理用户注册的函数

    void dealUserLogin(QString json); //处理用户登录的函数

    void addUserLonginSuc(UserData hostData, vector<UserData>& friends); // 构建登录成功的json串
    void dealUserLoginSuc(QString json);

    //构建用户上线的json
    void addUserOnline(UserData user);
    //处理用户上线的函数
    void dealUserOnline(QString json);

    //构建用户下线的json
    void addUserOffline(UserData user);
    //处理用户下线的函数
    void dealUserOffline(QString json);

    //处理发送信息的函数
    void dealUserSendMsg(QString json);

    //构建用户接收信息的json
    void addUserReceiveMsg(UserData from, UserData to, QString msg);
    //处理用户接收信息的函数
    void dealUserReceiveMsg(QString json);

    ~SocketThread();

private slots:
    void onReadyRead();//接收信息的槽函数

   void onDiscon();//断开连接的槽函数；

signals:
    //用户登录成功时， 发送的自定义信号;
    void sigUserLoginSuc(UserData user, SocketThread *t);

    //用户下线的时候发送自定义信号
    void sigUserOffline(UserData user);

    //用户接收消息发送的时候发送的自定义信号
    void sigUserSendMsg(UserData from, UserData to, QString msg);

private:
    qintptr sd;//sd 标志或者套接字描述

    //创建套接字指针
    QTcpSocket *socket;

    bool isRun ; // 标志 ：是否断开连接
    bool isRead ; //标志： 是否来信息

    //创建互斥锁
    QMutex mutex;
    //创建消息类型
    queue<QString> msgQueue;

    //保存自己的结构体
    UserData host;

};

#endif // SOCKETTHREAD_H
