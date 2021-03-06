#include "tuniboss.h"
#include "../bullets/bullet.h"
#include <QTimer>
#include <qmath.h>
#include <QPen>
#include <QDebug>

extern SoundEngine * sndEngine;

Tuniboss::Tuniboss(QList<QPointF> pointsToFollow, QGraphicsItem *parent):
    EnemyBase(pointsToFollow, parent)
{
    // set graphics for enemy
    setPixmap(QPixmap(":/images/tuniboss"));

    // init values for boss
    damage_ = 5;
    health_ = 20000;
    STEP_SIZE_ = 1;

    points = pointsToFollow;
    destination_ = EnemyBase::getDestination();
    point_index_ = EnemyBase::getPointIndex();

    // create enemies hitbox
    QVector<QPointF> corners;
    corners << QPointF(1,1) << QPointF(1,-1) << QPointF(-1,-1) << QPointF(-1,1);

    // scale hibox points
    int SCALEFACTOR = 44;
    for (int i = 0, n = corners.size(); i < n; i++) {
        corners[i] *= SCALEFACTOR;
    }

    // create the QGraphicsPolygonItem
    hit_box = new QGraphicsPolygonItem(QPolygonF(corners), this);

    // center the hitbox to enemys position
    QPointF hit_box_center(0,0);
    hit_box_center = mapToScene(hit_box_center);
    QPointF enemy_center(x(), y());
    QLineF line(hit_box_center, enemy_center);
    hit_box->setPos(x()+line.dx(), y()+line.dy());

    // connect timer to move_forward
    QTimer * timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(moveForward()));
    timer->start(100); // movespeed

    QTimer * hitTimer = new QTimer(this);
    connect(hitTimer, SIGNAL(timeout()), this, SLOT(checkHit()));
    hitTimer->start(10);
}

Tuniboss::~Tuniboss(){}

void Tuniboss::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    if(e->buttons() & Qt::LeftButton) {
        sndEngine->playSound("alert");
    }
}


double Tuniboss::getHealth()
{
    return health_;
}

void Tuniboss::moveForward()
{
    // If enemy is close to its destination -> rotate to next dest
    QLineF line(pos(), destination_);

    if (line.length() < 5)
    {
        point_index_++;
        // last point reached
        if (point_index_ >= points.size())
        {
            return;
        }
        // last point not reached
        destination_ = points[point_index_];
        rotateToPoint(destination_);
    }

    // move enemy forward at current angle
    double angle = rotation();  // degrees -> convert to radian

    double dy = STEP_SIZE_ * qSin(qDegreesToRadians(angle));
    double dx = STEP_SIZE_ * qCos(qDegreesToRadians(angle));

    setPos(x()+dx, y()+dy);
}

void Tuniboss::checkHit()
{
    // Get a list of projectiles hitting the enemy
    QList<QGraphicsItem*> collidingProjectiles = hit_box->collidingItems();

    is_hit = false;

    if (collidingProjectiles.size() > 0) {
        for (int i = 0, n = collidingProjectiles.size(); i < n; i++) {
            // Make sure that the item colliding is a bullet
            Bullet * bullet = dynamic_cast<Bullet*>(collidingProjectiles[i]);
            if (bullet) {
                is_hit = true;
                if (is_hit){
                    setHealth(bullet->getDamage());
                    if (health_ <= 0){
                        emit  passThis(this);
                        delete this;
                    }
                    delete collidingProjectiles[i];
                    is_hit = false;
                }
            }
            else{
                continue;
            }
        }
    }

}

double Tuniboss::getDamage()
{
    return damage_;
}

double Tuniboss::setHealth(double damage)
{
    if (health_ <= 0)
    {
        delete this;
    }
    return health_ -= damage;
}
