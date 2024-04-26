#ifndef CAIPIAO_H
#define CAIPIAO_H

#include <QDialog>
#include <QTime>
#include <QDebug>

namespace Ui {
class caipiao;
}

class caipiao : public QDialog
{
    Q_OBJECT

public:
    explicit caipiao(QWidget *parent = 0);
    ~caipiao();
private slots:
    void on_pushButton_clear_clicked();

    void on_pushButton_ok_clicked();

    void on_pushButton_open_clicked();

    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_0_clicked();
private:
    Ui::caipiao *ui;
};

#endif // CAIPIAO_H
