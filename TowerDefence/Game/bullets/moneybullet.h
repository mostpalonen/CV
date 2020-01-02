#ifndef MONEYBULLET_H
#define MONEYBULLET_H

#include "bullet.h"
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QTimer>

class Moneybullet : public Bullet
{
public:
    Moneybullet(QGraphicsItem * parent = nullptr);

public slots:
    void move() override;
    double getDamage() override;

private:
    double damage_;
};

#endif // MONEYBULLET_H
