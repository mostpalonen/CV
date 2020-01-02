#include "gameobjectmanager.h"
#include <QGraphicsScene>
#include <QDebug>
#include <QGuiApplication>

ObjectManager::ObjectManager(MainWindow * parent, QGraphicsScene* scene) {
    scene_ = scene;
    parent_ = parent;
    duoCount_ = 0;
    connect(this, SIGNAL(passCost(int, int, int, int)), parent_, SLOT(passCost(int, int, int, int)));
}

void ObjectManager::addSpace(int x, int y) {
    // Creates the map tile
    BuildingSpace * b = new BuildingSpace(this, x, y, true);
    spaces_.push_back(b);
    scene_->addItem(b);
}

void ObjectManager::addTower(QPointF pos) {
    // Builds correct tower according to MainWindows call
    // and then emits the build costs of that tower

    //WÄINÖLÄ
    if (buildMode_ == 1) {
        buildMode_ = 0;
        emit passCost(-50, 0, 0, 0);

        Wainola * t = new Wainola(scene_);
        t->setPos(pos);
        scene_->addItem(t);
        towers_.push_back(t);
        QGuiApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
        parent_->cancelBuilding();
        qDebug() << "Rakennettu: Wäinölä.";

    //HQ
    } else if (buildMode_ == 2) {
        buildMode_ = 0;
        headquarter * h = new headquarter(this, scene_);
        h->setPos(pos);
        scene_->addItem(h);
        hq_ = h;
        QGuiApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
        parent_->cancelBuilding();
        qDebug() << "Rakennettu: TTY.";

    //MIKONTALO
    } else if (buildMode_ == 3) {
        buildMode_ = 0;
        emit passCost(-150, -50, -50, 0);

        Mikontalo * h = new Mikontalo(scene_);
        h->setPos(pos);
        scene_->addItem(h);
        towers_.push_back(h);
        QGuiApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
        parent_->cancelBuilding();
        qDebug() << "Rakennettu: Mikontalo.";

    //MATRIISIT
    }  else if (buildMode_ == 4) {
        buildMode_ = 0;
        emit passCost(-300, -500, -450, -15);

        Matriisit * h = new Matriisit(scene_);
        h->setPos(pos);
        scene_->addItem(h);
        towers_.push_back(h);
        QGuiApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
        parent_->cancelBuilding();
        qDebug() << "Rakennettu: Matriisitornit.";

    //TIETEENTORNIT
    } else if (buildMode_ == 5) {
        buildMode_ = 0;
        emit passCost(-200, -150, -100, -4);

        TTorni * h = new TTorni(scene_);
        h->setPos(pos);
        scene_->addItem(h);
        towers_.push_back(h);
        QGuiApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
        parent_->cancelBuilding();
        qDebug() << "Rakennettu: Tieteentornit.";

    // DUO
    } else if (buildMode_ == 6) {
        buildMode_ = 0;

        if (duoCount_ <= 1) {
            duoCount_ += 1;
            emit passCost(-120, -100, -75, -2);

            Duo * h = new Duo(scene_);
            h->setPos(pos);
            scene_->addItem(h);
            towers_.push_back(h);
            QGuiApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
            parent_->cancelBuilding();
            qDebug() << "Rakennettu: Duo.";

            QTimer * resourceTimer = new QTimer(this);
            connect(resourceTimer, SIGNAL(timeout()), this, SLOT(addRes()));
            resourceTimer->start(21000);
            timers_.push_back(resourceTimer);
        } else {
            qDebug() << "MAX MÄÄRÄ DUOJA";
        }
    }
}

bool ObjectManager::checkDuos() {
    // Checks if the player has build max amount of DUOs

    if (duoCount_ <= 1) {
        return true;
    } else {
        return false;
    }
}

double ObjectManager::getHqHealth() {
    return hq_->getHealth();
}

void ObjectManager::setHqHp(int amount) {
    hq_->setHealth(amount);
}


void ObjectManager::setBuildMode(int building) {
    buildMode_ = building;   
}

int ObjectManager::getBuildMode() {
    return buildMode_;
}

void ObjectManager::resetSpaceStates() {
    for (BuildingSpace * s : spaces_) {
        s->setState(true);
    }
    // Kaikki tie-spacet asetetaan sellaisiksi,
    // ettei niiden päälle voi rakentaa
    spaces_.at(0)->setState(false);
    spaces_.at(10)->setState(false);
    spaces_.at(11)->setState(false);
    spaces_.at(12)->setState(false);
    spaces_.at(13)->setState(false);
    spaces_.at(14)->setState(false);
    spaces_.at(15)->setState(false);
    spaces_.at(16)->setState(false);
    spaces_.at(17)->setState(false);
    spaces_.at(18)->setState(false);
    spaces_.at(20)->setState(false);
    spaces_.at(21)->setState(false);
    spaces_.at(24)->setState(false);
    spaces_.at(25)->setState(false);
    spaces_.at(26)->setState(false);
    spaces_.at(28)->setState(false);
    spaces_.at(34)->setState(false);
    spaces_.at(36)->setState(false);
    spaces_.at(38)->setState(false);
    spaces_.at(40)->setState(false);
    spaces_.at(41)->setState(false);
    spaces_.at(44)->setState(false);
    spaces_.at(45)->setState(false);
    spaces_.at(46)->setState(false);
    spaces_.at(47)->setState(false);
    spaces_.at(48)->setState(false);
    spaces_.at(50)->setState(false);
    spaces_.at(51)->setState(false);
    spaces_.at(52)->setState(false);
    spaces_.at(53)->setState(false);
    spaces_.at(54)->setState(false);
    spaces_.at(55)->setState(false);
    spaces_.at(56)->setState(false);
    spaces_.at(60)->setState(false);
    spaces_.at(70)->setState(false);
    spaces_.at(74)->setState(false);
    spaces_.at(75)->setState(false);
    spaces_.at(76)->setState(false);
    spaces_.at(77)->setState(false);
    spaces_.at(78)->setState(false);
    spaces_.at(79)->setState(false);
    spaces_.at(80)->setState(false);
    spaces_.at(90)->setState(false);
    spaces_.at(91)->setState(false);
    spaces_.at(92)->setState(false);
    spaces_.at(93)->setState(false);
    spaces_.at(94)->setState(false);
    spaces_.at(84)->setState(false);
    spaces_.at(89)->setState(false);
    spaces_.at(99)->setState(false);
}

void ObjectManager::addRes() {
    if (roundActive_) {
        emit passCost(60,30,15,1);
    }
}

void ObjectManager::roundStatus(bool set) {
    roundActive_ = set;
}

void ObjectManager::gameOver() {
    // Deletes all class timers and resets game status

    if (timers_.size() != 0) {
        for (QTimer* t : timers_) {
            t->stop();
            timers_.pop_front();
            delete t;
        }
    }
    duoCount_ = 0;
    if (towers_.size() != 0) {
        for (TowerBase * t : towers_) {
            scene_->removeItem(t);
            towers_.removeFirst();
            delete t;
        }
    }
    resetSpaceStates();
}
