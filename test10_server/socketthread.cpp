#include "socketthread.h"

SocketThread::SocketThread(qintptr sd):sd(sd)
{
    isRun = true;
    isRead = false;
}

void SocketThread::run()
{
    socket = new QTcpSocket;
    socket->setSocketDescriptor(sd);

    //接收客户端消息的时候， 套接字发送readyread()信号；
    connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));

    //客户端断开连接的时候，套接字发送信号
    connect(socket, SIGNAL(disconnected()), this, SLOT(onDiscon()));

    //事件循环处理的信息
    while(isRun == true)//是否是连接状态
      {
        if(isRead)
        {
            //获取接收信息
            QByteArray data = socket->readAll();

            //QByteArray -> QString
            QString jsonStr = QString::fromLocal8Bit(data);

            //加锁
            mutex.lock();
            //存放到消息队列
            msgQueue.push(jsonStr);
            //解锁
            mutex.unlock();
            isRead = false;
          }
            //遍历消息队列
            while(!msgQueue.empty())
            {

                QString jsonStr = msgQueue.front();//获取队首元素

                qDebug() << jsonStr;

                //加锁
                mutex.lock();
                //存放到消息队列
                msgQueue.pop();
                //解锁
                mutex.unlock();
                //获取消息类型
               int type = MsgBuilder::msgType(jsonStr);
                //判断消息类型
               switch(type)
               {
               case MsgBuilder::registerUser://注册用户 type :0
                   dealUserRegister(jsonStr);//处理用户注册的函数
                   break;
               case MsgBuilder::login:  //用户登录 type ： 2
                   dealUserLogin(jsonStr); //处理用户登录的函数
                   break;
               case MsgBuilder::loginSucReturn://登录成功 type ：3
                   dealUserLoginSuc(jsonStr);//处理用户登录的函数
                   break;
               case MsgBuilder::sendMsg://发送消息类型 type:5
                   dealUserSendMsg(jsonStr);//处理发送消息的函数
                   break;
               case MsgBuilder::receiveMsg://接收消息类型 type:6
                   dealUserReceiveMsg(jsonStr);//处理发送消息的函数
                   break;
               case MsgBuilder::userOnline://用户上线 type:7
                   dealUserOnline(jsonStr);//用户处理上线得函数
                   break;
               case MsgBuilder::userOffline://用户下线 type:8
                   dealUserOffline(jsonStr);//用户处理下线得函数
                   break;
               default:
                   break;
               }
            }
        socket->waitForDisconnected(20);
    }

    //发送自定义信号
    emit sigUserOffline(host);
    //关闭套接字
    socket->close();

    delete socket;
}

void SocketThread::dealUserRegister(QString json)
{
    //解析json函数
    UserData user = MsgBuilder::parseRegisterUserMsg(json);
    //同步数据
    UserEntity e;

    e.passwd = user.password;
    e.nickName = user.nickname;
    e.headId = user.headId;

    //通过数据库插入注册数据
    UserDao::getIns()->insertTable(e);

    //构建json串
    QString jsonStr = MsgBuilder::buildRegisterUserReturnMsg(e.userId);
    qDebug() << jsonStr;

    //把账号发送给客户端
    socket->write(jsonStr.toLocal8Bit());
}


void SocketThread::dealUserLogin(QString json)
{
    //解析json串
    UserData user = MsgBuilder::parseLoginMsg(json);

    //同步数据
    UserEntity e;
    e.userId = user.id;
    e.passwd = user.password;

    //定于变量
    bool ok = false;
    //通过数据库查询；
    UserDao::getIns()->selectTable(ok, e);
    //判断登录结果
    if(ok)
    {
        //数据同步
        user.headId = e.headId;
        user.nickname = e.nickName;

        host = user;

        //发送自定义信号给主线程
        emit sigUserLoginSuc(user, this);


        /*
        //构建成功的json
        vector<UserData> friends;//当修改多线程的时候在获取好友信息

        QString jsonStr = MsgBuilder::buildLoginSucReturnMsg(user,friends); //登录成功
        //发送给客户端
        socket->write(jsonStr.toLocal8Bit());
        */
    }
    else
    {
        //登录失败
        QString jsonStr = MsgBuilder::buildLoginLoseReturnMsg();
        //发送给客户端
        socket->write(jsonStr.toLocal8Bit());
    }

}

void SocketThread::dealUserSendMsg(QString json)
{
    //提供保存数据的结构体
    UserData from, to;

    //解析json
   QString msg = MsgBuilder::parseSendMsg(json, from, to);

    //发送自定义信号给主线程
    emit sigUserSendMsg(from, to, msg);
}

void SocketThread::addUserReceiveMsg(UserData from, UserData to, QString msg)
{
    //构建json串
    QString json = MsgBuilder::buildReceiveMsg(from, to, msg);
    //加锁
    mutex.lock();
    //入队
    msgQueue.push(json);
    //解锁
    mutex.unlock();
}

void SocketThread::dealUserReceiveMsg(QString json)
{
    //发送给客户端
    socket->write(json.toLocal8Bit());
}

void SocketThread::addUserLonginSuc(UserData hostData, vector<UserData> &friends)
{
    //构建json串
    QString json = MsgBuilder::buildLoginSucReturnMsg(hostData, friends);
    //加锁
    mutex.lock();
    //入队
    msgQueue.push(json);
    //解锁
    mutex.unlock();
}

void SocketThread::dealUserLoginSuc(QString json)
{
    //发送给客户端
    socket->write(json.toLocal8Bit());
}

void SocketThread::addUserOnline(UserData user)
{
    //构建json串
    QString json = MsgBuilder::buildUserOnline(user);
    //加锁
    mutex.lock();
    //入队
    msgQueue.push(json);
    //解锁
    mutex.unlock();
}

void SocketThread::dealUserOnline(QString json)
{
    //发送给客户端
    socket->write(json.toLocal8Bit());
}

void SocketThread::addUserOffline(UserData user)
{
    //构建json串
    QString json = MsgBuilder::buildUserOffline(user);
    //加锁
    mutex.lock();
    //入队
    msgQueue.push(json);
    //解锁
    mutex.unlock();
}

void SocketThread::dealUserOffline(QString json)
{
    //发送给客户端
    socket->write(json.toLocal8Bit());
}


SocketThread::~SocketThread()
{
    qDebug() << "delete";
}
void SocketThread::onReadyRead()
{
    qDebug() << "来消息了";
    isRead = true;
    /*
    //获取接收信息
    QByteArray data = socket->readAll();

    //QByteArray -> QString
    QString jsonStr = QString::fromLocal8Bit(data);
    qDebug() << jsonStr;
    //获取消息类型
    int type = MsgBuilder::msgType(jsonStr);
    //判断消息类型
    switch(type)
    {
           case MsgBuilder::registerUser://注册用户 type :0
        dealUserRegister(jsonStr);//处理用户注册的函数
        break;
    case MsgBuilder::login:
        dealUserLogin(jsonStr);
        break;
    default:
        break;
    }
    */
}

void SocketThread::onDiscon()
{
  qDebug() << "断开连接";
  isRun = false;
}

