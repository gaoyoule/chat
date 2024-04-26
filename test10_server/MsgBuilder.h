#ifndef MSGBUILDER_H
#define MSGBUILDER_H

#include "CJsonObject.hpp"
#include <QString>
#include <vector>

using namespace neb;
using namespace std;

struct UserData//封装用户基本信息
{
    int id;//账号
    QString password;
    int headId;//我的demo没有的，预留的数据
    QString nickname;
    bool operator<(const UserData& other)const
    {
        return id < other.id;
    }
};

class MsgBuilder
{
public:
    enum MsgType//消息类型
    {
        registerUser,       //注册用户
        registerUserReturn, //注册用户服务器返回
        login,              //登录
        loginSucReturn,     //登录成功服务器返回
        loginLoseReturn,    //登录失败服务器返回
        sendMsg,            //发送聊天消息
        receiveMsg,         //收到聊天信息
        userOnline,         //用户上线
        userOffline,        //用户下线
    };

    //获取消息类型
    static int msgType(QString jsonStr);
    //以build开头的函数都是在构建json串 以parse开头的函数都是在解析json串
    //注册用户    
    static QString buildRegisterUserMsg(QString password, int headId, QString nickname);
    static UserData parseRegisterUserMsg(QString jsonStr);
    //注册用户返回
    static QString buildRegisterUserReturnMsg(int id);
    static int parseRegisterUserReturnMsg(QString jsonStr);
    //登录
    static QString buildLoginMsg(int id, QString password);
    static UserData parseLoginMsg(QString jsonStr);
    //登录返回
    static QString buildLoginSucReturnMsg(UserData hostData, vector<UserData>& friends);
    static vector<UserData> parseLoginSucReturnMsg(UserData& hostData, QString jsonStr);
    static QString buildLoginLoseReturnMsg();
    //发送聊天数据
    static QString buildSendMsg(UserData from, UserData to, QString msg);
    static QString parseSendMsg(QString jsonStr, UserData& from, UserData& to);
    //收到聊天信息
    static QString buildReceiveMsg(UserData from, UserData to, QString msg);
    static QString parseReceiveMsg(QString jsonStr, UserData& from, UserData& to);
    //用户上线
    static QString buildUserOnline(UserData user);
    static UserData parseUserOnline(QString jsonStr);
    //用户下线
    static QString buildUserOffline(UserData user);
    static UserData parseUserOffline(QString jsonStr);
};

#endif // MSGBUILDER_H
