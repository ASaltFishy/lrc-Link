#include "qlinktest.h"

//测试直接连接的情况
void QlinkTest::direct()
{
    QFETCH(Player::ActivePoint, point1);
    QFETCH(Player::ActivePoint, point2);
    QFETCH(bool, result);

    int tempNum;
    Player::ActivePoint inflec1,inflec2;
    map->map[0][0].type = 1;
    map->map[3][0].type = 1;
    map->map[0][3].type = 1;
    QCOMPARE(p->checkEliminated(point1,point2,tempNum,*map,&inflec1,&inflec2), result);
}

void QlinkTest::direct_data()
{
    QTest::addColumn<Player::ActivePoint>("point1");
    QTest::addColumn<Player::ActivePoint>("point2");
    QTest::addColumn<bool>("result");

     QTest::newRow("direct1") << Player::ActivePoint(0,0,1)<<Player::ActivePoint(0,3,1)<<true;
     QTest::newRow("direct2") <<Player::ActivePoint(0,3,1) << Player::ActivePoint(0,0,1)<<true;
     QTest::newRow("direct3") << Player::ActivePoint(0,0,1)<<Player::ActivePoint(3,0,1)<<true;
     QTest::newRow("direct4") << Player::ActivePoint(3,0,1)<<Player::ActivePoint(0,0,1)<<true;
}

//测试一次转折可以连接的情况
void QlinkTest::oneInflection()
{
    QFETCH(Player::ActivePoint, point1);
    QFETCH(Player::ActivePoint, point2);
    QFETCH(bool, result);

    int tempNum;
    Player::ActivePoint inflec1,inflec2;
    map->clearMap();
    map->map[0][0].type = 1;
    map->map[3][3].type = 1;
    map->map[4][0].type = 1;
    map->map[7][3].type = 1;
    map->map[7][0].type = 2;
    map->map[0][4].type = 1;
    map->map[2][4].type = 2;
    map->map[3][7].type = 1;
    map->map[4][4].type = 1;
    map->map[7][7].type = 1;
    map->map[7][6].type = 2;
    QCOMPARE(p->checkEliminated(point1,point2,tempNum,*map,&inflec1,&inflec2), result);
}

void QlinkTest::oneInflection_data()
{
    QTest::addColumn<Player::ActivePoint>("point1");
    QTest::addColumn<Player::ActivePoint>("point2");
    QTest::addColumn<bool>("result");

     QTest::newRow("oneInflection1") << Player::ActivePoint(0,0,1)<<Player::ActivePoint(3,3,1)<<true;
     QTest::newRow("oneInflection2") <<Player::ActivePoint(3,3,1) << Player::ActivePoint(0,0,1)<<true;
     QTest::newRow("oneInflection3") << Player::ActivePoint(4,0,1)<<Player::ActivePoint(7,3,1)<<true;
     QTest::newRow("oneInflection4") << Player::ActivePoint(7,3,1)<<Player::ActivePoint(4,0,1)<<true;
     QTest::newRow("oneInflection5") << Player::ActivePoint(0,4,1)<<Player::ActivePoint(3,7,1)<<true;
     QTest::newRow("oneInflection6") << Player::ActivePoint(3,7,1)<<Player::ActivePoint(0,4,1)<<true;
     QTest::newRow("oneInflection7") << Player::ActivePoint(4,4,1)<<Player::ActivePoint(7,7,1)<<true;
     QTest::newRow("oneInflection8") << Player::ActivePoint(7,7,1)<<Player::ActivePoint(4,4,1)<<true;

}

//测试两次转折可以连接的情况
void QlinkTest::twoInflection()
{
    QFETCH(Player::ActivePoint, point1);
    QFETCH(Player::ActivePoint, point2);
    QFETCH(bool, result);

    int tempNum;
    Player::ActivePoint inflec1,inflec2;
    map->clearMap();
    map->map[0][0].type = 1;
    map->map[0][1].type = 2;
    map->map[0][2].type = 2;
    map->map[0][3].type = 2;
    map->map[3][0].type = 2;
    map->map[2][1].type = 2;
    map->map[3][3].type = 1;

    map->map[4][0].type = 1;
    map->map[4][1].type = 2;
    map->map[4][2].type = 2;
    map->map[4][3].type = 1;

    map->map[0][4].type = 1;
    map->map[0][6].type = 2;
    map->map[0][7].type = 2;
    map->map[1][4].type = 2;
    map->map[2][4].type = 2;
    map->map[3][4].type = 2;
    map->map[3][7].type = 1;

    map->map[4][4].type = 1;
    map->map[5][4].type = 2;
    map->map[6][4].type = 2;
    map->map[7][4].type = 1;
    QCOMPARE(p->checkEliminated(point1,point2,tempNum,*map,&inflec1,&inflec2), result);
}

void QlinkTest::twoInflection_data()
{
    QTest::addColumn<Player::ActivePoint>("point1");
    QTest::addColumn<Player::ActivePoint>("point2");
    QTest::addColumn<bool>("result");

     QTest::newRow("twoInflection1") << Player::ActivePoint(0,0,1)<<Player::ActivePoint(3,3,1)<<true;
     QTest::newRow("twoInflection2") <<Player::ActivePoint(3,3,1) << Player::ActivePoint(0,0,1)<<true;
     QTest::newRow("twoInflection3") << Player::ActivePoint(4,0,1)<<Player::ActivePoint(4,3,1)<<true;
     QTest::newRow("twoInflection4") << Player::ActivePoint(4,3,1)<<Player::ActivePoint(4,0,1)<<true;
     QTest::newRow("twoInflection5") << Player::ActivePoint(0,4,1)<<Player::ActivePoint(3,7,1)<<true;
     QTest::newRow("twoInflection6") << Player::ActivePoint(3,7,1)<<Player::ActivePoint(0,4,1)<<true;
     QTest::newRow("twoInflection7") << Player::ActivePoint(4,4,1)<<Player::ActivePoint(7,4,1)<<true;
     QTest::newRow("twoInflection8") << Player::ActivePoint(7,4,1)<<Player::ActivePoint(4,4,1)<<true;
}

//测试不能消去的情况
void QlinkTest::cannotEliminate()
{
    QFETCH(Player::ActivePoint, point1);
    QFETCH(Player::ActivePoint, point2);
    QFETCH(bool, result);

    int tempNum;
    Player::ActivePoint inflec1,inflec2;
    map->clearMap();
    map->map[0][0].type = 1;
    map->map[0][1].type = 2;
    map->map[0][3].type = 2;
    map->map[1][3].type = 2;
    map->map[2][0].type = 2;
    map->map[3][0].type = 2;
    map->map[3][2].type = 2;
    map->map[3][3].type = 1;

    map->map[4][0].type = 1;
    map->map[4][2].type = 2;
    map->map[4][3].type = 2;
    map->map[5][0].type = 2;
    map->map[6][3].type = 2;
    map->map[7][0].type = 2;
    map->map[7][1].type = 2;
    map->map[7][3].type = 1;
    QCOMPARE(p->checkEliminated(point1,point2,tempNum,*map,&inflec1,&inflec2), result);
}

void QlinkTest::cannotEliminate_data()
{
    QTest::addColumn<Player::ActivePoint>("point1");
    QTest::addColumn<Player::ActivePoint>("point2");
    QTest::addColumn<bool>("result");

     QTest::newRow("noEliminate1") << Player::ActivePoint(0,0,1)<<Player::ActivePoint(3,3,1)<<false;
     QTest::newRow("noEliminate2") <<Player::ActivePoint(3,3,1) << Player::ActivePoint(0,0,1)<<false;
     QTest::newRow("noEliminate3") << Player::ActivePoint(4,0,1)<<Player::ActivePoint(7,3,1)<<false;
     QTest::newRow("noEliminate4") << Player::ActivePoint(7,3,1)<<Player::ActivePoint(4,0,1)<<false;
}

//初始化测试环境，生成8*8地图和新玩家
void QlinkTest::initTestCase()
{
    map = new GameMap(8,8,1);
    p = new Player;
}

//释放动态分配的内存
void QlinkTest::cleanupTestCase()
{
    delete map;
    delete p;
}


QTEST_MAIN(QlinkTest)
