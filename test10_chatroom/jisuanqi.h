#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QDebug>
#include <QString>

#include <QtCore/qmath.h>

enum btnType
{
    Num, //数字
    Op, //运算符
    PoT, //小数点
    Equal, //等于
    Clear, //清空
    Back, //退格
    Sq //次方
};

namespace Ui {
class jisuanqi;
}

class jisuanqi : public QMainWindow
{
    Q_OBJECT

public:
    explicit jisuanqi(QWidget *parent = 0);
    ~jisuanqi();


public slots:

    void OnClisked(btnType _type, QString _btn);

private slots:
    void on_btn_0_clicked();


    void on_btn_1_clicked();

    void on_btn_2_clicked();

    void on_btn_3_clicked();

    void on_btn_4_clicked();

    void on_btn_5_clicked();

    void on_btn_6_clicked();

    void on_btn_7_clicked();

    void on_btn_8_clicked();

    void on_btn_9_clicked();

    void on_btn_Add_clicked();

    void on_btn_Mul_clicked();

    void on_btn_Mod_clicked();

    void on_btn_Div_clicked();

    void on_btn_Sub_clicked();

    void on_btn_Squ_clicked();

    void on_btn_Sub1_clicked();

    void on_btn_Result_clicked();

    void on_btn_clear_clicked();

    void on_btn_Pot_clicked();

private:
    Ui::jisuanqi *ui;
    QString Num1;
    QString Num2;
    QString op;
    QString sq1;
    QString sq2;
    double sqR1 = 0;
    double sqR2 = 0;
};

#endif // MAINWINDOW_H
