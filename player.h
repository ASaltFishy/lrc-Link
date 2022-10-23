#ifndef PLAYER_H
#define PLAYER_H
#include <QKeyEvent>
#include <QPainter>
#include <QObject>
#include "gamemap.h"

#define scorePerPair 5

class Player:public QObject
{
    Q_OBJECT
    friend class QlinkTest;

private:
    //玩家坐标
    int x;
    int y;
    //玩家分数
    int score;
    //玩家类型（决定玩家用哪套键盘控制1-上下左右 2-WASD）
    int type;
    struct Point{
    public:
         // type:0为空白，1-10为供消除的连连看箱子，11--+1s，12--shuffle,13--hint,14--false
        int type;
        Point(int _type = 0):type(_type){}
    };
    //用于记录当前的激活的元素个数
    struct ActivePoint:Point{
    public:
        int x;
        int y;
         // type:0为空白，1-10为供消除的连连看箱子，11--+1s，12--shuffle,13--hint,14--false,player代表激活箱子的用户类型
        ActivePoint(int _x,int _y,int _type = 0):Point(_type){x=_x;y=_y;}
        ActivePoint(int _type = 0):Point(_type){}
    };
    //单独为每一个玩家维护一个active数组
    QVector<ActivePoint> activePoint;
    //记录消除的要画连线的配对
    QVector<ActivePoint> eliminatePair;

public:
    Player(int _x = 0,int _y = 0,int _type = 1);
    Player(const QJsonObject &json,int _type);
    ~Player();
    //处理按键事件
    void keyPress(QKeyEvent *event, GameMap &game);
    //绘制事件
    void paintPlayer(QPainter *painter);
    void paintActivate(QPainter *painter);
    void drawLine(QPainter *painter,GameMap &game);
    //更新分数
    int getScore();
    //保存与加载
    void load(const QJsonObject &json);
    void save(QJsonObject &json) const;
    void refreshHint(GameMap &game);
signals:
    void gameOver();
    void refreshScore();
private:
    //激活箱子
    void activateBlock(int x,int y, GameMap &game);
    //判断两个点之间能否直接连接
    bool isDirectlyLinkable(int x1,int y1,int x2,int y2, GameMap &game);
    //寻找以两个点为对角线的矩形另外两个顶点
    //找到后返回true并把x2、y2更改为折点坐标
    bool findInteractPoint(const int &x1,const int &y1,int &x2,int &y2, GameMap &game);
    //获取某个图片元素的中点
    QPoint getCenterPoint(ActivePoint &point);
    //检查两个方块是否可连接
    bool checkEliminated(ActivePoint from,ActivePoint to,int &inflectionNum, GameMap &game,ActivePoint *inflection1=nullptr,ActivePoint *inflection2=nullptr);
    //检查有无可连接对剩余
    bool checkRemain(GameMap &game);

};

#endif // PLAYER_H
