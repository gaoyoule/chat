#include "MsgBuilder.h"

int MsgBuilder::msgType(QString jsonStr)
{
    int type;
    CJsonObject jsonObj(jsonStr.toStdString());
    jsonObj.Get("type", type);
    return type;
}

QString MsgBuilder::buildRegisterUserMsg(QString password, int headId, QString nickname)
{
    CJsonObject jsonObj;//CJsonObject是给数据加字段的容器
    jsonObj.Add("type", registerUser);//数据的类型，要注册用户，服务器端首先会看数据的type字段，根据不同的类型执行不同的逻辑
    jsonObj.Add("password", password.toStdString());//这里之所以把QString转成C++的string类型，因为第三方框架是独立的，不会支持QT的任何类型
    jsonObj.Add("headId", headId);
    jsonObj.Add("nickname", nickname.toStdString());
	//jsonObj.ToString() 将容器对象转换成JSON字符串
	//根据这个字符串创建一个QString对象，因为这个字符串要交给QT做处理
    QString retData(jsonObj.ToString().c_str());
    return retData;
}

UserData MsgBuilder::parseRegisterUserMsg(QString jsonStr)
{
    CJsonObject jsonObj(jsonStr.toStdString());//根据json字符串创建JSON容器对象
    UserData data;//用来存在解析后得到的数据
    std::string stdStr;
    jsonObj.Get("password", stdStr);//根据数据的字段获得数据
    data.password = QString(stdStr.c_str());
    jsonObj.Get("headId", data.headId);
    jsonObj.Get("nickname", stdStr);
    data.nickname = QString(stdStr.c_str());
    return data;
}

QString MsgBuilder::buildRegisterUserReturnMsg(int id)
{
    CJsonObject jsonObj;
    jsonObj.Add("type", registerUserReturn);
    jsonObj.Add("id", id);
    QString retData(jsonObj.ToString().c_str());
    return retData;
}

int MsgBuilder::parseRegisterUserReturnMsg(QString jsonStr)
{
    CJsonObject jsonObj(jsonStr.toStdString());
    int id;
    jsonObj.Get("id", id);
    return id;
}

QString MsgBuilder::buildLoginMsg(int id, QString password)
{
    CJsonObject jsonObj;
    jsonObj.Add("type", login);
    jsonObj.Add("id", id);
    jsonObj.Add("password", password.toStdString());
    QString retData(jsonObj.ToString().c_str());
    return retData;
}

UserData MsgBuilder::parseLoginMsg(QString jsonStr)
{
    CJsonObject jsonObj(jsonStr.toStdString());
    UserData data;
    std::string stdStr;
    jsonObj.Get("password", stdStr);
    data.password = QString(stdStr.c_str());
    jsonObj.Get("id", data.id); 
    return data;
}

QString MsgBuilder::buildLoginSucReturnMsg(UserData hostData, vector<UserData> &friends)
{
    CJsonObject jsonObj;
    jsonObj.Add("type", loginSucReturn);
    CJsonObject friendsArr;
    for(int i = 0;i < friends.size();i++)
    {
        CJsonObject friendObj;
        friendObj.Add("id", friends[i].id);
        friendObj.Add("headId", friends[i].headId);
        friendObj.Add("nickname", friends[i].nickname.toStdString());     
        friendsArr.Add(friendObj);
    }
    jsonObj.Add("friends", friendsArr);
    jsonObj.Add("hostId",hostData.id);
    jsonObj.Add("hostHeadId",hostData.headId);
    jsonObj.Add("hostNickname",hostData.nickname.toStdString());
    QString retData(jsonObj.ToString().c_str());
    return retData;
}

vector<UserData> MsgBuilder::parseLoginSucReturnMsg(UserData& hostData, QString jsonStr)
{
    vector<UserData> friends;
    CJsonObject jsonObj(jsonStr.toStdString());
    CJsonObject friendsArr;
    jsonObj.Get("friends", friendsArr);
    for(int i = 0;i < friendsArr.GetArraySize();i++)
    {
        UserData data;
        CJsonObject friendObj = friendsArr[i];
        friendObj.Get("id", data.id);
        friendObj.Get("headId", data.headId);
        string nickname;
        friendObj.Get("nickname", nickname);
        data.nickname = QString(nickname.c_str());
        friends.push_back(data);
    }
    jsonObj.Get("hostId", hostData.id);
    jsonObj.Get("hostHeadId", hostData.headId);
    string hostNickname;
    jsonObj.Get("hostNickname", hostNickname);
    hostData.nickname = QString(hostNickname.c_str());
    return friends;
}

QString MsgBuilder::buildLoginLoseReturnMsg()
{
    CJsonObject jsonObj;
    jsonObj.Add("type", loginLoseReturn);
    QString retData(jsonObj.ToString().c_str());
    return retData;
}

QString MsgBuilder::buildSendMsg(UserData from, UserData to, QString msg)
{
    CJsonObject jsonObj;
    jsonObj.Add("type", sendMsg);
    jsonObj.Add("fromId", from.id);
    jsonObj.Add("toId", to.id);
    jsonObj.Add("msg", msg.toStdString());
    QString ret(jsonObj.ToString().c_str());
    return ret;
}

QString MsgBuilder::parseSendMsg(QString jsonStr, UserData &from, UserData &to)
{
    CJsonObject jsonObj(jsonStr.toStdString());
    jsonObj.Get("fromId", from.id);
    jsonObj.Get("toId", to.id);
    string msg;
    jsonObj.Get("msg", msg);
    return QString(msg.c_str());
}

QString MsgBuilder::buildReceiveMsg(UserData from, UserData to, QString msg)
{
    CJsonObject jsonObj;
    jsonObj.Add("type", receiveMsg);
    jsonObj.Add("fromId", from.id);
    jsonObj.Add("toId", to.id);
    jsonObj.Add("msg", msg.toStdString());
    QString ret(jsonObj.ToString().c_str());
    return ret;
}

QString MsgBuilder::parseReceiveMsg(QString jsonStr, UserData &from, UserData &to)
{
    CJsonObject jsonObj(jsonStr.toStdString());
    jsonObj.Get("fromId", from.id);
    jsonObj.Get("toId", to.id);
    string msg;
    jsonObj.Get("msg", msg);
    return QString(msg.c_str());
}

QString MsgBuilder::buildUserOnline(UserData user)
{
    CJsonObject jsonObj;
    jsonObj.Add("type", userOnline);
    jsonObj.Add("id", user.id);
    jsonObj.Add("headId", user.headId);
    jsonObj.Add("nickname", user.nickname.toStdString());
    QString ret(jsonObj.ToString().c_str());
    return ret;
}

UserData MsgBuilder::parseUserOnline(QString jsonStr)
{
    UserData user;
    CJsonObject jsonObj(jsonStr.toStdString());
    jsonObj.Get("id", user.id);
    jsonObj.Get("headId", user.headId);
    string nickname;
    jsonObj.Get("nickname", nickname);
    user.nickname = QString(nickname.c_str());
    return user;
}

QString MsgBuilder::buildUserOffline(UserData user)
{
    CJsonObject jsonObj;
    jsonObj.Add("type", userOffline);
    jsonObj.Add("id", user.id);
    jsonObj.Add("headId", user.headId);
    jsonObj.Add("nickname", user.nickname.toStdString());
    QString ret(jsonObj.ToString().c_str());
    return ret;
}

UserData MsgBuilder::parseUserOffline(QString jsonStr)
{
    UserData user;
    CJsonObject jsonObj(jsonStr.toStdString());
    jsonObj.Get("id", user.id);
    jsonObj.Get("headId", user.headId);
    string nickname;
    jsonObj.Get("nickname", nickname);
    user.nickname = QString(nickname.c_str());
    return user;
}


