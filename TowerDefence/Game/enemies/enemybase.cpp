#include "enemybase.h"
#include "mainwindow.h"
#include <QPixmap>
#include <QTimer>
#include <qmath.h>
#include <QVector>
#include <QPointF>
#include <QList>
#include <QLineF>

#include <bullets/bullet.h>
#include <towers/headquarter.h>
#include <managers/gameeventhandler.h>

#include <QDebug>

EnemyBase::EnemyBase(QList<QPointF> pointsToFollow, QGraphicsItem *parent):
    QObject(), QGraphicsPixmapItem(parent) {

    is_hit = false;
    setPixmap(QPixmap(":/images/basicenemy.png"));

    // set route for enemy
    points = pointsToFollow;
    point_index = 0;
    dest = points[0];
    rotateToPoint(dest);
}

EnemyBase::~EnemyBase(){}


void EnemyBase::rotateToPoint(QPointF p)
{
    // QLine gets angle counting counter clockwise and set rotation
    // sets it clockwise, so multiply angle() by -1
    QLineF line(pos(), p);
    setRotation(-1 * line.angle());
}

QPointF EnemyBase::getDestination()
{
    return dest;
}

int EnemyBase::getPointIndex()
{
    return point_index;
}

void EnemyBase::moveForward()
{
    // If enemy is close to its destination -> rotate to next dest
    QLineF line(pos(), dest);

    if (line.length() < 5)
    {
        point_index++;
        // last point reached
        if (point_index >= points.size())
        {
            return;
        }
        // last point not reached
        dest = points[point_index];
        rotateToPoint(dest);
    }

    // move enemy forward at current angle
    int STEP_SIZE = 5;
    double angle = rotation();  // degrees -> convert to radian

    double dy = STEP_SIZE * qSin(qDegreesToRadians(angle));
    double dx = STEP_SIZE * qCos(qDegreesToRadians(angle));

    setPos(x()+dx, y()+dy);
}

double EnemyBase::getDamage(){}

