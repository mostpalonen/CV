#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QTimer>

class Bullet: public QObject, public QGraphicsPixmapItem
{   Q_OBJECT
public:
    Bullet(QGraphicsItem * parent=nullptr);

public slots:
    virtual void move();
    virtual double getDamage(); 

private:
    double damage_;
};

#endif // BULLET_H
