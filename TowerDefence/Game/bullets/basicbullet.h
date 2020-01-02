#ifndef BASICBULLET_H
#define BASICBULLET_H

#include "bullet.h"
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QTimer>

class BasicBullet : public Bullet
{
public:
    BasicBullet(QGraphicsItem* parent = nullptr);
public slots:
    void move() override;
    double getDamage() override;

private:
    double damage_;
};

#endif // BASICBULLET_H
