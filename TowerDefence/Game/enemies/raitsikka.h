#ifndef RAITSIKKA_H
#define RAITSIKKA_H
#include "../Game/enemies/enemybase.h"


class Raitsikka: public EnemyBase
{ Q_OBJECT
public:
    Raitsikka(QList<QPointF> pointsToFollow, QGraphicsItem * parent);
    ~Raitsikka() override;
    double getHealth();

public slots:
    void moveForward() override;
    void checkHit();
    double getDamage() override;
    double setHealth(double damage);

private:
   double damage_;
   double health_;
   double STEP_SIZE_;
   QList<QPointF> points;
   QPointF destination_;
   int point_index_;
};

#endif // RAITSIKKA_H
