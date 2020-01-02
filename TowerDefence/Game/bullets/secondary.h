#ifndef SECONDARY_H
#define SECONDARY_H

#include "bullet.h"
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QTimer>

class Secondary : public Bullet
{
public:
    Secondary(QGraphicsItem * parent = nullptr);

public slots:
    void move() override;
    double getDamage() override;

private:
    double damage_;
};

#endif // SECONDARY_H
