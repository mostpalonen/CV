#include <QtTest>
#include "../Game/managers/gameeventhandler.h"
#include "../Game/managers/gameobjectmanager.h"
#include "../Game/managers/resourcemanager.h"
#include "../Game/managers/soundengine.h"
#include "../Game/bullets/basicbullet.h"
#include "../Game/bullets/bullet.h"
#include "../Game/bullets/moneybullet.h"
#include "../Game/bullets/secondary.h"
#include "../Game/bullets/toxicbullet.h"
#include "../Game/enemies/basicenemy.h"
#include "../Game/enemies/enemybase.h"
#include "../Game/enemies/feministi.h"
#include "../Game/enemies/humanisti.h"
#include "../Game/enemies/raitsikka.h"
#include "../Game/enemies/tuniboss.h"
#include "../Game/tiles/buildingspace.h"
#include "../Game/towers/duo.h"
#include "../Game/towers/headquarter.h"
#include "../Game/towers/matriisit.h"
#include "../Game/towers/mikontalo.h"
#include "../Game/towers/towerbase.h"
#include "../Game/towers/ttorni.h"
#include "../Game/towers/wainola.h"
#include "../Game/mainwindow.h"
#include "../Game/dialoginfo.h"
#include "../Game/dialogstart.h "
#include "../Game/player.h"
#include "../Course/CourseLib/buildings/buildingbase.h"
#include "../Course/CourseLib/buildings/farm.h"
#include "../Course/CourseLib/buildings/headquarters.h"
#include "../Course/CourseLib/buildings/outpost.h"
#include "../Course/CourseLib/exceptions/baseexception.h"
#include "../Course/CourseLib/exceptions/keyerror.h"
#include "../Course/CourseLib/exceptions/ownerconflict.h"
#include "../Course/CourseLib/exceptions/invalidpointer.h"
#include "../Course/CourseLib/exceptions/illegalaction.h"
#include "../Course/CourseLib/exceptions/notenoughspace.h"
#include "../Course/CourseLib/graphics/simplemapitem.h"
#include "../Course/CourseLib/graphics/simplegamescene.h"
#include "../Course/CourseLib/interfaces/iobjectmanager.h"
#include "../Course/CourseLib/interfaces/igameeventhandler.h"
#include "../Course/CourseLib/tiles/grassland.h"
#include "../Course/CourseLib/tiles/forest.h"
#include "../Course/CourseLib/tiles/tilebase.h"
#include "../Course/CourseLib/workers/basicworker.h"
#include "../Course/CourseLib/workers/workerbase.h"
#include "../Course/CourseLib/core/basicresources.h"
#include "../Course/CourseLib/core/placeablegameobject.h"
#include "../Course/CourseLib/core/worldgenerator.h"
#include "../Course/CourseLib/core/coordinate.h"
#include "../Course/CourseLib/core/playerbase.h"
#include "../Course/CourseLib/core/gameobject.h"
#include "../Course/CourseLib/core/resourcemaps.h"


class UnitTest : public QObject
{
    Q_OBJECT

public:
    UnitTest();
    ~UnitTest();

private slots:
    void GEHtest_checkGoal();
    void GOMtest_addTower();

    void GEHtest_checkGoal_data();
    void GOMtest_addTower_data();

};

UnitTest::UnitTest(){}

UnitTest::~UnitTest(){}


void UnitTest::GEHtest_checkGoal()
{
    // TEST TO CHECK THAT THE CALLED WAVENUMBER IS OK
    QFETCH(int, input);
    QFETCH(int, output);

    QVERIFY2(output==1, "Errorenous wave number");
}

void UnitTest::GEHtest_checkGoal_data()
{
    QTest::addColumn<int>("input");
    QTest::addColumn<int>("output");

    QTest::newRow("1 round")    << 1    << 1;
    QTest::newRow("n roundi")   << 12   << 0;
    QTest::newRow("fatal")      << 0    << 0;
    QTest::newRow("fatal2")     << -2   << 0;

}

void UnitTest::GOMtest_addTower()
{
    QFETCH(int, input);
    QFETCH(bool, output);

    QVERIFY2(output == true, "Errorenous class call");
}

void UnitTest::GOMtest_addTower_data()
{
    QTest::addColumn<int>("input");
    QTest::addColumn<bool>("output");

    QTest::newRow("rakenna waiski")     << 1    << true;
    QTest::newRow("virhe call")         << 7    << false;
    QTest::newRow("virhe call")         << -2   << false;
}

QTEST_APPLESS_MAIN(UnitTest)

#include "tst_unittest.moc"
