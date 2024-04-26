#ifndef USERDAO_H
#define USERDAO_H
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

struct UserEntity
{
    //每个成员对应表中的一个字段，主要用于数据的传递
    int userId; //账号
    QString nickName; //昵称
    QString passwd; // 密码
    int headId; // 头像
};

//单例模式
class UserDao
{
private:
    UserDao();
    UserDao(const UserDao& o);
    static UserDao* ins;
    QSqlDatabase db ;

public:
    static UserDao* getIns();
    void createTable();//创建表
    bool insertTable(UserEntity& e); //用于注册阶段
    bool selectTable(bool &ok, UserEntity& e); //用于查询阶段, ok代表是否登录成功；
    ~UserDao();
};

#endif // USERDAO_H
