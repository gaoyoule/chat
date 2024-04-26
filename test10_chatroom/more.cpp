#include "more.h"
#include "ui_more.h"
#include "jisuanqi.h"
#include "caipiao.h"
#include "caishuzi.h"
More::More(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::More)
{
    ui->setupUi(this);
}

More::~More()
{
    delete ui;
}

//新建计算器界面
void More::on_pushButton_jisuanqi_clicked()
{
    jisuanqi *f = new jisuanqi(this);
    f->show();
}

//关闭更多窗口
void More::on_pushButton_5_clicked()
{
    More::close();
}

//彩票的槽函数
void More::on_pushButton_caipiao_clicked()
{
    caipiao *f = new caipiao(this);
    f->show();
}
//猜数字的槽函数
void More::on_pushButton_caishuzi_clicked()
{
    caishuzi *f = new caishuzi(this);
    f->show();
}
