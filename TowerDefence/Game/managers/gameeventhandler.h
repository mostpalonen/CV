#ifndef GAMEEVENTHANDLER_H
#define GAMEEVENTHANDLER_H
#include <QObject>
#include <QPointF>
#include <QList>
#include <QGraphicsScene>
#include "../Game/mainwindow.h"
#include "../towers/towerbase.h"
#include "../enemies/enemybase.h"
#include "../enemies/basicenemy.h"
#include "../enemies/tuniboss.h"
#include "../enemies/humanisti.h"
#include "../enemies/feministi.h"
#include "../enemies/raitsikka.h"
#include <unistd.h>


class gameEventHandler : public QGraphicsScene
{
    Q_OBJECT

public:
    gameEventHandler(class MainWindow* parent = nullptr,
                     QGraphicsScene* scene = nullptr);
    void clearTimersAndEnemies();
    void winWave();
public slots:
    void startWave();
    void spawnEnemy();
    void spawnHumanisti();
    void spawnFeministi();
    void spawnRaitsikka();
    void spawnFinalBoss();
    void createRoad();
    void gameOver(bool win);
    void removeEnemy(class EnemyBase* enemy);
    void checkGoal();

private:
    int waveNumber_ = 1;
    QList<QPointF> pointsToFollow_;

    QGraphicsScene* scene_;
    QList<QTimer*> timers_;
    QList<class EnemyBase*> enemies_;

    class MainWindow* parent_;
    QMap<QString, int> spawned_;
    QMap<QString, int> killed_;
};  // class gameEventHandler


#endif // GAMEEVENTHANDLER_H
