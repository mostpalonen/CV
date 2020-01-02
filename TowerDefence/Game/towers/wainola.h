#ifndef WAINOLA_H
#define WAINOLA_H

#include "../Game/towers/towerbase.h"

/*
#include <QPixmap>
#include <QVector>
#include <QPointF>
#include <QPolygonF>
#include <QTimer>
#include <QLineF>
#include <QGraphicsRectItem>
#include <qmath.h>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem> */

class Wainola : public TowerBase
 { Q_OBJECT
public:
    Wainola(QGraphicsScene* scene = nullptr);
    void fire() override; //OVERRIDE POIS
private:
    QGraphicsScene * scene_;
    int level_;
    int scale_;
};

#endif // WAINOLA_H
