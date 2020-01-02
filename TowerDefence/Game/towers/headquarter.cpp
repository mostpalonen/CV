#include "headquarter.h"
#include <enemies/enemybase.h>
#include <enemies/basicenemy.h>
#include <mainwindow.h>

#include <QLineF>
#include <QPointF>
#include <QList>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <qmath.h>
#include <QTimer>

#include <QDebug>

headquarter::headquarter(ObjectManager* parent, QGraphicsScene* scene): QObject()
{
    setPixmap(QPixmap(":images/base.png"));
    scene_ = scene;
    parent_ = parent;

    is_hit_ = false;
    health_ = 50;
    damage_ = 1;

    // Lets create a hitBox for the HQ
    QVector<QPointF> hitBoxCorners;
    hitBoxCorners << QPointF(1,1) << QPointF(1,-1) << QPointF(-1,-1) << QPointF(-1,1);

    // scale hibox points
    int SCALEFACTOR = 44;
    for (int i = 0, n = hitBoxCorners.size(); i < n; i++) {
        hitBoxCorners[i] *= SCALEFACTOR;
    }

    // create the QGraphicsPolygonItem
    hit_box = new QGraphicsPolygonItem(QPolygonF(hitBoxCorners), this);

    // center the hitbox to enemys position
    QPointF hit_box_center(0,0);
    hit_box_center = mapToScene(hit_box_center);
    QPointF HQ_center(x()+44, y()+44);
    QLineF line(hit_box_center, HQ_center);
    hit_box->setPos(x()+line.dx(), y()+line.dy());

    QTimer * hitTimer = new QTimer(this);
    connect(hitTimer, SIGNAL(timeout()), this, SLOT(checkHit()));
    hitTimer->start(500);
}

double headquarter::getHealth()
{
    return health_;
}

void headquarter::checkHit() {
    // Checks is any enemy is hitting the HQ and calls takeDamage based
    // on enemies dealt damage

    QList<QGraphicsItem*> colliding_enemies = hit_box->collidingItems();

    is_hit_ = false;
    for (int i = 0, n = colliding_enemies.size(); i < n; ++i) {
        EnemyBase * enemy = dynamic_cast<EnemyBase*>(colliding_enemies[i]);
        if (enemy) {
            is_hit_ = true;
            if (is_hit_){
               takeDamage(enemy->getDamage());
               is_hit_ = false;
            }
        }
    }
}

void headquarter::takeDamage(double damage) {
    // Lowers HQ's health and checks if HQ is destroyed.
    // If so calls gameOver from ObjectManager

    health_ -= damage;
    if (health_ <= 0) {
        this->parent_->gameOver();
    }
}

void headquarter::setHealth(int health) {
    health_ = health;
}

double headquarter::getDamage() {
    return damage_;
}
