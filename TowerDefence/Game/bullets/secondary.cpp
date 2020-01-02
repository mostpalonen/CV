#include "secondary.h"
#include <QPixmap>
#include <QTimer>
#include <qmath.h>
#include "mainwindow.h"

Secondary::Secondary(QGraphicsItem *parent):
    Bullet(parent)
{
    // set bullet graphics
    setPixmap(QPixmap(":/images/secondarybullet.png"));

    // connect a timer to move
    QTimer * move_timer = new QTimer(this);
    connect(move_timer, SIGNAL(timeout()), this, SLOT(move()));
    move_timer->start(50);

    // init values
    damage_ = 2;
}

void Secondary::move()
{
    // Calculates the bullets new position according to STEP_SIZE and sets it in scene

    int STEP_SIZE = 10;
    double angle = rotation(); // degrees -> convert to radian for qSin and qCos

    double dy = STEP_SIZE * qSin(qDegreesToRadians(angle));
    double dx = STEP_SIZE * qCos(qDegreesToRadians(angle));

    setPos(x()+dx, y()+dy);
}

double Secondary::getDamage()
{
    return damage_;
}
