#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <QObject>
#include "../../Course/CourseLib/interfaces/iobjectmanager.h"



class objectManager : public QObject, public Course::iObjectManager
{
public:
    objectManager();
};

#endif // OBJECTMANAGER_H
