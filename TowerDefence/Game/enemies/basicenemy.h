#ifndef BASICENEMY_H
#define BASICENEMY_H

#include <QObject>
#include "enemybase.h"

class BasicEnemy : public EnemyBase
{
    Q_OBJECT
public:
    BasicEnemy(QList<QPointF> pointsToFollow, QGraphicsItem *parent);
    ~BasicEnemy() override;
    double getHealth();

public slots:
    void moveForward() override;
    void checkHit();
    double getDamage() override;
    double setHealth(double damage);

private:
    double health_;
    double damage_;
    double STEP_SIZE_;
    QList<QPointF> points;
    QPointF destination_;
    int point_index_;
};

#endif // BASICENEMY_H
