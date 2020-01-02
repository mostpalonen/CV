#ifndef TOXICBULLET_H
#define TOXICBULLET_H

#include "bullet.h"
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QTimer>

class ToxicBullet: public Bullet
{
public:
    ToxicBullet(QGraphicsItem* parent = nullptr);

public slots:
    void move() override;
    double getDamage() override;

private:
    double damage_;
};

#endif // TOXICBULLET_H
