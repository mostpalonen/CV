#ifndef TOWERBASE_H
#define TOWERBASE_H

#include <QObject>
#include <QPointF>
#include <QGraphicsItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsPixmapItem>
//#include "../Game/mainwindow.h"

#include <QPixmap>
#include <QVector>
#include <QPolygonF>
#include <QTimer>
#include <QLineF>
#include <QGraphicsRectItem>
#include <qmath.h>
#include <QGraphicsScene>
//#include <QGraphicsSceneMouseEvent>
#include <memory>

//#include "buildings/buildingbase.h"
#include <enemies/enemybase.h>
#include <bullets/bullet.h>

#include <QDebug>

//#include "../Game/managers/gameobjectmanager.h"

class TowerBase : public QObject, public QGraphicsPixmapItem
{   Q_OBJECT

    //Otettu gom-manager parent ittuun! :: ObjectManager * parent = nullptr,
public:
    TowerBase(QGraphicsScene* scene = nullptr);
    double distanceTo(QGraphicsItem * item);
    virtual void fire();
    //void mousePressEvent(QGraphicsSceneMouseEvent* e);
    QVector<QPointF> points_;

public slots:
    void get_target();

private:
    QGraphicsScene* scene_;
    int level_;

protected:
    QGraphicsPolygonItem * attack_area = nullptr;
    QPointF attack_dest;
    bool has_target;



};

#endif // TOWERBASE_H
