#ifndef CAISHUZI_H
#define CAISHUZI_H

#include <QDialog>
#include <QTime>

namespace Ui {
class caishuzi;
}

class caishuzi : public QDialog
{
    Q_OBJECT

public:
    explicit caishuzi(QWidget *parent = 0);
    ~caishuzi();

private slots:
    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::caishuzi *ui;
};

#endif // CAISHUZI_H
