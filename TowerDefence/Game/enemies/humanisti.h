#ifndef HUMANISTI_H
#define HUMANISTI_H

#include <QObject>
#include "enemybase.h"

class Humanisti : public EnemyBase
{ Q_OBJECT
public:
    Humanisti(QList<QPointF> pointsToFollow, QGraphicsItem *parent);
    ~Humanisti() override;
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

#endif // HUMANISTI_H
