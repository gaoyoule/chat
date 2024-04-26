#ifndef MORE_H
#define MORE_H

#include <QMainWindow>

namespace Ui {
class More;
}

class More : public QMainWindow
{
    Q_OBJECT

public:
    explicit More(QWidget *parent = 0);
    ~More();


private slots:
    void on_pushButton_jisuanqi_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_caipiao_clicked();

    void on_pushButton_caishuzi_clicked();

private:
    Ui::More *ui;
};

#endif // MORE_H
