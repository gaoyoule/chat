#include "mysocket.h"
MySocket * MySocket:: ins = NULL;//懒汉模式

MySocket::MySocket()
{

}

MySocket::MySocket(const MySocket &o)
{

}

MySocket *MySocket::getIns()
{
    if(ins == NULL)
    {
        ins = new MySocket;//想什么时候用， 什么时候给
    }
    return ins;
}

MySocket::~MySocket()
{

}

