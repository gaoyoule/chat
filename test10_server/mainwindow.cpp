#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //注册自定义类型
    qRegisterMetaType<UserData>("UserData");
    //初始化
    initIp();
//    server = new QTcpServer(this);
    server = new Myserver(this);

    //监听, QHostAddress::Any 任意ip；
    server->listen(QHostAddress::Any, 11111);

    //连接函数 当有新的客户端连接时， server对象会发出newConnection信号
//    connect(server, SIGNAL(newConnection()), this, SLOT(newConnect()));

    //当有新客户端连接时，server对象会发出自定义信号
    connect(server, SIGNAL(sig_sendsd(qintptr)),this, SLOT(onsigSendsd(qintptr)));

}

void MainWindow::initIp()
{
    //获取主机名称
    QString hostName = QHostInfo::localHostName();

    //获取主机信息
    QHostInfo info = QHostInfo::fromName(hostName);

    //获取主机地址(一般不只有一个）
    QList<QHostAddress> list = info.addresses();

    //定义遍历，用与拼接
    QString ip;

    //遍历容器
    for(int i = 0; i < list.size(); i++)
    {
        //协议类型（ipv4)
        //list[i].protocol()获取协议类型
        if(list[i].protocol() == QAbstractSocket::IPv4Protocol)
        {
            ip += "*";
            ip += list[i].toString();
        }
    }
    //显示在ui端
    ui->label_ip->setText(ip);
}
/*
void MainWindow::dealUserRegister(QString json)
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

void MainWindow::dealUserLogin(QString json)
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
        //构建成功的json
        vector<UserData> friends;//当修改多线程的时候在获取好友信息

        QString jsonStr = MsgBuilder::buildLoginSucReturnMsg(user,friends); //登录成功
        //发送给客户端
        socket->write(jsonStr.toLocal8Bit());
    }
    else
    {
        //登录失败
        QString jsonStr = MsgBuilder::buildLoginLoseReturnMsg();
        //发送给客户端
        socket->write(jsonStr.toLocal8Bit());
    }

}
*/
MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::newConnect()
//{
//    qDebug() << "客户端连接我了";

//    //获取与客户端通信的套接字对象
//    socket = server->nextPendingConnection();

//    //接收客户端消息的时候， 套接字发送readyread()信号；
//    connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
//}

void MainWindow::onsigSendsd (qintptr sd)
{
    //创建子线程
    SocketThread *st = new SocketThread(sd);
    //开启线程
    st->start();

    //线程执行完毕后会发送信号， 调用自带的槽函数， 自带的槽函数调用析构
    connect(st, SIGNAL(finished()), st, SLOT(deleteLater()));

    //用户登录成功的时候子线程发送信号
    connect(st, SIGNAL(sigUserLoginSuc(UserData,SocketThread*)),
            this, SLOT(onUserLoginSuc(UserData,SocketThread*)));
    //用户下线的时候子线程发送自定义信号
    
    
    connect(st, SIGNAL(sigUserOffline(UserData)), this, SLOT(onUserOffline(UserData)));

    //用户发送信息的时候子线程发送的信号
    connect(st, SIGNAL(sigUserSendMsg(UserData,UserData,QString)),
            this, SLOT(onUserSendMsg(UserData,UserData,QString)));

}

void MainWindow::onUserLoginSuc(UserData user, SocketThread *t)
{
  //1.判断重复登录
    if(users.count(user))
    {
        return;
    }
    //2.获得所有的在线用户， 放在vector中
    vector<UserData> v;

    for(map<UserData, SocketThread*>::iterator iter = users.begin();
        iter != users.end(); iter++)
    {
        v.push_back(iter->first);//添加好友放入容器；

        //通知在线好友, 新客户端登录了
       iter->second->addUserOnline(user);

    }
    //3.将vector传给子线程， 子线程发送json串
    t->addUserLonginSuc(user, v);

    //4.将登录用户添加到在线用户中
    users[user] = t;// 如果key值重复， value值覆盖

}

void MainWindow::onUserOffline(UserData user)
{
    //1.判断重复登录
      if(users.count(user))
      {
          users.erase(user);//删除数据
      }
    //2.通知其他在线人员
      for(map<UserData, SocketThread*>::iterator iter = users.begin();
          iter != users.end(); iter++)
      {
          //通知在线好友, 新客户端下线了
         iter->second->addUserOffline(user);

      }
}

void MainWindow::onUserSendMsg(UserData from, UserData to, QString msg)
{
    //1.判断是否存在
    if(users.count(to))
    {
        //获取接收者的子线程
        SocketThread *t = users[to];

        //让子线程构建json串
        t->addUserReceiveMsg(from, to, msg);
    }
}

//void MainWindow::onReadyRead()
//{
//    qDebug() << "来消息了";
//    //获取接收信息
//    QByteArray data = socket->readAll();

//    //QByteArray -> QString
//    QString jsonStr = QString::fromLocal8Bit(data);
//    qDebug() << jsonStr;
//    //获取消息类型
//    int type = MsgBuilder::msgType(jsonStr);
//    //判断消息类型
//    switch(type)
//    {
//           case MsgBuilder::registerUser://注册用户 type :0
//        dealUserRegister(jsonStr);//处理用户注册的函数
//        break;
//    case MsgBuilder::login:
//        dealUserLogin(jsonStr);
//        break;
//    default:
//        break;
//}
//}
