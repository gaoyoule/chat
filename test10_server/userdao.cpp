#include "userdao.h"
UserDao *UserDao::ins = NULL;
UserDao::UserDao()
{
    //加载驱动
    db = QSqlDatabase::addDatabase("QSQLITE");
    //设置数据库主机名称
    db.setHostName("test");

    //设置数据库文件名称；
    db.setDatabaseName("test.db");

    //打开数据库
    db.open();

    //创建表
    createTable();
}

UserDao::UserDao(const UserDao &o)
{

}

UserDao *UserDao::getIns()
{
    if(ins == NULL)
    {
        ins = new UserDao;
    }
    return ins;
}

void UserDao::createTable()
{
    //创建操作数据库的类对象
     QSqlQuery query;
     //执行sql语句
     query.exec("create table if not exists user("
                "userid integer primary key autoincrement,"
                "password varchar(20),"
                "nickname varchar(20),"
                "headid integer);");
     //插入数据 让账号从100001开始
     query.exec("insert into user values(100000, 'abc123', 'admine', 0)");
}

bool UserDao::insertTable(UserEntity &e)
{
    //创建操作数据库的类对象
    QSqlQuery query;
    //准备sql
    query.prepare("insert into user(password, nickname, headid) values(?, ?, ?);");
    //绑定数据
    query.bindValue(0, e.passwd);
    query.bindValue(1,e.nickName);
    query.bindValue(2, e.headId);
    //插入数据
    bool ok = query.exec();//执行语句
    if(ok == true)
    {
        qDebug() << "插入表";
        //获取最新的插入id
        query.exec("select LAST_INSERT_ROWID();");

        //判断是否查询到数据
        if(query.next())
        {
            //获取到id值并更新给结构体； query.record():获取一行记录。
            e.userId = query.record().value(0).toInt();
        }
    }
    else
    {
        qDebug() << "插入失败";
    }
    return ok;
}

bool UserDao::selectTable(bool &ok, UserEntity &e)
{
    //创建操作数据库的类对象
    QSqlQuery query;
    //准备sql语句
    query.prepare("select* from user where userid = ? and password = ?;");

    //绑定参数
    query.bindValue(0, e.userId);
    query.bindValue(1, e.passwd);

    //执行语句
    bool okk = query.exec();

    //判断是否查询时数据
    if(query.next())
    {
        //登录成功
        ok = true;
        //同步数据
        e.nickName = query.record().value(2).toString();
        e.headId = query.record().value(3).toInt();
    }
    else
    {
        //登录失败
        ok = false;
    }
    return okk;
}

UserDao::~UserDao()
{
    //关闭数据库
    db.close();
}

