#include "jisuanqi.h"
#include "ui_jisuanqi.h"

jisuanqi::jisuanqi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::jisuanqi)
{
    ui->setupUi(this);
    /*
    //数字按键绑定
    connect(ui->btn_0, &QPushButton::clicked,[this](){OnClisked(Num, "0");});
    connect(ui->btn_1, &QPushButton::clicked,[this](){OnClisked(Num, "1");});
    connect(ui->btn_2, &QPushButton::clicked,[this](){OnClisked(Num, "2");});
    connect(ui->btn_3, &QPushButton::clicked,[this](){OnClisked(Num, "3");});
    connect(ui->btn_4, &QPushButton::clicked,[this](){OnClisked(Num, "4");});
    connect(ui->btn_5, &QPushButton::clicked,[this](){OnClisked(Num, "5");});
    connect(ui->btn_6, &QPushButton::clicked,[this](){OnClisked(Num, "6");});
    connect(ui->btn_7, &QPushButton::clicked,[this](){OnClisked(Num, "7");});
    connect(ui->btn_8, &QPushButton::clicked,[this](){OnClisked(Num, "8");});
    connect(ui->btn_9, &QPushButton::clicked,[this](){OnClisked(Num, "9");});

    //逻辑按键绑定
    connect(ui->btn_Add, &QPushButton::clicked,[this](){OnClisked(Op, "+");});
    connect(ui->btn_Mul, &QPushButton::clicked,[this](){OnClisked(Op, "*");});
    connect(ui->btn_Mod, &QPushButton::clicked,[this](){OnClisked(Op, "%");});
    connect(ui->btn_Div, &QPushButton::clicked,[this](){OnClisked(Op, "/");});
    connect(ui->btn_Sub, &QPushButton::clicked,[this](){OnClisked(Op, "-");});
    connect(ui->btn_Squ, &QPushButton::clicked,[this](){OnClisked(Sq, "^");});

    //其他按键
    connect(ui->btn_Sub1, &QPushButton::clicked,[this](){OnClisked(Back, "0");});
    connect(ui->btn_Result, &QPushButton::clicked,[this](){OnClisked(Equal, "=");});
    connect(ui->btn_clear, &QPushButton::clicked,[this](){OnClisked(Clear, "clear");});
    connect(ui->btn_Pot, &QPushButton::clicked,[this](){OnClisked(PoT, ".");});
    */
}

jisuanqi::~jisuanqi()
{
    delete ui;
}

void jisuanqi::OnClisked(btnType _type, QString _btn)
{

    switch (_type) {
    case Num:
        //判断运算符是否存在（判断次方位置）
        if(op.isEmpty())
        {
            if(!sq1.isEmpty())
            {
                Num1.chop(1);
                sqR1=qPow(Num1.toDouble(),_btn.toInt());
                qDebug()<<sqR1;
                Num1+="^";
                //sq1.clear();

            }
            Num1+=_btn;
        }
        else
        {
            if(!sq2.isEmpty() )
            {
                Num2.chop(1);
                sqR2=qPow(Num2.toDouble(),_btn.toInt());
                qDebug()<<sqR2;
                Num2+="^";
                //sq2.clear();
            }
            Num2+=_btn;
        }
        break;
    case Op:
        //连续运算
        if(!Num1.isEmpty() && !Num2.isEmpty() && !op.isEmpty())
        {
            double num1=Num1.toDouble();
            double num2=Num2.toDouble();
            double result2=0.0;
            if(op=="+")
            {
                result2=num1+num2;
            }
            else if(op=="-")
            {
                result2=num1-num2;
            }
            else if(op=="*")
            {
                result2=num1*num2;
            }
            else if(op=="/")
            {
                if(num2!=0.0)
                {
                    result2=num1/num2;
                }
                else
                {
                    ui->lineEdit->setText("输入错误！");
                }
            }
            else if(op=="%")
            {
                if(num2!=0.0)
                {
                    int num3=Num1.toInt();
                    int num4=Num2.toInt();
                    while(num3>num4)
                    {
                        num3-=num4;
                    }
                    result2=num3;
                }
                else
                {
                    ui->lineEdit->setText("输入错误！");
                }
                qDebug()<<result2;

            }
            ui->lineEdit->setText(QString::number(result2));
            Num1=QString::number(result2);
            Num2.clear();
        }
        op=_btn;
        break;
    case Clear:
        Num1.clear();
        Num2.clear();
        op.clear();
        sq1.clear();
        sq2.clear();
        sqR1=0;
        sqR2=0;
        break;
    case PoT:
        if(op.isEmpty())
        {
            if(!Num1.isEmpty() && !Num1.contains("."))//操作数没有点且不为空
            {
                Num1+=".";
            }

        }
        else
        {
            if(!Num2.isEmpty() && !Num2.contains("."))
            {
                Num2+=".";
            }

        }
        break;
    case Equal:
    {
        double result2=0.0;
        double num1;
        double num2;
        if(sqR1!=0)
        {
            num1=sqR1;
            if(sqR2!=0)
            {
                num2=sqR2;
            }
            else
            {
                num2=Num2.toDouble();
            }
        }
        else
        {
            if(sqR2!=0)
            {
                num1=Num1.toDouble();
                num2=sqR1;
            }
            else
            {
                num1=Num1.toDouble();
                num2=Num2.toDouble();
            }

        }
        if(sqR1!=0 && sqR2==0)
        {
            result2=num1;
        }
        if(Num2.isEmpty() && sqR1==0)
        {
            return;
        }


        if(op=="+")
        {
            result2=num1+num2;
        }
        else if(op=="-")
        {
            result2=num1-num2;
        }
        else if(op=="*")
        {
            result2=num1*num2;
        }
        else if(op=="/")
        {
            if(num2!=0.0)
            {
                result2=num1/num2;
            }
            else
            {
                ui->lineEdit->setText("输入错误！");
            }
        }
        else if(op=="%")
        {
            if(num2!=0.0)
            {
                result2=Num1.toInt()%Num2.toInt();

            }
            else
            {
                ui->lineEdit->setText("输入错误！");
            }
            qDebug()<<result2;

        }
        ui->lineEdit->setText(QString::number(result2));
        Num1=QString::number(result2);
        Num2.clear();
        op.clear();
        return;
        break;
    }
    case Back:
    {

        if(!Num1.isEmpty())
        {
            if(!Num2.isEmpty())
            {
                Num2.chop(1);//尾部删除字符串（指定个数）
            }
            else if(!op.isEmpty())
            {
                op.chop(1);
            }
            else
            {
                Num1.chop(1);
            }
        }
        break;
    }
    case Sq:
    {
        if(!op.isEmpty())
        {
            sq2=_btn;
            Num2+=sq2;
        }
        else
        {
            sq1=_btn;
            Num1+=sq1;
        }
        break;
    }
    default:
        break;
    }
    ui->lineEdit->setText(Num1+op+Num2);

}

void jisuanqi::on_btn_0_clicked()
{
    OnClisked(Num, "0");
}


void jisuanqi::on_btn_1_clicked()
{
    OnClisked(Num, "1");
}

void jisuanqi::on_btn_2_clicked()
{
    OnClisked(Num, "2");
}

void jisuanqi::on_btn_3_clicked()
{
    OnClisked(Num, "3");
}

void jisuanqi::on_btn_4_clicked()
{
    OnClisked(Num, "4");
}

void jisuanqi::on_btn_5_clicked()
{
    OnClisked(Num, "5");
}

void jisuanqi::on_btn_6_clicked()
{
    OnClisked(Num, "6");
}

void jisuanqi::on_btn_7_clicked()
{
    OnClisked(Num, "7");
}

void jisuanqi::on_btn_8_clicked()
{
    OnClisked(Num, "8");
}

void jisuanqi::on_btn_9_clicked()
{
    OnClisked(Num, "9");
}

void jisuanqi::on_btn_Add_clicked()
{
    OnClisked(Op, "+");
}

void jisuanqi::on_btn_Mul_clicked()
{
    OnClisked(Op, "*");
}

void jisuanqi::on_btn_Mod_clicked()
{
    OnClisked(Op, "%");
}

void jisuanqi::on_btn_Div_clicked()
{
    OnClisked(Op, "/");
}

void jisuanqi::on_btn_Sub_clicked()
{
    OnClisked(Op, "-");
}

void jisuanqi::on_btn_Squ_clicked()
{
    OnClisked(Sq, "^");
}

void jisuanqi::on_btn_Sub1_clicked()
{
    OnClisked(Back, "0");
}

void jisuanqi::on_btn_Result_clicked()
{
    OnClisked(Equal, "=");
}

void jisuanqi::on_btn_clear_clicked()
{
    OnClisked(Clear, "clear");
}

void jisuanqi::on_btn_Pot_clicked()
{
    OnClisked(PoT, ".");
}
