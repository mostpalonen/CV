#ifndef DUO_H
#define DUO_H
#include "../Game/towers/towerbase.h"

class Duo : public TowerBase
{ Q_OBJECT
public:
    Duo(QGraphicsScene * scene = nullptr);
    void fire() override;
private:
    QGraphicsScene * scene_;
    int level_;
    int scale_;
};

#endif // DUO_H
