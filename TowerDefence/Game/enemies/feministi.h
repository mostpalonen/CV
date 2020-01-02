#ifndef FEMINISTI_H
#define FEMINISTI_H

#include <QObject>
#include "enemybase.h"

class Feministi : public EnemyBase
{ Q_OBJECT
public:
    Feministi(QList<QPointF> pointsToFollow, QGraphicsItem *parent);
    ~Feministi() override;
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

#endif // FEMINISTI_H
