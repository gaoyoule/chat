#include "friendsdialog.h"
#include "ui_friendsdialog.h"
#include "more.h"
friendsDialog::friendsDialog(UserData host, vector<UserData> friends, QWidget *parent) :
    QDialog(parent),friends(friends),
    ui(new Ui::friendsDialog)
{
    ui->setupUi(this);

    //获取套接字
    socket = MySocket::getIns();
    //拼接字符串
    QString str = QString("%1(%2)").arg(host.nickname).arg(host.id);
    ui->label->setText(str);

    //保存自己的信息
    socket->setSelf(host);

    //显示好友
    for(vector<UserData>::iterator it = friends.begin(); it != friends.end(); it++ )
    {
        //创建自定义界面
        FriendForm *ff = new FriendForm(*it, ui->listWidget);

        //创建行对象
        QListWidgetItem *item = new QListWidgetItem(ui->listWidget);

        //修改行对象尺寸
        item->setSizeHint(ff->size());
        //三者进行绑定
        ui->listWidget->setItemWidget(item, ff);

    }
//接收信息时 套接字发送的信号readyRead
    connect(socket, SIGNAL(readyRead()), this, SLOT(onFriendRead()));
}

void friendsDialog::dealUserOnline(QString json)
{
    //解析json
    UserData user = MsgBuilder::parseUserOnline(json);

    //创建自定义界面
    FriendForm *ff = new FriendForm(user, ui->listWidget);

    //创建行对象
    QListWidgetItem *item = new QListWidgetItem(ui->listWidget);

    //修改行对象尺寸
    item->setSizeHint(ff->size());
    //三者进行绑定
    ui->listWidget->setItemWidget(item, ff);

    //存放数据
    friends.push_back(user);
}

void friendsDialog::dealUserOffline(QString json)
{
    //解析json
    UserData user = MsgBuilder::parseUserOffline(json);

    //遍历好友列表
    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        //获取行对象
        QListWidgetItem* it = ui->listWidget->item(i);
        //获取控件对象
       QWidget * w =  ui->listWidget->itemWidget(it);
       //获取自定义控件
       FriendForm *f = dynamic_cast<FriendForm *>(w);

       //判断是否是下线好友
       if(f->getUser().id == user.id)
       {
           //移除好友
           ui->listWidget->takeItem(i);
           delete f;
           delete it;
           break;
       }
    }
    //删除好友信息
    //    friends.erase(iter);
}

void friendsDialog::dealUserReceiveMsg(QString json)
{
    //创建保存数据的结构体
    UserData from, to;

    //解析json串
    QString msg = MsgBuilder::parseReceiveMsg(json, from, to);

    //判断窗口是否打开,如果打开就不用打开了
    if(chatFriends.count(from))
    {
        //把信息显示在聊天列表的左侧
        ChatDialog *c = chatFriends[from];
        c->addReceiveMsg(msg);
    }
    else
    {
        //遍历好友列表
        for(int i = 0; i < ui->listWidget->count(); i++)
        {
            //获取行对象
            QListWidgetItem* it = ui->listWidget->item(i);
            //获取控件对象
           QWidget * w =  ui->listWidget->itemWidget(it);
           //获取自定义控件
           FriendForm *f = dynamic_cast<FriendForm *>(w);

           //判断是否是下线好友
           if(f->getUser().id == from.id)
           {
               //把未读信息保存起来
               f->addWaitMsg(msg);
               //新消息提醒
               f->msgTip(true);
           }
        }
    }

}

friendsDialog::~friendsDialog()
{
    delete ui;
}

void friendsDialog::onFriendRead()
{
    //获取接收的消息
    QByteArray data = socket->readAll();
    //QByteArray -> QString
    QString jsonStr = QString::fromLocal8Bit(data);

    qDebug() << jsonStr;
    //获取消息类型
    int type = MsgBuilder::msgType(jsonStr);
    //判断消息类型
    switch (type) {
    case MsgBuilder::receiveMsg:// 接收信息 type : 6
        //处理接收信息的函数
        dealUserReceiveMsg(jsonStr);
        break;
    case MsgBuilder::userOnline:// 用户上线 type : 7
        //处理用户上线的函数
        dealUserOnline(jsonStr);
        break;
    case MsgBuilder::userOffline:// 用户下线 type : 8
        //处理用户上线的函数
        dealUserOffline(jsonStr);

        break;
    default:
        break;
    }

}

void friendsDialog::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    //获取控件对象
    QWidget *w = ui->listWidget->itemWidget(item);

    //获取自定义控件
    //父类转子类（下型转换）
    //获取控件对象
    FriendForm *f = dynamic_cast<FriendForm *>(w);

    //获取好友信息
    UserData user = f->getUser();

    //判断窗口是否打开,如果打开就不用打开了
    if(chatFriends.count(user))
    {
        return ;
    }
    //消除新消息
    f->msgTip(false);
    //获取未读消息
    QStringList lists = f->getWaitMsg();

    //页面切换(单聊）
    ChatDialog *chat = new ChatDialog(user, this);

    //连接函数，当单聊窗口被点×关闭时，会发出 rejected信号
    connect(chat, SIGNAL(rejected()), this, SLOT(onReject()));

    //页面显示
    chat->show();
    //显示未读信息
    chat->showWaitMsg(lists);

    //把正在聊天的信息保存到容器
    chatFriends[user] = chat;
}

void friendsDialog::onReject()
{
    //获取发送信号的对象
    QObject* obj = QObject::sender();
    //获取单聊的窗口
    ChatDialog *ch = dynamic_cast<ChatDialog *>(obj);

    //获取好友信息
    UserData to = ch->getTo();
    //查找
    map<UserData, ChatDialog*>::iterator iter = chatFriends.find(to);
    //判断是否找到
    if(iter != chatFriends.end())
    {
        chatFriends.erase(iter);//删除
    }

}

void friendsDialog::on_pushButton_more_clicked()
{
    More *f = new More(this);
    f->show();
}
