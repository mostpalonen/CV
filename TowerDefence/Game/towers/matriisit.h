#ifndef MATRIISIT_H
#define MATRIISIT_H
#include "../Game/towers/towerbase.h"
#include "../Game/bullets/moneybullet.h"

class Matriisit : public TowerBase
{ Q_OBJECT
public:
    Matriisit(QGraphicsScene * scene = nullptr);
    void fire() override;
private:
    QGraphicsScene * scene_;
    int level_;
    int scale_;
};

#endif // MATRIISIT_H
