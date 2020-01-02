#include "towerbase.h"


TowerBase::TowerBase(QGraphicsScene* scene) {

    scene_ = scene;
    level_ = 1;

    // set attack destination
    attack_dest = QPointF(0,0);
    has_target = false;

    QTimer * timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(get_target()));
    timer->start(1000);
}

double TowerBase::distanceTo(QGraphicsItem *item) {
    // Returns the distance to given item
    QLineF line(this->pos(), item->pos());
    return line.length();
}

void TowerBase::fire() {
    // Fires a bullet in right angle towards the closest enemy
    // and adds the bullet to scene.

    Bullet * bullet = new Bullet();
    bullet->setPos(x()+44, y()+44);

    QLineF line(QPointF(x()+44, y()+44), attack_dest);
    double angle = -1 * line.angle();

    bullet->setRotation(angle);
    scene_->addItem(bullet);
}

void TowerBase::get_target() {
    // Gets a list of all the objects that collide with attack_area and finds the closest one
    // and sets it's position as the attack_destination

    // Get a list of all the objects within attack_area
    QList<QGraphicsItem*> colliding_items = attack_area->collidingItems();

    // Assume that the tower does not have a target
    has_target = false;

    // Find the closest enemy
    double closest_dist = 500;  // Assume the distance
    QPointF closest_pt(0,0);

    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        // make sure the colliding item is an enemy
        EnemyBase * enemy = dynamic_cast<EnemyBase*>(colliding_items[i]);

        // Check if the distance is closer than assumed
        if (enemy)
        {
            double this_dist = distanceTo(colliding_items[i]);
            if (this_dist < closest_dist)
            {
                closest_dist = this_dist;
                closest_pt = colliding_items[i]->pos();
                has_target = true;
            }
        }
    }

    // If has_target = true, set the closest enemy as attack_dest and fire
    if (has_target)
    {
        attack_dest = closest_pt;
        fire();
    }
}


