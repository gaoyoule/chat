#include "myserver.h"

Myserver::Myserver(QObject *parent):QTcpServer(parent)
{

}

void Myserver::incomingConnection(qintptr socketDescriptor)
{
    //发送自定义信号发送给主线程
   emit sig_sendsd(socketDescriptor);
}

Myserver::~Myserver()
{

}

