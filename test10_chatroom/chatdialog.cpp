#include "chatdialog.h"
#include "ui_chatdialog.h"

ChatDialog::ChatDialog(UserData user,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatDialog), to(user)
{
    ui->setupUi(this);
    //获取套接字对象
    socket = MySocket::getIns();

    //获取自己的信息
    from = socket->getSelf();

    //初始化聊天列表
    chat = new ChatWidget(this);

    //创建总布局（网格）
    QGridLayout *g = new QGridLayout(this);
    setLayout(g);


    //添加聊天的列表给总布局
    g->addWidget(chat, 0, 0, 1, 2);//从第一行第一列开始占1行2列

    //创建水平布局
    QHBoxLayout *h = new QHBoxLayout;
    h->addWidget(ui->pushButton_1);
    h->addWidget(ui->pushButton_2);

    //添加水平布局到总布局
    g->addLayout(h, 1, 0, 1, 2);

    //添加文本框给总布局
    g->addWidget(ui->textEdit, 2, 0, 1, 1);

    //添加发送按钮给总布局
    g->addWidget(ui->pushButton_send, 2, 1, 1, 1);

    //设置窗口标题
    setWindowTitle(QString("%1(%2)").arg(user.nickname).arg(user.id));


}

void ChatDialog::addReceiveMsg(QString msg)
{
    //把好友信息显示在左侧
    chat->addMsg(msg,to.headId,ChatItem::guest);
}

void ChatDialog::showWaitMsg(QStringList waitMsgs)
{
    for(QStringList::iterator it = waitMsgs.begin(); it != waitMsgs.end(); it++)
    {
        //把好友信息显示在左侧
        chat->addMsg(*it, to.headId, ChatItem::guest);
    }
}

ChatDialog::~ChatDialog()
{
    delete ui;
}

void ChatDialog::on_pushButton_send_clicked()
{
    //获取文本内容
    QString msg = ui->textEdit->toPlainText();
    //判断是否为空
    if(msg.isEmpty())
        return;

    //清空多行编辑框
    ui->textEdit->clear();
    //构建json串
   QString jsonStr =  MsgBuilder::buildSendMsg(from, to, msg);
    //发送给服务器
    socket->write(jsonStr.toLocal8Bit());

    //把消息显示在聊天列表的右侧
    chat->addMsg(msg, from.headId, ChatItem::host);

}

//字体颜色设计
void ChatDialog::on_pushButton_2_clicked()
{
    color = QColorDialog::getColor(color, this);
    if(color.isValid())
    {
        ui->textEdit->setTextColor(color);
        ui->textEdit->setFocus();
    }
}

//字体加粗
void ChatDialog::on_pushButton_1_clicked(bool checked)
{
    if(checked)
        ui->textEdit->setFontWeight(QFont::Bold);
    else
        ui->textEdit->setFontWeight(QFont::Normal);
    ui->textEdit->setFocus();
}
