#include "buildingspace.h"
#include <QDebug>


BuildingSpace::BuildingSpace(ObjectManager * parent, int x, int y, bool buildable)
{
    setPos(x, y);

    if (this->pos() == QPointF(792, 792)) {
        buildable_ = false;
    } else {
        buildable_ = buildable;
    }

    if (buildable_) {
        setPixmap(QPixmap(":images/buildablescape.png"));
    } else {
        setPixmap(QPixmap(":images/road_texture.png"));
    }
    parent_ = parent;
}

void BuildingSpace::setState(bool state)
{
    buildable_ = state;
}

void BuildingSpace::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    if(e->buttons() & Qt::LeftButton) {
        if (buildable_ && parent_->getBuildMode() != 0) {
            buildable_ = false;
            parent_->addTower(this->pos());
        }
    }
}

