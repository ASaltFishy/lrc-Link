#include "gamemap.h"
#include <QJsonObject>
#include <QJsonArray>

//传入地图长宽的构造函数，调用init随机生成地图
GameMap::GameMap(int _height,int _width){
    width = _width;
    height = _height;
    initMap();
    connect(hintTimer,SIGNAL(timeout()),this,SLOT(endHint()));
}

//传入地图长宽的构造函数，不随机生成地图，可自己制定，测试用
GameMap::GameMap(int _height, int _width, int _forTest)
{
    Q_UNUSED(_forTest);
    width = _width;
    height = _height;
    map = new Point*[width];
    for(int i=0;i<width;i++){
        map[i] = new Point[height];
    }
}

//传入json变量加载地图，导入游戏时调用
GameMap::GameMap(const QJsonObject &json)
{
    load(json);
    connect(hintTimer,SIGNAL(timeout()),this,SLOT(endHint()));
    initImage();
}

//释放动态内存的析构函数
GameMap::~GameMap()
{
    if(hintTimer)
    delete hintTimer;
    for(int i=0;i<height;i++){
        delete map[i];
    }
    delete map;
}

//传入painter指针，绘制地图方块和提示方框并返回
void GameMap::paintMap(QPainter* painter){
    //绘制贴图
    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            if(map[i][j].type!=0){
                QImage img(imgURL[map[i][j].type]);
                QRect rect(i*iconWidth,j*iconWidth,iconWidth,iconWidth);
                painter->drawImage(rect,img);
            }
        }
    }
    //绘制提示
    if(hint){
        QPen blackpen;
        blackpen.setColor(Qt::black);
        blackpen.setWidth(5);
        painter->setPen(blackpen);
        ActivePoint a1 = hintPair[0];
        ActivePoint a2 = hintPair[1];
        painter->drawRect(a1.x*iconWidth,a1.y*iconWidth,iconWidth,iconWidth);
        painter->drawRect(a2.x*iconWidth,a2.y*iconWidth,iconWidth,iconWidth);
    }
}


//随机生成地图和道具并返回
void GameMap::initMap(){

    //构造地图二维数组
    map = new Point*[width];
    for(int i=0;i<width;i++){
        map[i] = new Point[height];
    }
    hintTimer = new QTimer(this);

    //随机生成地图，存在可供移动的空位置
    QVector<int> random;
    //1、2号位置不放水果给用户留出初始位置
    for(int i=1;i<height*width;i++){
        random.push_back(i);
    }
    std::random_shuffle(random.begin(),random.end());
    int groupNumber = height*width/20-1;
    pairNumber = groupNumber*10;

    //随机生成箱子
    for(int i=0;i<groupNumber*20;i++){
        int x = random[i]/height;
        int y = random[i]%height;
        int type = i%20/2+1;
//        qDebug()<<x<<" "<<y<<" "<<type<<endl;
        map[x][y].type = type;
    }

    //随机生成道具
    int propsType[4]={11,12,13};
    for(int i=0;i<4;i++){
        int x = random[i+groupNumber*20]/height;
        int y = random[i+groupNumber*20]%height;
//        qDebug()<<x<<" "<<y<<" "<<propsType[i]<<endl;
        map[x][y].type = propsType[i];
    }

    initImage();
}

//地图的二维数组转化为一维
void GameMap::mapToVector()
{
    tempMap.clear();
    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            tempMap.push_back(map[i][j]);
        }
    }
}

//存有地图数据的一维数组转化为二维
void GameMap::vectorToMap()
{
    if(tempMap.empty()){
        qDebug()<<"重新加载出现错误"<<Qt::endl;
    }
    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            map[i][j] = tempMap[i*height+j];
        }
    }
}

//保存地图贴图资源
void GameMap::initImage()
{
    //将图片路径保存至imgURL数组中
    imgURL.push_back("");
    imgURL.push_back(":/imag/3.png");
    imgURL.push_back(":/imag/4.png");
    imgURL.push_back(":/imag/5.png");
    imgURL.push_back(":/imag/6.png");
    imgURL.push_back(":/imag/7.png");
    imgURL.push_back(":/imag/8.png");
    imgURL.push_back(":/imag/9.png");
    imgURL.push_back(":/imag/10.png");
    imgURL.push_back(":/imag/11.png");
    imgURL.push_back(":/imag/12.png");
    imgURL.push_back(":/imag/addone.png");
    imgURL.push_back(":/imag/shuffle.png");
    imgURL.push_back(":/imag/hint.png");
    imgURL.push_back(":/imag/flash.png");

}

//实现+1道具，发送addOneSecond信号
void GameMap::addOneProp()
{
    emit addOneSecond();
}

//实现重排道具
void GameMap::shuffleProp()
{
    mapToVector();
    std::random_shuffle(tempMap.begin(),tempMap.end());
    vectorToMap();

}

//实现提示道具
void GameMap::hintProp()
{
    //10秒后发送信号关闭hint提示
    hintTimer->start(1000);
    hint = true;
}


//传入QJsonObject对象，实现读档加载地图
void GameMap::load(const QJsonObject &json)
{
    width = json["width"].toInt();
    height = json["height"].toInt();
    map = new Point*[width];
    for(int i=0;i<width;i++){
        map[i] = new Point[height];
    }
    hintTimer = new QTimer(this);
    QJsonArray mapArray = json["map"].toArray();
    tempMap.clear();
    for(int i=0;i<mapArray.size();i++){
        tempMap.push_back(Point(mapArray[i].toInt()));
    }
    vectorToMap();

    pairNumber = json["pairNumber"].toInt();
    hint = json["hint"].toBool();
    hintTime = json["hintTime"].toInt();
    //继续hint计时
    if(hint){
        hintProp();
    }
}

//实现保存地图数据到json
void GameMap::save(QJsonObject &json)
{
    mapToVector();
    QJsonArray mapArray;
    for(int i=0;i<width*height;i++){
        QJsonValue tempVal = tempMap[i].type;
        mapArray.append(tempVal);
    }
    json["map"] = mapArray;
    json["pairNumber"] = pairNumber;
    json["hint"] = hint;
    json["hintTime"] = hintTime;

}

//暂停暗示计时器计时
void GameMap::pauseHint()
{
    hintTimer->stop();
}

//清空地图（测试用）
void GameMap::clearMap()
{
    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            map[i][j].type = 0;
        }
    }
}

//结束hint道具效果
void GameMap::endHint()
{
    qDebug()<<hintTime<<Qt::endl;
    if(hintTime==0){
        hint = false;
        hintTimer->stop();
        hintPair.clear();
    }
    else hintTime--;
}




