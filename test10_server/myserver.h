#ifndef MYSERVER_H
#define MYSERVER_H
#include <QTcpServer>


class Myserver : public QTcpServer
{
    Q_OBJECT
public:
    Myserver(QObject *parent = 0);

    //重写
    void incomingConnection(qintptr socketDescriptor);

    ~Myserver();

    // 自定义信号， 属性随意；
    signals:
    void sig_sendsd(qintptr sd);

};

#endif // MYSERVER_H
