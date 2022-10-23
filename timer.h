#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QTimer>

class Timer:public QObject
{
    Q_OBJECT
public:
    Timer(int _beginCount=120);
    Timer(const QJsonObject &json);
    ~Timer();
    int getTime();
    int addOne();
    //保存与加载
    void load(const QJsonObject &json);
    void save(QJsonObject &json) const;
private:
    int beginCount;
};

#endif // TIMER_H
