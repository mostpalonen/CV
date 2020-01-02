#ifndef BUILDINGSPACE_H
#define BUILDINGSPACE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <towers/towerbase.h>
#include <QGraphicsSceneMouseEvent>
#include <managers/gameobjectmanager.h>

class BuildingSpace: public QGraphicsPixmapItem
{
    //Q_OBJECT

public:
    BuildingSpace(class ObjectManager* parent, int x, int y, bool buildable);
    void setState(bool state);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* e);
private:
    bool buildable_;
    class ObjectManager* parent_ = nullptr;
};

#endif // BUILDINGSPACE_H
