#include "caishuzi.h"
#include "ui_caishuzi.h"
int num;
int n;

caishuzi::caishuzi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::caishuzi)
{
    ui->setupUi(this);
    //设置提醒字
    ui->lineEdit_in1->setPlaceholderText("请您输入小于100的数字");
    //字体颜色红色
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::red);
    ui->label->setPalette(pa);
}

caishuzi::~caishuzi()
{
    delete ui;
}

void caishuzi::on_pushButton_1_clicked()
{
    //随机数种子；
    qsrand(QTime::currentTime().second());
    n = rand() % 100 + 1;
    num = ui->lineEdit_in1->text().toInt();
    if (n < num)
        ui->lineEdit_1->setText("您输入大了，请重新输入");
    else if(n > num)
        ui->lineEdit_1->setText("您输入小了， 请重新输入");
    else
    {
        ui->lineEdit_1->setText("you are winner!");
    }
}

void caishuzi::on_pushButton_2_clicked()
{
    //设置提醒字
    ui->lineEdit_in_2->setPlaceholderText("请您再次输入小于100的数字");
    num = ui->lineEdit_in_2->text().toInt();
    if (n < num)
        ui->lineEdit_2->setText("您输入大了，请重新输入");
    else if(n > num)
        ui->lineEdit_2->setText("您输入小了， 请重新输入");
    else
    {
        ui->lineEdit_2->setText("you are winner!");

    }
}

void caishuzi::on_pushButton_3_clicked()
{
    //设置提醒字
    ui->lineEdit_in_3->setPlaceholderText("请您再次输入小于100的数字");

    num = ui->lineEdit_in_3->text().toInt();
    if(num == n)
        ui->lineEdit_3->setText("you are winner!");
    else
        ui->lineEdit_3->setText("游戏结束，您失败了！");

    //字体颜色红色
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::red);
    ui->label_2->setPalette(pa);
    QString s = QString::number(n);
    ui->label_2->setText(s);
}
