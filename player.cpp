#include "player.h"
#include <QJsonObject>

//构造函数，传入玩家的初始位置和类型（1为玩家一，2为玩家二）
Player::Player(int _x,int _y,int _type)
{
    x = _x;
    y = _y;
    type = _type;
    score = 0;
}

//构造函数，传入QJsonObject对象加载玩家状态
Player::Player(const QJsonObject &json, int _type)
{
    type = _type;
    load(json);
    emit(refreshScore());
}

//析构函数
Player::~Player()
{

}

//处理按键事件
void Player::keyPress(QKeyEvent *event,GameMap &game)
{
    if(type==1){
        switch(event->key()){
        case Qt::Key_Up:
            //上边界不能再走
            if(y==0);
            else{
                switch(game.map[x][y-1].type){
                //上面为空地，直接向上走
                case 0:
                    break;
                //上面为道具,消除它并向上走
                case 11:
                    game.map[x][y-1].type=0;
                    game.addOneProp();
                    break;
                case 12:
                    game.map[x][y-1].type=0;
                    game.shuffleProp();
                    refreshHint(game);
                    activePoint.clear();
                    break;
                case 13:
                    game.map[x][y-1].type=0;
                    refreshHint(game);
                    game.hintProp();
                    break;
                //上面为普通箱子，激活它！
                default:
                    activateBlock(x,y-1,game);
                }
                y--;
            }
            break;
        case Qt::Key_Down:
            //下边界不能再走
            if(y==game.height-1);
            else{
                switch(game.map[x][y+1].type){
                //下面为空地，直接向下走
                case 0:
                    break;
                //下面为道具,消除它并向下走
                case 11:
                    game.map[x][y+1].type=0;
                    game.addOneProp();
                    break;
                case 12:
                    game.map[x][y+1].type=0;
                    game.shuffleProp();
                    refreshHint(game);
                    activePoint.clear();
                    break;
                case 13:
                    game.map[x][y+1].type=0;
                    refreshHint(game);
                    game.hintProp();
                    break;
                //下面为普通箱子，激活它！
                default:
                    activateBlock(x,y+1,game);
                }
                y++;
            }
            break;
        case Qt::Key_Left:
            if(x==0);
            else{
                switch(game.map[x-1][y].type){
                //左面为空地，直接向左走
                case 0:
                    break;
                //左面为道具,消除它并向左走
                case 11:
                    game.map[x-1][y].type=0;
                    game.addOneProp();
                    break;
                case 12:
                    game.map[x-1][y].type=0;
                    game.shuffleProp();
                    refreshHint(game);
                    activePoint.clear();
                    break;
                case 13:
                    game.map[x-1][y].type=0;
                    refreshHint(game);
                    game.hintProp();
                    break;
                //左面为普通箱子，激活它！
                default:
                    activateBlock(x-1,y,game);
                }
                x--;
            }
            break;
        case Qt::Key_Right:
            if(x==game.width-1);
            else{
                switch(game.map[x+1][y].type){
                //右面为空地，直接向右走
                case 0:
                    break;
                //右面为道具,消除它并向右走
                case 11:
                    game.map[x+1][y].type=0;
                    game.addOneProp();
                    break;
                case 12:
                    game.map[x+1][y].type=0;
                    game.shuffleProp();
                    refreshHint(game);
                    activePoint.clear();
                    break;
                case 13:
                    game.map[x+1][y].type=0;
                    refreshHint(game);
                    game.hintProp();
                    break;
                //右面为普通箱子，激活它！
                default:
                    activateBlock(x+1,y,game);
                }
                x++;
            }
            break;
        }
    }
    else {
        switch(event->key()){
        case Qt::Key_W:
            //上边界不能再走
            if(y==0);
            else{
                switch(game.map[x][y-1].type){
                //上面为空地，直接向上走
                case 0:
                    break;
                //上面为道具,消除它并向上走
                case 11:
                    game.map[x][y-1].type=0;
                    game.addOneProp();
                    break;
                case 12:
                    game.map[x][y-1].type=0;
                    game.shuffleProp();
                    refreshHint(game);
                    activePoint.clear();
                    break;
                case 13:
                    game.map[x][y-1].type=0;
                    refreshHint(game);
                    game.hintProp();
                    break;
                //上面为普通箱子，激活它！
                default:
                    activateBlock(x,y-1,game);
                }
                y--;
            }
            break;
        case Qt::Key_S:
            //下边界不能再走
            if(y==game.height-1);
            else{
                switch(game.map[x][y+1].type){
                //下面为空地，直接向下走
                case 0:
                    break;
                //下面为道具,消除它并向下走
                case 11:
                    game.map[x][y+1].type=0;
                    game.addOneProp();
                    break;
                case 12:
                    game.map[x][y+1].type=0;
                    game.shuffleProp();
                    refreshHint(game);
                    activePoint.clear();
                    break;
                case 13:
                    game.map[x][y+1].type=0;
                    refreshHint(game);
                    game.hintProp();
                    break;
                //下面为普通箱子，激活它！
                default:
                    activateBlock(x,y+1,game);
                }
                y++;
            }
            break;
        case Qt::Key_A:
            if(x==0);
            else{
                switch(game.map[x-1][y].type){
                //左面为空地，直接向左走
                case 0:
                    break;
                //左面为道具,消除它并向左走
                case 11:
                    game.map[x-1][y].type=0;
                    game.addOneProp();
                    break;
                case 12:
                    game.map[x-1][y].type=0;
                    game.shuffleProp();
                    refreshHint(game);
                    activePoint.clear();
                    break;
                case 13:
                    game.map[x-1][y].type=0;
                    refreshHint(game);
                    game.hintProp();
                    break;
                //左面为普通箱子，激活它！
                default:
                    activateBlock(x-1,y,game);
                }
                x--;
            }
            break;
        case Qt::Key_D:
            if(x==game.width-1);
            else{
                switch(game.map[x+1][y].type){
                //右面为空地，直接向右走
                case 0:
                    break;
                //右面为道具,消除它并向右走
                case 11:
                    game.map[x+1][y].type=0;
                    game.addOneProp();
                    break;
                case 12:
                    game.map[x+1][y].type=0;
                    game.shuffleProp();
                    refreshHint(game);
                    activePoint.clear();
                    break;
                case 13:
                    game.map[x+1][y].type=0;
                    refreshHint(game);
                    game.hintProp();
                    break;
                //右面为普通箱子，激活它！
                default:
                    activateBlock(x+1,y,game);
                }
                x++;
            }
            break;
        }
    }

}

//绘制玩家贴图
void Player::paintPlayer(QPainter *painter)
{
    QString imgURL;
    if(type==1)
        imgURL = ":/imag/p1.png";
    else imgURL = ":/imag/p2.png";
    QImage img(imgURL);
    QRect rect(x*iconWidth,y*iconWidth,iconWidth,iconWidth);
    painter->drawImage(rect,img);
}

//绘制方块激活状态
void Player::paintActivate(QPainter *painter)
{
    QPen redPen,bluePen;
    redPen.setColor(Qt::darkGreen);
    redPen.setWidth(5);
    bluePen.setColor(Qt::blue);
    bluePen.setWidth(5);
    if(type==1){
        painter->setPen(redPen);
    }else{
        painter->setPen(bluePen);
    }
    for(int i=0;i<int(activePoint.size());i++){
        int x = activePoint[i].x;
        int y = activePoint[i].y;
        painter->drawRect(x*iconWidth,y*iconWidth,iconWidth,iconWidth);
    }
}

//绘制可连接之间的连线
void Player::drawLine(QPainter *painter,GameMap &game)
{
    //根据玩家类型更换画笔颜色
    QPen redPen,bluePen;
    redPen.setColor(Qt::darkGreen);
    redPen.setWidth(5);
    bluePen.setColor(Qt::blue);
    bluePen.setWidth(5);
    if(type==1){
        painter->setPen(redPen);
    }else{
        painter->setPen(bluePen);
    }
    int size = eliminatePair.size();
    if(size==0)
        return;
    else{
        switch(size){
        case 2:
            painter->drawLine(getCenterPoint(eliminatePair[0]),getCenterPoint(eliminatePair[1]));
            break;
        case 3:
            painter->drawLine(getCenterPoint(eliminatePair[0]),getCenterPoint(eliminatePair[2]));
            painter->drawLine(getCenterPoint(eliminatePair[2]),getCenterPoint(eliminatePair[1]));
            break;
        case 4:
            painter->drawLine(getCenterPoint(eliminatePair[0]),getCenterPoint(eliminatePair[2]));
            painter->drawLine(getCenterPoint(eliminatePair[2]),getCenterPoint(eliminatePair[3]));
            painter->drawLine(getCenterPoint(eliminatePair[3]),getCenterPoint(eliminatePair[1]));
            break;
        }
        game.map[eliminatePair[0].x][eliminatePair[0].y].type = 0;
        game.map[eliminatePair[1].x][eliminatePair[1].y]=0;
        if(game.hint){
            //若消除的方块对为提示块中至少之一则更新提示
            if(game.map[game.hintPair[0].x][game.hintPair[0].y].type==0 ||
                    game.map[game.hintPair[1].x][game.hintPair[1].y].type==0)
                refreshHint(game);
        }
        eliminatePair.clear();
    }
}

//获取玩家分数
int Player::getScore()
{
    return score;
}

//根据json对象读取玩家位置和分数
void Player::load(const QJsonObject &json)
{
    if(json.contains("x-"+QString::number(type))&&
            json.contains("y-"+QString::number(type))&&
            json.contains("score-"+QString::number(type))){
        x = json["x-"+QString::number(type)].toInt();
        y = json["y-"+QString::number(type)].toInt();
        score = json["score-"+QString::number(type)].toInt();
    }
    else{
        qDebug()<<"Player::json 解析错误"<<Qt::endl;
    }


}

//保存玩家状态至json对象
void Player::save(QJsonObject &json) const
{
    json["x-"+QString::number(type)] = x;
    json["y-"+QString::number(type)] = y;
    json["score-"+QString::number(type)] = score;
}

//判断方块是否需要激活
//传入地图坐标，根据情况判断方块需要激活，若能，进一步调用判断函数判断是否能够消除
void Player::activateBlock(int x, int y, GameMap &game)
{
    if(activePoint.size()==0)
    {
        activePoint.push_back(ActivePoint(x,y,game.map[x][y].type));
    }
    else{
        ActivePoint temp = activePoint[0];
        //两次激活同一方块则取消激活
        if(temp.x==x&&temp.y==y)activePoint.pop_back();
        //激活不同类方块取消前一个激活现在的
        else if(temp.type!=game.map[x][y].type){
            activePoint.pop_back();
            activePoint.push_back(ActivePoint(x,y,game.map[x][y].type));
        }
        //激活同类方块开始判定是否能够连接
        else{
            int inflectionNumber = 0;
            ActivePoint from(x,y),inflection1, inflection2;
            if(checkEliminated(from,temp,inflectionNumber,game,&inflection1,&inflection2)){
                eliminatePair.push_back(from);
                eliminatePair.push_back(temp);
                switch (inflectionNumber) {
                case 0:
                    break;
                case 1:
                    eliminatePair.push_back(inflection1);
                    break;
                case 2:
                    eliminatePair.push_back(inflection1);
                    eliminatePair.push_back(inflection2);
                    break;
                }
                game.pairNumber--;
                qDebug()<<"remain:"<<game.pairNumber<<Qt::endl;
                score+=scorePerPair;
                emit refreshScore();
                if(!checkRemain(game)){
                    emit gameOver();
                }
            }
            activePoint.pop_back();
        }

    }
}

//判断地图中两点是否能直接连接
//传入两点坐标，返回表示是否能连接的布尔值
bool Player::isDirectlyLinkable(int x1, int y1, int x2, int y2, GameMap &game)
{
    if(x1 == x2){
        if(y1>y2)std::swap(y1,y2);
        for(y1+=1;y1<y2;++y1)
            if(game.map[x1][y1].type)
                return false;
    }
    else if(y1 == y2){
        if(x1>x2)std::swap(x1,x2);
        for(x1+=1;x1<x2;++x1)
            if(game.map[x1][y1].type)
                return false;
    }
    else return false;
    return true;
}

//寻找能连接到地图两点的中心点
//传入两点坐标，返回能否找到这样的点，若能，更新x2 y2的值为中间点坐标
bool Player::findInteractPoint(const int &x1, const int &y1, int &x2, int &y2, GameMap &game)
{
    if(!game.map[x1][y2].type){
        if(isDirectlyLinkable(x1,y1,x1,y2,game) &&
                isDirectlyLinkable(x2,y2,x1,y2,game)){
            x2=x1;
            return true;
        }
    }
    if(!game.map[x2][y1].type){
        if(isDirectlyLinkable(x1,y1,x2,y1,game)&&
                isDirectlyLinkable(x2,y2,x2,y1,game)){
            y2=y1;
            return true;
        }
    }
    return false;
}

//获取贴图方块的中心点坐标
//传入元素坐标，返回其贴图中心点在地图中的坐标
QPoint Player::getCenterPoint(ActivePoint &point)
{
    int x = point.x;
    int y = point.y;
    return QPoint(x*iconWidth+iconWidth/2,y*iconWidth+iconWidth/2);
}

//判断两点是否能消去
//传入两点坐标from to，记录折弯次数的inflectionNum和记录折弯中间点的inflection1 inflection2
//返回是否能消除的布尔值，若能消除，更新inflectionNum和inflection1、inflection2
bool Player::checkEliminated(ActivePoint from, ActivePoint to, int &inflectionNum, GameMap &game, ActivePoint *inflection1, ActivePoint *inflection2)
{
    int x1 = from.x;
    int y1 = from.y;
    int x2 = to.x;
    int y2 = to.y;
    //一、检查两点能否以直线连接
    if(isDirectlyLinkable(x1,y1,x2,y2,game)){
        inflectionNum=0;
        return true;
    }
    //二、检查两点能否以一个拐点折线连接
    if(findInteractPoint(x1,y1,x2,y2,game)){
        inflectionNum=1;
        inflection1->x = x2;
        inflection1->y = y2;
        return true;
    }
    //三、检查两点能否以两个拐点折线连接
    //情况一，在起始点的x方向找到了中间点
    for(int i=0;i<game.width;i++){
        if(!game.map[i][y1].type && isDirectlyLinkable(i,y1,x1,y1,game) &&
                findInteractPoint(i,y1,x2,y2,game)){
            inflectionNum=2;
            inflection1->x = i;
            inflection1->y = y1;
            inflection2->x = x2;
            inflection2->y = y2;
            return true;
        }
    }
    //情况二，在起始点的y方向找到中间点
    for(int i=0;i<game.height;i++){
        if(!game.map[x1][i].type && isDirectlyLinkable(x1,i,x1,y1,game) &&
                findInteractPoint(x1,i,x2,y2,game)){
            inflectionNum=2;
            inflection1->x = x1;
            inflection1->y = i;
            inflection2->x = x2;
            inflection2->y = y2;
            return true;
        }
    }
    return false;
}

//判断地图中是否还存在可消去块
//传入GameMap对象，返回是否存在可消去块的布尔值
bool Player::checkRemain(GameMap &game)
{
    //全部消除
    if(game.pairNumber==0)return false;
    for(int i=0;i<game.width;i++){
        for(int j=0;j<game.height;j++){
            if(game.map[i][j].type){
                int x,y;
                for(x=i;x<game.width;x++){
                    if(x==i)y=j+1;
                    else y=0;
                    for(;y<game.height;y++){
                        if(game.map[x][y].type==game.map[i][j].type){
                            ActivePoint from(i,j),to(x,y);
                            int inflectionNumber=0;
                            ActivePoint inflection1,inflection2;
                            if(checkEliminated(from,to,inflectionNumber,game,&inflection1,&inflection2)){
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

//更新提示块数组
//传入传入GameMap对象，更新类的数据成员HintPair
void Player::refreshHint(GameMap &game)
{
    game.hintPair.clear();
    for(int i=0;i<game.width;i++){
        for(int j=0;j<game.height;j++){
            if(game.map[i][j].type){
                int x,y;
                for(x=i;x<game.width;x++){
                    if(x==i)y=j+1;
                    else y=0;
                    for(;y<game.height;y++){
                        if(game.map[x][y].type==game.map[i][j].type){
                            ActivePoint from(i,j),to(x,y);
                            int inflectionNumber=0;
                            ActivePoint inflection1,inflection2;
                            if(checkEliminated(from,to,inflectionNumber,game,&inflection1,&inflection2)){
                                //找到一对可连接的便跳出循环
                                game.hintPair.push_back(GameMap::ActivePoint(from.x,from.y,from.type));
                                game.hintPair.push_back(GameMap::ActivePoint(to.x,to.y,to.type));
                                return;
                            }
                        }
                    }
                }
            }
        }
    }
}
