#ifndef HEADQUARTER_H
#define HEADQUARTER_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include "../Game/mainwindow.h"
#include "../Game/enemies/enemybase.h"
#include "../Game/managers/gameobjectmanager.h"

#include <enemies/enemybase.h>
#include <mainwindow.h>

#include <QLineF>
#include <QPointF>
#include <QList>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <qmath.h>
#include <QTimer>

#include <QDebug>

class headquarter : public QObject, public QGraphicsPixmapItem
{   Q_OBJECT

public:
    headquarter(class ObjectManager* parent = nullptr, QGraphicsScene * scene = nullptr);
    double getHealth();
    double getDamage();
    void takeDamage(double damage);
    void setHealth(int health);

public slots:
    void checkHit();


protected:
    QGraphicsPolygonItem* hit_box;

private:
    QGraphicsScene* scene_;
    class ObjectManager* parent_;
    double health_;
    double damage_;
    bool is_hit_;
};

#endif // HEADQUARTER_H
