#ifndef ENEMYBASE_H
#define ENEMYBASE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QList>
#include <QPointF>
#include <QGraphicsSceneMouseEvent>
#include "managers/soundengine.h"

class EnemyBase : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    EnemyBase(QList<QPointF> pointsToFollow, QGraphicsItem * parent = nullptr);
    virtual ~EnemyBase();
    void rotateToPoint(QPointF p);
    QPointF getDestination();
    int getPointIndex();

signals:
    void passThis(EnemyBase* enemy);

public slots:
    virtual void moveForward();
    virtual double getDamage();

protected:
    QGraphicsPolygonItem * hit_box;
    bool is_hit;

private:
    QList<QPointF> points;
    QPointF dest;
    int point_index;
    double health_;
    double damage_;
};

#endif // ENEMYBASE_H
