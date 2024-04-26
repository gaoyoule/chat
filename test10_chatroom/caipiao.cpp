#include "caipiao.h"
#include "ui_caipiao.h"
QString s; //输入得号码
QString s2; //7位号码
QString w; //中奖号码
int count; //输入得次数
int a[7]; //输出得号码
int top;
int b[7]; //中奖得号码
caipiao::caipiao(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::caipiao)
{
    ui->setupUi(this);
    //设置提醒字
    ui->lineEdit_ag->setPlaceholderText("请您输入7位数字");
    //字体颜色红色
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::red);
    ui->label->setPalette(pa);
    ui->label_2->setPalette(pa);
}

caipiao::~caipiao()
{
    delete ui;
}
void caipiao::on_pushButton_clear_clicked()
{
    s.clear();
    w.clear();
    ui->lineEdit_ag->setText(s);
    count = 0;
}

void caipiao::on_pushButton_ok_clicked()
{
    if(count > 7)
    {
        ui->lineEdit_ag->setText(s2);
        count = 7;
    }

}

void caipiao::on_pushButton_open_clicked()
{
    if(count != 7)
        return;
    int num = 0; // 中奖得位数
    //输入7位数字后，生成中奖号码
    if(count == 7)
    {
        //随机数种子；
        qsrand(QTime::currentTime().second());
        for(int i = 0; i < 7; i++)
        {
            //随机生产一个小于10得数字；
            int n = rand()%10;
            b[i] = n;
            //将数字转化成字符串
            QString s1 = QString("%1").arg(n);
            //字符串w,追加“ ”， s1；
            w.append("  ");
            w.append(s1);
        }
        ui->lineEdit_open->setText(w);

    }
    for(int i = 0; i < 7; i++)
    {
        qDebug() << a[i] << " " << b[i];
        if(a[i] == b[i])
            num++;
    }
    qDebug() << "num is :" << num;
    w.clear();
    s.clear();
    switch(num)
    {
    case 7:
        ui->lineEdit_win->setText("恭喜您，中奖一百万");
        break;
    case 6:
        ui->lineEdit_win->setText("恭喜您，中奖十万");
        break;
    case 5:
        ui->lineEdit_win->setText("恭喜您，中奖一万");
        break;
    case 4:
        ui->lineEdit_win->setText("恭喜您，中奖两千");
        break;
    case 3:
        ui->lineEdit_win->setText("恭喜您，中奖一百");
        break;
    default:
        ui->lineEdit_win->setText("很遗憾，您没有中奖");
    }
    top = 0;
}

void caipiao::on_pushButton_1_clicked()
{
    //判断输入得次数
    if(count == 7)
        s2 = s;
    if(count < 7)
        a[top++] = 1;
    ui->lineEdit_ag->setText("  1");
    s.append("  1");
    ui->lineEdit_ag->setText(s);
    count++;
}

void caipiao::on_pushButton_2_clicked()
{
    if(count == 7)
        s2 = s;
    if(count < 7)
        a[top++] = 2;
    ui->lineEdit_ag->setText("  2");
    s.append("  2");
    ui->lineEdit_ag->setText(s);
    count++;

}

void caipiao::on_pushButton_3_clicked()
{
    if(count == 7)
        s2 = s;
    if(count < 7)
        a[top++] = 3;
    ui->lineEdit_ag->setText("  3");
    s.append("  3");
    ui->lineEdit_ag->setText(s);
    count++;
}

void caipiao::on_pushButton_4_clicked()
{
    if(count == 7)
        s2 = s;
    if(count < 7)
        a[top++] = 4;
    ui->lineEdit_ag->setText("  4");
    s.append("  4");
    ui->lineEdit_ag->setText(s);
    count++;
}

void caipiao::on_pushButton_5_clicked()
{    if(count == 7)
        s2 = s;
    if(count < 7)
        a[top++] = 5;
    ui->lineEdit_ag->setText("  5");
     s.append("  5");
      ui->lineEdit_ag->setText(s);
       count++;
}

void caipiao::on_pushButton_6_clicked()
{
    if(count == 7)
        s2 = s;
    if(count < 7)
        a[top++] = 6;
    ui->lineEdit_ag->setText("  6");
    s.append("  6");
    ui->lineEdit_ag->setText(s);
    count++;
}

void caipiao::on_pushButton_7_clicked()
{
    if(count == 7)
        s2 = s;
    if(count < 7)
        a[top++] = 7;
    ui->lineEdit_ag->setText("  7");
    s.append("  7");
    ui->lineEdit_ag->setText(s);
    count++;
}

void caipiao::on_pushButton_8_clicked()
{
    if(count == 7)
        s2 = s;
    if(count < 7)
        a[top++] = 8;
    ui->lineEdit_ag->setText("  8");
    s.append("  8");
    ui->lineEdit_ag->setText(s);
    count++;
}

void caipiao::on_pushButton_9_clicked()
{
    if(count == 7)
        s2 = s;
    if(count < 7)
        a[top++] = 9;
    ui->lineEdit_ag->setText("  9");
    s.append("  9");
    ui->lineEdit_ag->setText(s);
    count++;
}

void caipiao::on_pushButton_0_clicked()
{
    if(count == 7)
        s2 = s;
    if(count < 7)
        a[top++] = 0;
    ui->lineEdit_ag->setText("  0");
    s.append("  0");
    ui->lineEdit_ag->setText(s);
    count++;
}

