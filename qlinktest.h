#ifndef QLINKTEST_H
#define QLINKTEST_H
#include <QtTest/QtTest>
#include "gamemap.h"
#include "player.h"


class QlinkTest:public QObject
{
    Q_OBJECT
private:
    GameMap *map;
    Player *p;
private slots:
    void direct();
    void direct_data();
    void oneInflection();
    void oneInflection_data();
    void twoInflection();
    void twoInflection_data();
    void cannotEliminate();
    void cannotEliminate_data();
    void initTestCase();
    void cleanupTestCase();

};

#endif // QLINKTEST_H
