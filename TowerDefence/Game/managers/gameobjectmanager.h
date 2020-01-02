#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H

#include <QObject>
#include <QGraphicsScene>
#include <QList>
#include "../Game/tiles/buildingspace.h"
#include "../Game/towers/towerbase.h"
#include "../Game/towers/headquarter.h"
#include "../Game/towers/wainola.h"
#include "../Game/towers/mikontalo.h"
#include "../Game/towers/matriisit.h"
#include "../Game/towers/ttorni.h"
#include "../Game/towers/duo.h"
#include "../Game/mainwindow.h"

class ObjectManager: public QObject
{
    Q_OBJECT
public:
    ObjectManager(class MainWindow* parent = nullptr, QGraphicsScene* scene = nullptr);

public slots:
    void addSpace(int x, int y);
    void addTower(QPointF pos);
    void setBuildMode(int building);
    int getBuildMode();
    void gameOver();
    void resetSpaceStates();
    void addRes();
    void roundStatus(bool set);
    bool checkDuos();
    double getHqHealth();
    void setHqHp(int amount);

signals:
    void passCost(int money, int concrete, int mead, int credits);

private:
    QList<class BuildingSpace *> spaces_;
    QList<class TowerBase*> towers_;
    QList<class QTimer*> timers_;
    class headquarter* hq_ = nullptr;
    QGraphicsScene* scene_ = nullptr;
    class MainWindow * parent_ = nullptr;
    int buildMode_ = 0;
    bool roundActive_;
    int duoCount_;
};

#endif // GAMEOBJECTMANAGER_H
