#include "gameeventhandler.h"
#include <towers/headquarter.h>

#include <QTimer>
#include <QPushButton>
#include <QDebug>
#include <QGraphicsScene>

extern SoundEngine * sndEngine;

gameEventHandler::gameEventHandler(class MainWindow *parent, QGraphicsScene* scene):
    QGraphicsScene(parent)
{
    waveNumber_ = 1;
    scene_ = scene;
    parent_ = parent;

    // Vector to tell enemies where to go in map
    pointsToFollow_ << QPointF(0,44) << QPointF(220,44)
                    << QPointF(220,132) << QPointF(132,132)
                    << QPointF(132,748) <<QPointF(396,748)
                    << QPointF(396,396) << QPointF(220,396)
                    << QPointF(220,572) << QPointF(484,572)
                    << QPointF(484,132) << QPointF(396,132)
                    << QPointF(396,44) << QPointF(836,44)
                    << QPointF(836, 396) << QPointF(660,396)
                    << QPointF(660,836) << QPointF(836,836);
}

void gameEventHandler::clearTimersAndEnemies()
{
    if (timers_.size() != 0) {
        for (QTimer * i : timers_) {
            i->stop();
            timers_.pop_front();
            delete i;
        }
    }
    if (enemies_.size() != 0) {
        for (EnemyBase* e : enemies_) {
            scene_->removeItem(e);
            enemies_.removeFirst();
        }
        enemies_.clear();
    }
}

void gameEventHandler::winWave()
{
    // Pauses timers and sets all the right data to ui

    parent_->roundStatus(false);
    sndEngine->stopSounds();

    sndEngine->playSound("win");
    clearTimersAndEnemies();

    parent_->passCost(30 * waveNumber_, 25*waveNumber_,
                      20* waveNumber_, 2*waveNumber_);

    if (waveNumber_ != 8) {
        parent_->winRound();
        parent_->operateTextBrowser("Päihitit erän " + QString::number(waveNumber_) + "! \n"
                                    + "Valmistaudu seuraavaan erään...");
        waveNumber_ += 1;
    } else {
        sndEngine->playSound("alert");
        parent_->winRound();
        parent_->operateTextBrowser("PÄIHITIT TUNIN! \n"
                                    "OLET MESTAREIDEN MESTARI!");
        parent_->gameOver(true);
    }

}

void gameEventHandler::spawnEnemy()
{
    // Spawns basicEnemy to scene. Offset needed to have enemy move on the road

    BasicEnemy * e = new BasicEnemy(pointsToFollow_, nullptr);

    connect(e, SIGNAL(passThis(EnemyBase*)), this, SLOT(removeEnemy(EnemyBase*)));

    e->setPos(pointsToFollow_[0]);
    e->setOffset(QPointF(-20,-20));
    scene_->addItem(e);
    enemies_.push_back(e);

    spawned_["basic"] += 1;
}

void gameEventHandler::spawnHumanisti()
{

    // Spawns Humanisti to scene. Offset needed to have enemy move on the road

    Humanisti * nisti = new Humanisti(pointsToFollow_, nullptr);

    connect(nisti, SIGNAL(passThis(EnemyBase*)), this, SLOT(removeEnemy(EnemyBase*)));
    nisti->setPos(pointsToFollow_[0]);
    nisti->setOffset(QPointF(-20,-20));
    scene_->addItem(nisti);
    enemies_.push_back(nisti);

    spawned_["humanist"] += 1;
}

void gameEventHandler::spawnFeministi()
{
    // Spawns Feministi to scene. Offset needed to have enemy move on the road

    Feministi * fem = new Feministi(pointsToFollow_, nullptr);

    connect(fem, SIGNAL(passThis(EnemyBase*)), this, SLOT(removeEnemy(EnemyBase*)));
    fem->setPos(pointsToFollow_[0]);
    fem->setOffset(QPointF(-20,-20));
    scene_->addItem(fem);
    enemies_.push_back(fem);

    spawned_["feminist"] += 1;
}

void gameEventHandler::spawnRaitsikka()
{
    // Spawns Raitiskka to scene. Offset needed to have enemy move on the road

    Raitsikka * vr = new Raitsikka(pointsToFollow_, nullptr);

    connect(vr, SIGNAL(passThis(EnemyBase*)), this, SLOT(removeEnemy(EnemyBase*)));
    vr->setPos(pointsToFollow_[0]);
    vr->setOffset(QPointF(-44,-44));
    scene_->addItem(vr);
    enemies_.push_back(vr);

    spawned_["tram"] += 1;
}

void gameEventHandler::spawnFinalBoss()
{
    // Spawns TuniBoss to scene. Offset needed to have enemy move on the road

    Tuniboss * boss = new Tuniboss(pointsToFollow_, nullptr);

    connect(boss, SIGNAL(passThis(EnemyBase*)), this, SLOT(removeEnemy(EnemyBase*)));
    boss->setPos(pointsToFollow_[0]);
    boss->setOffset(QPointF(-44,-44));
    scene_->addItem(boss);
    enemies_.push_back(boss);

    spawned_["tuni"] += 1;
}

void gameEventHandler::createRoad()
{
    // Creates a road for the enemies to move on according to the pointsToFollow

    for (int i = 0, n = pointsToFollow_.size()-1; i < n; i++){
        // create a line connecting the two points
        QLineF line(pointsToFollow_[i],pointsToFollow_[i+1]);
        QGraphicsLineItem * lineItem = new QGraphicsLineItem(line);

        QPen pen;
        pen.setWidth(50);
        pen.setColor(Qt::gray);

        lineItem->setPen(pen);
        scene_->addItem(lineItem);
    }
}

void gameEventHandler::gameOver(bool win)
{
    // Clears previous games timers and enemies and resets all the sounds
    // and resets game data to round 1

    if (win == false) {
        parent_->roundStatus(false);
        sndEngine->stopSounds();
        sndEngine->playSound("lose");
        waveNumber_ = 1;
        clearTimersAndEnemies();
    } else {
        sndEngine->stopSounds();
        parent_->roundStatus(false);
        waveNumber_ = 1;
    }
}

void gameEventHandler::removeEnemy(EnemyBase *enemy)
{
    // Checks which enemy was killed and pass the info to MainWindow
    // to tell resourceManager to add resources. Also removes the killed
    // enemy from game.

    for (int i = 0; i < enemies_.size(); i++) {
        if (enemies_.at(i) == enemy) {
            if (dynamic_cast<BasicEnemy*>(enemies_.at(i))) {
                killed_["basic"] += 1;
                parent_->passCost(2, 0, 1, 0);
            } else if (dynamic_cast<Humanisti*>(enemies_.at(i))) {
                killed_["humanist"] += 1;
                parent_->passCost(3, 4, 0, 0);
            } else if (dynamic_cast<Feministi*>(enemies_.at(i))) {
                killed_["feminist"] += 1;
                parent_->passCost(5, 5, 4, 0);
            } else if (dynamic_cast<Raitsikka*>(enemies_.at(i))) {
                killed_["tram"] += 1;
                parent_->passCost(100, 100, 100, 2);
            } else if (dynamic_cast<Tuniboss*>(enemies_.at(i))) {
                killed_["tuni"] += 1;
                parent_->passCost(1000, 1000, 1000, 20);
            }
            enemies_.removeAt(i);
            sndEngine->playSound("death");
        }
    }
}

void gameEventHandler::checkGoal()
{
    // Checks if player has killed all the waves enemies.
    // If so stops enemies timers

    if (waveNumber_ == 1) {
        if (spawned_["basic"] >= 10) {
            timers_.at(0)->stop();
        }  if (spawned_["humanist"] >= 5) {
            timers_.at(1)->stop();
        }

        if (killed_["basic"] >= 10 && killed_["humanist"] >= 5) {
            winWave();
        }
    } else if (waveNumber_ == 2) {
        if (spawned_["basic"] >= 25) {
            timers_.at(0)->stop();
        }  if (spawned_["humanist"] >= 10) {
            timers_.at(1)->stop();
        }
        if (killed_["basic"] >= 25 && killed_["humanist"] >= 10) {
            winWave();
        }
    } else if (waveNumber_ == 3) {
        if (spawned_["basic"] >= 40) {
            timers_.at(0)->stop();
        }  if (spawned_["humanist"] >= 20) {
            timers_.at(1)->stop();
        } if (spawned_["feministi"] >= 10) {
            timers_.at(2)->stop();
        }
        if (killed_["basic"] >= 40 && killed_["humanist"] >= 20
            && killed_["feminist"] >= 10) {
            winWave();
        }
    } else if (waveNumber_ == 4) {
        if (spawned_["basic"] >= 8) {
            timers_.at(0)->stop();
        }  if (spawned_["humanist"] >= 5) {
            timers_.at(1)->stop();
        } if (spawned_["tram"] >= 1) {
            timers_.at(3)->stop();
        }
        if (killed_["basic"] >= 8 && killed_["humanist"] >= 5
            && killed_["tram"] >= 1) {
            winWave();
        }
    } else if (waveNumber_ == 5) {
        if (spawned_["basic"] >= 30) {
            timers_.at(0)->stop();
        } if (spawned_["humanist"] >= 30) {
            timers_.at(1)->stop();
        } if (spawned_["feminist"] >= 50) {
            timers_.at(2)->stop();
        }
        if (killed_["basic"] >= 30 &&
                killed_["humanist"] >= 30 &&
                killed_["feminist"] >= 50) {
            winWave();
        }
    } else if (waveNumber_ == 6) {
        if (spawned_["basic"] >= 99) {
            timers_.at(0)->stop();
        } if (spawned_["humanist"] >= 99) {
            timers_.at(1)->stop();
        } if (spawned_["feminist"] >= 99) {
            timers_.at(2)->stop();
        }
        if (killed_["basic"] >= 99 &&
                killed_["humanist"] >= 99 &&
                killed_["feminist"] >= 99) {
            winWave();
        }
    } else if (waveNumber_ == 7) {
        if (spawned_["tram"] >= 8) {
            timers_.at(3)->stop();
        } if (spawned_["feminist"] >= 50) {
            timers_.at(2)->stop();
        }
        if (killed_["tram"] >= 8  && killed_["feminist"] >= 50){
            winWave();
        }
    } else if (waveNumber_ == 8) {
        if (spawned_["tuni"] >= 1) {
            timers_.at(4)->stop();
        } if (spawned_["tram"] >= 15) {
            timers_.at(3)->stop();
        }
        if (killed_["tuni"] >= 1) {
            timers_.at(3)->stop();
            winWave();
        }
    }
}

void gameEventHandler::startWave()
{
    // Starts correct wave and calls correct spawnEnemy methods.
    // Resets previous rounds spawned and killed enemy records

    parent_->roundStatus(true);
    spawned_.clear();
    killed_.clear();
    if (waveNumber_ != 8) {
        sndEngine->playSound("start");
    } else {
        sndEngine->playSound("alert");
    }

    parent_->operateTextBrowser("Erä " + QString::number(waveNumber_) + " alkaa. \n");

    QTimer * goalTimer = new QTimer(this);
    connect(goalTimer, SIGNAL(timeout()),
            this, SLOT(checkGoal()));
    goalTimer->start(1000);

    QTimer * enemyTimer = new QTimer(this);
    QTimer * enemyTimer2 = new QTimer(this);
    QTimer * enemyTimer3 = new QTimer(this);
    QTimer * enemyTimer4 = new QTimer(this);
    QTimer * enemyTimer5 = new QTimer(this);
    timers_.push_back(enemyTimer);
    timers_.push_back(enemyTimer2);
    timers_.push_back(enemyTimer3);
    timers_.push_back(enemyTimer4);
    timers_.push_back(enemyTimer5);
    timers_.push_back(goalTimer);

    connect(enemyTimer, SIGNAL(timeout()),
    this, SLOT(spawnEnemy()));
    connect(enemyTimer2, SIGNAL(timeout()),
    this, SLOT(spawnHumanisti()));
    connect(enemyTimer3, SIGNAL(timeout()),
    this, SLOT(spawnFeministi()));
    connect(enemyTimer4, SIGNAL(timeout()),
    this, SLOT(spawnRaitsikka()));
    connect(enemyTimer5, SIGNAL(timeout()),
    this, SLOT(spawnFinalBoss()));


    if (waveNumber_ == 1) {
        sndEngine->playSound("music");       
        enemyTimer->start(3500);
        enemyTimer2->start(5000);

    } else if (waveNumber_ == 2) {
        sndEngine->playSound("music");
        enemyTimer->start(3500);
        enemyTimer2->start(5000);
    } else if (waveNumber_ == 3) {
        sndEngine->playSound("music");
        enemyTimer->start(3500);
        enemyTimer2->start(4000);
        enemyTimer3->start(5000);
    } else if (waveNumber_ == 4) {
        sndEngine->playSound("bossmusic");
        parent_->operateTextBrowser("Erä " + QString::number(waveNumber_) +
                                    " alkaa. \n" +
                                    "Varo raiteilla!!");
        enemyTimer4->start(22000);
        enemyTimer->start(1000);
        enemyTimer2->start(900);
    } else if (waveNumber_ == 5) {
        sndEngine->playSound("music");
        enemyTimer->start(1000);
        enemyTimer2->start(1100);
        enemyTimer3->start(900);
    } else if (waveNumber_ == 6) {
        sndEngine->playSound("music");
        enemyTimer->start(1500);
        enemyTimer2->start(1500);
        enemyTimer3->start(1500);
    } else if (waveNumber_ == 7) {
        sndEngine->playSound("bossmusic");
        parent_->operateTextBrowser("Erä " + QString::number(waveNumber_) +
                                    " alkaa. \n" +
                                    "Allianssi testiajaa useita ratikoita!");
        enemyTimer4->start(8000);
        enemyTimer3->start(1000);
    } else if (waveNumber_ == 8) {
        sndEngine->playSound("finalbossmusic");
        parent_->operateTextBrowser("Aika on koittanut... "
                                    "Todista itsesi ja pysäyttä TUNI kätyreineen!!");
        enemyTimer5->start(1000);
        enemyTimer4->start(25000);
    }
}
