#ifndef FRIENDSDIALOG_H
#define FRIENDSDIALOG_H

#include <QDialog>
#include "mysocket.h"
#include "friendform.h"
#include <QListWidgetItem>
#include "chatdialog.h"

namespace Ui {
class friendsDialog;
}

class friendsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit friendsDialog(UserData host, vector<UserData> friends, QWidget *parent = 0);

    //处理用户上线的函数
    void dealUserOnline(QString json);

    //处理用户下线的函数
    void dealUserOffline(QString json);

    //处理用户接收的信息的函数
    void dealUserReceiveMsg(QString json);

    ~friendsDialog();
private slots:
    void onFriendRead();//接收信息的槽函数

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);//头文件

    void onReject(); //单聊窗口关闭时的槽函数

    void on_pushButton_more_clicked();

private:
    Ui::friendsDialog *ui;

    //定义保存好友信息的容器
    vector<UserData> friends;

    //创建套接字指针
    MySocket *socket;

    //定义保存正在聊天的好友容器
    map<UserData, ChatDialog*> chatFriends;
};

#endif // FRIENDSDIALOG_H
