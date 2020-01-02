#ifndef MIKONTALO_H
#define MIKONTALO_H
#include "../Game/towers/towerbase.h"
#include "../Game/bullets/toxicbullet.h"

class Mikontalo : public TowerBase
{ Q_OBJECT
public:
    Mikontalo(QGraphicsScene* scene = nullptr);
    void fire() override;
private:
    QGraphicsScene * scene_;
    int level_;
    int scale_;
};

#endif // MIKONTALO_H
