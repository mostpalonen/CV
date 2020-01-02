#ifndef TTORNI_H
#define TTORNI_H
#include "../Game/towers/towerbase.h"
#include "../Game/bullets/basicbullet.h"
#include "../Game/bullets/secondary.h"

class TTorni : public TowerBase
{ Q_OBJECT
public:
    TTorni(QGraphicsScene * scene = nullptr);
    void fire() override;
private:
    QGraphicsScene * scene_;
    int level_;
    int scale_;
};

#endif // TTORNI_H
