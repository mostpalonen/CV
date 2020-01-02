QT += testlib
QT += gui
QT += widgets
QT += multimedia
QT += core

TARGET = tst_unittest.cpp

CONFIG += qt console warn_on depend_includepath testcase c++14
CONFIG -= app_bundle
CONFIG += console

TEMPLATE = app

INCLUDEPATH +=  $$PWD/../Game \
                $$PWD/../Course/CourseLib \


DEPENDPATH +=   $$PWD/../Game \
                $$PWD/../Course/CourseLib \

HEADERS += \
        $$PWD/../Game/managers/gameeventhandler.h \
        $$PWD/../Game/managers/gameobjectmanager.h \
        $$PWD/../Game/managers/resourcemanager.h \
        $$PWD/../Game/managers/soundengine.h \
        $$PWD/../Game/bullets/basicbullet.h \
        $$PWD/../Game/bullets/bullet.h \
        $$PWD/../Game/bullets/moneybullet.h \
        $$PWD/../Game/bullets/secondary.h \
        $$PWD/../Game/bullets/toxicbullet.h \
        $$PWD/../Game/enemies/basicenemy.h \
        $$PWD/../Game/enemies/enemybase.h \
        $$PWD/../Game/enemies/feministi.h \
        $$PWD/../Game/enemies/humanisti.h \
        $$PWD/../Game/enemies/raitsikka.h \
        $$PWD/../Game/enemies/tuniboss.h \
        $$PWD/../Game/tiles/buildingspace.h \
        $$PWD/../Game/towers/duo.h \
        $$PWD/../Game/towers/headquarter.h \
        $$PWD/../Game/towers/matriisit.h \
        $$PWD/../Game/towers/mikontalo.h \
        $$PWD/../Game/towers/towerbase.h \
        $$PWD/../Game/towers/ttorni.h \
        $$PWD/../Game/towers/wainola.h \
        $$PWD/../Game/mainwindow.h \
        $$PWD/../Game/dialoginfo.h \
        $$PWD/../Game/dialogstart.h \
        $$PWD/../Game/player.h \
        $$PWD/../Course/CourseLib/buildings/buildingbase.h \
        $$PWD/../Course/CourseLib/buildings/farm.h \
        $$PWD/../Course/CourseLib/buildings/headquarters.h \
        $$PWD/../Course/CourseLib/buildings/outpost.h \
        $$PWD/../Course/CourseLib/exceptions/baseexception.h \
        $$PWD/../Course/CourseLib/exceptions/keyerror.h \
        $$PWD/../Course/CourseLib/exceptions/ownerconflict.h \
        $$PWD/../Course/CourseLib/exceptions/invalidpointer.h \
        $$PWD/../Course/CourseLib/exceptions/illegalaction.h \
        $$PWD/../Course/CourseLib/exceptions/notenoughspace.h \
        $$PWD/../Course/CourseLib/graphics/simplemapitem.h \
        $$PWD/../Course/CourseLib/graphics/simplegamescene.h \
        $$PWD/../Course/CourseLib/interfaces/iobjectmanager.h \
        $$PWD/../Course/CourseLib/interfaces/igameeventhandler.h \
        $$PWD/../Course/CourseLib/tiles/grassland.h \
        $$PWD/../Course/CourseLib/tiles/forest.h \
        $$PWD/../Course/CourseLib/tiles/tilebase.h \
        $$PWD/../Course/CourseLib/workers/basicworker.h \
        $$PWD/../Course/CourseLib/workers/workerbase.h \
        $$PWD/../Course/CourseLib/core/basicresources.h \
        $$PWD/../Course/CourseLib/core/placeablegameobject.h \
        $$PWD/../Course/CourseLib/core/worldgenerator.h \
        $$PWD/../Course/CourseLib/core/coordinate.h \
        $$PWD/../Course/CourseLib/core/playerbase.h \
        $$PWD/../Course/CourseLib/core/gameobject.h \
        $$PWD/../Course/CourseLib/core/resourcemaps.h \

SOURCES +=  tst_unittest.cpp \
        $$PWD/../Game/managers/gameeventhandler.cc \
        $$PWD/../Game/managers/gameobjectmanager.cpp \
        $$PWD/../Game/managers/resourcemanager.cpp \
        $$PWD/../Game/managers/soundengine.cpp \
        $$PWD/../Game/bullets/basicbullet.cpp \
        $$PWD/../Game/bullets/bullet.cpp \
        $$PWD/../Game/bullets/moneybullet.cpp \
        $$PWD/../Game/bullets/secondary.cpp \
        $$PWD/../Game/bullets/toxicbullet.cpp \
        $$PWD/../Game/enemies/basicenemy.cpp \
        $$PWD/../Game/enemies/enemybase.cpp \
        $$PWD/../Game/enemies/feministi.cpp \
        $$PWD/../Game/enemies/humanisti.cpp \
        $$PWD/../Game/enemies/raitsikka.cpp \
        $$PWD/../Game/enemies/tuniboss.cpp \
        $$PWD/../Game/tiles/buildingspace.cpp \
        $$PWD/../Game/towers/duo.cpp \
        $$PWD/../Game/towers/headquarter.cpp \
        $$PWD/../Game/towers/matriisit.cpp \
        $$PWD/../Game/towers/mikontalo.cpp \
        $$PWD/../Game/towers/towerbase.cpp \
        $$PWD/../Game/towers/ttorni.cpp \
        $$PWD/../Game/towers/wainola.cpp \
        $$PWD/../Game/mainwindow.cpp \
        $$PWD/../Game/dialoginfo.cpp \
        $$PWD/../Game/dialogstart.cpp \
        $$PWD/../Game/player.cpp \
        $$PWD/../Course/CourseLib/buildings/buildingbase.cpp \
        $$PWD/../Course/CourseLib/buildings/headquarters.cpp \
        $$PWD/../Course/CourseLib/buildings/outpost.cpp \
        $$PWD/../Course/CourseLib/buildings/farm.cpp \
        $$PWD/../Course/CourseLib/tiles/grassland.cpp \
        $$PWD/../Course/CourseLib/graphics/simplemapitem.cpp \
        $$PWD/../Course/CourseLib/graphics/simplegamescene.cpp \
        $$PWD/../Course/CourseLib/tiles/forest.cpp \
        $$PWD/../Course/CourseLib/tiles/tilebase.cpp \
        $$PWD/../Course/CourseLib/workers/basicworker.cpp \
        $$PWD/../Course/CourseLib/workers/workerbase.cpp \
        $$PWD/../Course/CourseLib/core/placeablegameobject.cpp \
        $$PWD/../Course/CourseLib/core/worldgenerator.cpp \
        $$PWD/../Course/CourseLib/core/coordinate.cpp \
        $$PWD/../Course/CourseLib/core/playerbase.cpp \
        $$PWD/../Course/CourseLib/core/gameobject.cpp \
        $$PWD/../Course/CourseLib/core/basicresources.cpp \

FORMS += \
        $$PWD/../Game/mainwindow.ui \
        $$PWD/../Game/dialoginfo.ui \
        $$PWD/../Game/dialogstart.ui \
        $$PWD/../Game/mapwindow.ui
