#include "mikontalo.h"


Mikontalo::Mikontalo(QGraphicsScene *scene):
    TowerBase(scene)
{
    setPixmap(QPixmap(":images/mikontalo.png"));
    scene_ = scene;
    scale_ = 120;

    // create points vector for defining an octagon shaped attack_area for the tower
    // QVector<QPointF> points_;
    points_ << QPointF(1,0) << QPointF((sqrt(2)/2), (sqrt(2)/2)) << QPointF(0,1)
           << QPointF((-sqrt(2)/2), (sqrt(2)/2)) << QPointF(-1,0)
           << QPointF((-sqrt(2)/2), (-sqrt(2)/2)) << QPointF(0, -1)
           << QPointF((sqrt(2)/2), (-sqrt(2)/2));

    // scale the points
    for (int i = 0, n = points_.size(); i < n; i++) {
        points_[i] *= scale_ + level_*6;
    }

    // create the QGraphicsPolygonItem
    attack_area = new QGraphicsPolygonItem(QPolygonF(points_), this);
    attack_area -> setPen(QPen(Qt::DotLine));

    // center the octagon to the towers center position
    QPointF octagon_center(0,0);
    octagon_center = mapToScene(octagon_center);
    QPointF tower_center(x()+44, y()+44);
    QLineF line(octagon_center, tower_center);
    attack_area->setPos(x()+line.dx(), y()+line.dy());
}

void Mikontalo::fire() {
    // Fires a bullet in right angle towards the closest enemy
    // and adds the bullet to scene.

    ToxicBullet * bullet = new ToxicBullet();
    bullet->setPos(x()+44, y()+44);

    QLineF line(QPointF(x()+44, y()+44), attack_dest);
    double angle = -1 * line.angle();

    bullet->setRotation(angle);
    scene_->addItem(bullet);
}
