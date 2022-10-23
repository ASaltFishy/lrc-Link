#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "qobject.h"
#include <QString>
#include <QPainter>
#include <QDebug>
#include <QVector>
#include <QTimer>
#include <algorithm>

#define iconWidth 60

class GameMap:public QObject
{
    Q_OBJECT

    friend class Player;
    friend class QlinkTest;

private:
    //结构体Point用于表示地图各元素的坐标和贴图类型
    struct Point{
    public:
         // type:0为空白，1-10为供消除的连连看箱子，11--+1s，12--shuffle,13--hint,14--flash
        int type;
        Point(int _type = 0):type(_type){}
    };

    //用于记录当前的激活的元素个数
    struct ActivePoint:Point{
    public:
        int x;
        int y;
         // type:0为空白，1-10为供消除的连连看箱子，11--+1s，12--shuffle,13--hint,14--flash,player代表激活箱子的用户类型
        ActivePoint(int _x,int _y,int _type = 0):Point(_type){x=_x;y=_y;}
        ActivePoint(int _type = 0):Point(_type){}
    };

    //地图高和宽
    int height;
    int width;
    //记录剩余配对数
    int pairNumber = 0;
    //记录Hint道具的开关
    bool hint = false;
    int hintTime = 10;
    QTimer *hintTimer = NULL;
    //记录提示的配对
    QVector<ActivePoint> hintPair;
    //记录地图数据的二维数组
    Point **map=nullptr;
    //记录贴图来源的数组
    QVector<QString> imgURL;
    //记录地图数据
    QVector<Point> tempMap;
    //将地图数据记为一个一维数组，相互转换的工具函数
    void mapToVector();
    void vectorToMap();
    void initImage();
public:
    GameMap(int _height=7,int _width=7);
    GameMap(int _height,int _width,int _forTest);
    GameMap(const QJsonObject &json);
    ~GameMap();

    //绘制地图
    void paintMap(QPainter *painter);

    //随机生成地图
    void initMap();

    //+1s
    void addOneProp();

    //shuffle
    void shuffleProp();

    //hint
    void hintProp();

    //load and save
    void load(const QJsonObject &json);
    void save(QJsonObject &json);
    //暂停提示道具计时，用于暂停状态
    void pauseHint();
    //for test
    void clearMap();

signals:
    void addOneSecond();
private slots:
    void endHint();


};

#endif // GAMEMAP_H
