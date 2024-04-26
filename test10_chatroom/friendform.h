#ifndef FRIENDFORM_H
#define FRIENDFORM_H

#include <QWidget>
#include"MsgBuilder.h"

namespace Ui {
class FriendForm;
}

class FriendForm : public QWidget
{
    Q_OBJECT

public:
    explicit FriendForm(UserData user, QWidget *parent = 0);

    //获取好友信息
    inline UserData getUser()
    {
        return user;
    }

    //添加未读的消息
    inline void addWaitMsg(QString msg)
    {
        //追加
        waitMsgs.append(msg);
    }

    //获取未读信息
    QStringList getWaitMsg();

    //新消息提醒
    void msgTip(bool flag);
    ~FriendForm();

private:
    Ui::FriendForm *ui;

    //定义保存好友信息的结构体
    UserData user;

    //定义保存未读信息的容器
    QStringList waitMsgs;
};

#endif // FRIENDFORM_H
