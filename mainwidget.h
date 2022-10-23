#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QDebug>
#include <QString>
#include <QKeyEvent>
#include <QTimer>
#include <QMessageBox>
#include <QPushButton>
#include <QFileDialog>
#include <QLabel>
#include <QLayout>
#include <QJsonObject>
#include <QJsonDocument>
#include <vector>
#include "player.h"
#include "gamemap.h"
#include "timer.h"

using namespace std;

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(int _height = 10,int _width = 10,bool _singleMode = true,QWidget *parent = nullptr);
    explicit MainWidget (const QJsonObject &json,QWidget *parent = nullptr);
    ~MainWidget();
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    //load and save
    void load(const QJsonObject &json);
    void save(QJsonObject &json);


private:
    //ui界面原件
    Ui::MainWidget *ui=nullptr;
    QHBoxLayout mainLayout;
    QLabel timeHint;
    QLabel timer;
    QLabel p1Hint;
    QLabel p1Score;
    QLabel *p2Hint;
    QLabel *p2Score;
    QPushButton *pause;
    bool isPause = false;
    void setWindow();

    //地图宽度和高度
    int height;
    int width;
    //是否单人模式
    bool singleMode;

    Player *player1 = nullptr,*player2 = nullptr;

    GameMap *map = nullptr;

    QPainter *painter = nullptr;
    //用于游戏计时的类
    Timer *gameTime;
    //定时提供超时事件的QTimer类
    QTimer *innerTimer;
    //存档用
    bool saveGame();


public slots:
    void gameOverSlot();
    void updateTimer();
    void addOneSecond();
    void gameTimeOutSlot();
    void refreshScoreSlot();
    void pauseSlot();
signals:
    void showStart();
    void gameTimeOut();

};

#endif // MAINWIDGET_H
