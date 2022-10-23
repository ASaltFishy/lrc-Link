#include "timer.h"
#include <QJsonObject>
#include <QDebug>

#define defaultAddOneTime 30

//构造函数，传入倒计时的开始时间
Timer::Timer(int _beginCount)
{
    beginCount = _beginCount;
}

//构造函数，根据json对象还原计时状态
Timer::Timer(const QJsonObject &json)
{
    load(json);
}


Timer::~Timer()
{
}

//获取当前时间的信号槽函数
//返回当前游戏剩余是时间
int Timer::getTime()
{
    return --beginCount;
}

//剩余时间增加函数，响应+1道具
int Timer::addOne()
{
    beginCount+=defaultAddOneTime;
    return beginCount;
}

//加载函数，传入json对象还原计时器状态
void Timer::load(const QJsonObject &json)
{
    if(json.contains("beginCount")){
        beginCount = json["beginCount"].toInt();
    }
    else{
        qDebug()<<"Timer::json 解析错误"<<Qt::endl;
    }

}

//保存函数，将当前状态保存至json对象
void Timer::save(QJsonObject &json) const
{
    json["beginCount"] = beginCount;
}
