QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    airCraft.cpp \
    backWarShip.cpp \
    battleShip.cpp \
    battlecannon.cpp \
    cannonBall.cpp \
    carrierVessels.cpp \
    enemyWarShip.cpp \
    fightScene.cpp \
    frontWarShip.cpp \
    gameScene.cpp \
    grid.cpp \
    humanoidEnemy.cpp \
    levelMap.cpp \
    main.cpp \
    mainwindow.cpp \
    operationButton.cpp \
    quitMessageBox.cpp \
    skillButton.cpp \
    standardEnemy.cpp \
    startScene.cpp \
    warShip.cpp

HEADERS += \
    airCraft.h \
    backWarShip.h \
    battleShip.h \
    battlecannon.h \
    cannonBall.h \
    carrierVessels.h \
    enemyWarShip.h \
    fightScene.h \
    frontWarShip.h \
    gameScene.h \
    grid.h \
    humanoidEnemy.h \
    levelMap.h \
    mainwindow.h \
    operationButton.h \
    quitMessageBox.h \
    skillButton.h \
    standardEnemy.h \
    startScene.h \
    warShip.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    logo.rc

RC_FILE+=logo.rc


