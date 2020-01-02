#ifndef TUNIBOSS_H
#define TUNIBOSS_H
#include "../Game/enemies/enemybase.h"
#include <QGraphicsSceneMouseEvent>

class Tuniboss : public EnemyBase
{ Q_OBJECT
public:
    Tuniboss(QList<QPointF> pointsToFollow, QGraphicsItem * parent);
    ~Tuniboss() override;
    double getHealth();

public slots:
    void moveForward() override;
    void checkHit();
    double getDamage() override;
    double setHealth(double damage);
    void mousePressEvent(QGraphicsSceneMouseEvent *e) override;

private:
   double damage_;
   double health_;
   double STEP_SIZE_;
   QList<QPointF> points;
   QPointF destination_;
   int point_index_;
};

#endif // TUNIBOSS_H
