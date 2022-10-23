#include "mainwidget.h"
#include "ui_mainwidget.h"

#define iconWidth 60
#define dx 90
#define dy 90
#define defaultTime 60

//构造函数，传入用户选择的地图宽高和模式，初始化玩家、地图
MainWidget::MainWidget(int _height,int _width,bool _singleMode,QWidget *parent) :
    QWidget(parent),ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    width = _width;
    height = _height;
    singleMode = _singleMode;

    //设置窗口布局
    setWindow();
    this->grabKeyboard();
    painter = new QPainter();
    map = new GameMap(height,width);
    gameTime = new Timer(defaultTime);
    innerTimer = new QTimer(this);

    player1 = new Player(0,0,1);
    //根据模式选择实例化游戏玩家
    if(!singleMode){
        player2 = new Player(1,0,2);
        connect(player2,SIGNAL(refreshScore()),this,SLOT(refreshScoreSlot()));
        connect(player2,SIGNAL(gameOver()),this,SLOT(gameOverSlot()));
    }
    //连接信号与槽
    connect(player1,SIGNAL(gameOver()),this,SLOT(gameOverSlot()));
    connect(map,SIGNAL(addOneSecond()),this,SLOT(addOneSecond()));
    connect(this,SIGNAL(gameTimeOut()),this,SLOT(gameTimeOutSlot()));
    connect(innerTimer,SIGNAL(timeout()),this,SLOT(updateTimer()));
    connect(player1,SIGNAL(refreshScore()),this,SLOT(refreshScoreSlot()));
    connect(pause,SIGNAL(clicked()),this,SLOT(pauseSlot()));
    innerTimer->start(1000);


}

//构造函数，传入QJsonObject加载还原游戏状态
MainWidget::MainWidget(const QJsonObject &json,QWidget *parent) :
    QWidget(parent),ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    load(json);

    this->grabKeyboard();
    painter = new QPainter();
    map = new GameMap(json);
    gameTime = new Timer(json);
    innerTimer = new QTimer(this);
    //设置窗口布局
    setWindow();
    this->grabKeyboard();

    player1 = new Player(json,1);
    player1->refreshHint(*map);
    //根据模式选择实例化游戏玩家
    if(!singleMode){
        player2 = new Player(json,2);
        connect(player2,SIGNAL(refreshScore()),this,SLOT(refreshScoreSlot()));
        connect(player2,SIGNAL(gameOver()),this,SLOT(gameOverSlot()));
        emit(player2->refreshScore());
    }
    //连接信号与槽
    connect(player1,SIGNAL(gameOver()),this,SLOT(gameOverSlot()));
    connect(map,SIGNAL(addOneSecond()),this,SLOT(addOneSecond()));
    connect(this,SIGNAL(gameTimeOut()),this,SLOT(gameTimeOutSlot()));
    connect(innerTimer,SIGNAL(timeout()),this,SLOT(updateTimer()));
    connect(player1,SIGNAL(refreshScore()),this,SLOT(refreshScoreSlot()));
    connect(pause,SIGNAL(clicked()),this,SLOT(pauseSlot()));
    innerTimer->start(1000);
    emit(player1->refreshScore());

}

//析构函数，释放动态分配资源
MainWidget::~MainWidget()
{
    delete ui;
    delete painter;
    delete map;
    delete innerTimer;
    delete pause;
    if(singleMode)delete player1;
    else {
        delete player1;
        delete player2;
        delete p2Hint;
        delete p2Score;
    }
}

//绘制事件，分别调用GameMap和Player类的绘制事件
void MainWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    painter->begin(this);
    //设置红线用于绘制激发态的矩形框
    //设置绿线表示连接成功后的路径
    //设置黑线表示地图边界
    QPen redPen,greenPen,blackPen;
    QTransform transform;
    transform.translate(dx,dy);
    painter->setTransform(transform);
    redPen.setColor(Qt::red);
    redPen.setWidth(8);
    greenPen.setColor(Qt::darkGreen);
    greenPen.setWidth(8);
    blackPen.setColor(Qt::black);

    // 绘制贴图
    map->paintMap(painter);
    player1->paintActivate(painter);
    player1->drawLine(painter,*map);
    player1->paintPlayer(painter);
    //绘制角色贴图
    if(!singleMode){
        player2->paintActivate(painter);
        player2->drawLine(painter,*map);
        player2->paintPlayer(painter);
    }
    //绘制地图边框
    painter->setPen(blackPen);
    painter->drawRect(0,0,iconWidth*width,iconWidth*height);
    painter->end();
}

//按键事件
void MainWidget::keyPressEvent(QKeyEvent *event)
{
    if(!isPause){
        if(singleMode){
            player1->keyPress(event,*map);
        }
        else{
            player1->keyPress(event,*map);
            player2->keyPress(event,*map);
        }
        update();
    }
}

//加载函数，传入QJsonObject对象加载宽高和模式
void MainWidget::load(const QJsonObject &json)
{
    width = json["width"].toInt();
    height = json["height"].toInt();
    singleMode = json["singleMode"].toBool();
}

//保存宽高和模式到json对象
void MainWidget::save(QJsonObject &json)
{
    json["width"] = width;
    json["height"] = height;
    json["singleMode"] = singleMode;
}

//设置窗口的各个元素
void MainWidget::setWindow()
{
    setWindowTitle("水果连连看");
    setFixedSize((width)*iconWidth+2*dy,(height)*iconWidth+2*dx);

    //倒计时
    timeHint.setText("游戏倒计时：");
    QFont ft;
    ft.setPointSize(14);
    timeHint.setFont(ft);
    timer.setFont(ft);
    timer.setText(QString::number(defaultTime));
    timer.setAlignment(Qt::AlignLeft);

    //设置分数面板
    mainLayout.addWidget(&timeHint);
    mainLayout.addWidget(&timer);
    mainLayout.setAlignment(Qt::AlignTop);
    p1Hint.setText("P1分数:");
    p1Hint.setFont(ft);
    p1Score.setText("0");
    p1Score.setAlignment(Qt::AlignLeft);
    p1Score.setFont(ft);
    mainLayout.addWidget(&p1Hint);
    mainLayout.addWidget(&p1Score);


    if(!singleMode){
        p2Hint = new QLabel();
        p2Hint->setText("P2分数:");
        p2Hint->setFont(ft);
        p2Score = new QLabel();
        p2Score->setText("0");
        p2Score->setAlignment(Qt::AlignLeft);
        p2Score->setFont(ft);
        mainLayout.addWidget(p2Hint);
        mainLayout.addWidget(p2Score);
    }

    //设置暂停按钮
    pause = new QPushButton("暂停");
    ft.setPointSize(12);
    pause->setFont(ft);
    mainLayout.addWidget(pause);

    //设置当前Widget的Layout
    this->setLayout(&mainLayout);
}

//保存游戏全局状态
bool MainWidget::saveGame()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save");
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, "Warning", "Failed to save file: " + file.errorString());
        return false;
    }
    //将当前状态以json格式的二进制编码保存
    QJsonObject saveObject;
    save(saveObject);
    map->save(saveObject);
    gameTime->save(saveObject);
    player1->save(saveObject);
    if(!singleMode)player2->save(saveObject);
    QJsonDocument saveDoc(saveObject);
    file.write(saveDoc.toJson());
    return true;
}

//更新计时器显示，timeout信号的槽函数
void MainWidget::updateTimer()
{
    int temp = gameTime->getTime();
    timer.setText(QString::number(temp));
    if(temp==0){
        emit gameTimeOut();
    }
}

//窗口相应+1信号的槽函数
void MainWidget::addOneSecond()
{
    int now = gameTime->addOne();
    timer.setText(QString::number(now));
}

//游戏时间结束信号的槽函数
void MainWidget::gameTimeOutSlot()
{
    QMessageBox msgBox(this);
    msgBox.grabKeyboard();
    if(singleMode){
        msgBox.setText("时间到！游戏结束~");
    }else{
        if(player1->getScore()>player2->getScore())msgBox.setText("时间到，游戏结束，P1胜利！");
        else if(player1->getScore()==player2->getScore())msgBox.setText("时间到，游戏结束，打成平手！");
        else msgBox.setText("时间到，游戏结束，P2胜利！");
    }
    msgBox.exec();
    if(msgBox.clickedButton()){
        this->close();
        emit showStart();
    }
}

//玩家分数有所变化的槽函数
void MainWidget::refreshScoreSlot()
{
    int p1 = player1->getScore();
    p1Score.setText(QString::number(p1));
    if(!singleMode){
        int p2 = player2->getScore();
        p2Score->setText(QString::number(p2));
    }

}

//暂停信号的槽函数
void MainWidget::pauseSlot()
{
    isPause = true;
    QMessageBox msgBox(this);
    msgBox.setText("游戏暂停");
    QPushButton *continueButton = msgBox.addButton(tr("继续"),QMessageBox::ActionRole);
    QPushButton *saveButton = msgBox.addButton(tr("保存并退出"),QMessageBox::ActionRole);
    QPushButton *quitButton = msgBox.addButton(tr("退出游戏"),QMessageBox::ActionRole);
    msgBox.setDefaultButton(continueButton);
    //暂停时停止计时
    innerTimer->stop();
    map->pauseHint();
    msgBox.exec();
    if(msgBox.clickedButton()==quitButton){
        this->close();
        emit showStart();
    }
    else if(msgBox.clickedButton()==saveButton){
        if(saveGame()){
            this->close();
            emit showStart();
        }
        else{
            innerTimer->start();
            isPause = false;
        }
    }
    else{
        innerTimer->start();
        isPause = false;
    }

}

//无可连接对游戏结束的槽函数
void MainWidget::gameOverSlot()
{
    qDebug()<<"无可连接水果对，游戏结束！"<<Qt::endl;
    innerTimer->stop();
    QMessageBox msgBox(this);
    msgBox.grabKeyboard();
    if(singleMode){
        msgBox.setText("没有可连接的水果对了！游戏结束~");
    }else{
        if(player1->getScore()>player2->getScore())msgBox.setText("游戏结束，P1胜利！");
        else if(player1->getScore()==player2->getScore())msgBox.setText("游戏结束，打成平手！");
        else msgBox.setText("游戏结束，P2胜利！");
    }

    msgBox.exec();
    if(msgBox.clickedButton()){
        this->close();
        emit showStart();
    }

}


