#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <QObject>
#include <QList>
#include <QMap>
#include <QDebug>
#include <mainwindow.h>
#include "managers/gameobjectmanager.h"


class ResourceManager : public QObject
{ Q_OBJECT
public:
    ResourceManager(QWidget* parent = nullptr, class ObjectManager* gom = nullptr);
public slots:
    void modifyResource(QString res, int amount);
    int getResource(QString res);
    bool checkResources(int building);
    void forceResource(QString res, int value);

signals:

private:
    QMap<QString, int> resources_;
    QWidget* parent_ = nullptr;
    class ObjectManager* gom_ = nullptr;
};

#endif // RESOURCEMANAGER_H
