TEMPLATE = app
TARGET = TheGame

QT += core gui widgets \
      multimedia

CONFIG += c++14

SOURCES += \
    bullets/basicbullet.cpp \
    bullets/bullet.cpp \
    bullets/moneybullet.cpp \
    bullets/secondary.cpp \
    bullets/toxicbullet.cpp \
    dialoginfo.cpp \
    dialogstart.cpp \
    enemies/basicenemy.cpp \
    enemies/enemybase.cpp \
    enemies/feministi.cpp \
    enemies/humanisti.cpp \
    enemies/raitsikka.cpp \
    enemies/tuniboss.cpp \
    main.cpp \
    mainwindow.cpp \
    managers/gameeventhandler.cc \
    managers/gameobjectmanager.cpp \
    managers/resourcemanager.cpp \
    managers/soundengine.cpp \
    player.cpp \
    tiles/buildingspace.cpp \
    towers/duo.cpp \
    towers/headquarter.cpp \
    towers/matriisit.cpp \
    towers/mikontalo.cpp \
    towers/towerbase.cpp \
    towers/ttorni.cpp \
    towers/wainola.cpp

HEADERS += \
    bullets/basicbullet.h \
    bullets/bullet.h \
    bullets/moneybullet.h \
    bullets/secondary.h \
    bullets/toxicbullet.h \
    dialoginfo.h \
    dialogstart.h \
    enemies/basicenemy.h \
    enemies/enemybase.h \
    enemies/feministi.h \
    enemies/humanisti.h \
    enemies/raitsikka.h \
    enemies/tuniboss.h \
    mainwindow.h \
    managers/gameeventhandler.h \
    managers/gameobjectmanager.h \
    managers/resourcemanager.h \
    managers/soundengine.h \
    player.h \
    tiles/buildingspace.h \
    towers/duo.h \
    towers/headquarter.h \
    towers/matriisit.h \
    towers/mikontalo.h \
    towers/towerbase.h \
    towers/ttorni.h \
    towers/wainola.h

win32:CONFIG(release, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/release/ -lCourseLib
else:win32:CONFIG(debug, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/debug/ -lCourseLib
else:unix: LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/ -lCourseLib

INCLUDEPATH += \
    $$PWD/../Course/CourseLib

DEPENDPATH += \
    $$PWD/../Course/CourseLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/libCourseLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/libCourseLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/CourseLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/CourseLib.lib
else:unix: PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/libCourseLib.a

FORMS += \
    dialoginfo.ui \
    dialogstart.ui \
    mainwindow.ui \
    mapwindow.ui

RESOURCES += \
    resources.qrc
