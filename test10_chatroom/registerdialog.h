#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H
#include "mysocket.h"
#include "MsgBuilder.h"
#include "QDebug"
#include <QCloseEvent>

#include <QDialog>

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = 0);
    void closeEvent(QCloseEvent*); //重写关闭事件
    ~RegisterDialog();

private slots:
    void on_pushButton_register_clicked();

    void onRead();//接收服务器信息的槽函数；

private:
    Ui::RegisterDialog *ui;

    //创建套接字指针
    MySocket *socket;
};

#endif // REGISTERDIALOG_H
