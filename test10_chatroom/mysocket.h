#ifndef MYSOCKET_H
#define MYSOCKET_H
#include <QTcpSocket>
#include "MsgBuilder.h"
//单例模式 : 保证一个类只有一个实例化对象, 并提供的一个全局访问点；
//实现方法： 1.私有化拷贝和构造函数 -》不能在类外创建实例化对象；
         //2.创建私有的静态类指针 -》保证创建一个实例化对象
         //3.公有的静态成员函数返回值时类指针 -》用来实例化对象；
class MySocket : public QTcpSocket
{
    MySocket();
    MySocket(const MySocket& o);
    static MySocket* ins;
    UserData self;//保存自己的信息

public:
    static MySocket* getIns();
    inline void setSelf(UserData self)
    {
        this->self = self;
    }

    inline UserData getSelf()
    {
        return self;
    }

    ~MySocket();
};

#endif // MYSOCKET_H
