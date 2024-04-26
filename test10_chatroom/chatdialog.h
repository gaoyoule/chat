#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QHBoxLayout>
#include "ChatWidget.h"
#include "MsgBuilder.h"
#include "mysocket.h"
#include <QColorDialog>

namespace Ui {
class ChatDialog;
}

class ChatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChatDialog(UserData user, QWidget *parent = 0);

    void addReceiveMsg(QString msg); //把好友消息显示在聊天列表的左侧

    void showWaitMsg(QStringList waitMsgs);//显示未读消息

    inline UserData getTo() //获取好友信息
    {
        return to;
    }
    QColor color;
    ~ChatDialog();

private slots:
    void on_pushButton_send_clicked();


    void on_pushButton_2_clicked();

    void on_pushButton_1_clicked(bool checked);

private:
    Ui::ChatDialog *ui;
    //创建聊天列表的类指针
    ChatWidget * chat;

    //创建套接字指针
    MySocket *socket;

    //创建保存自己信息的结构体
    UserData from;

    //创建保存好友的信息的结构体
    UserData to;
};

#endif // CHATDIALOG_H
