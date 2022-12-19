QT       += core gui statemachine

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Instruct CMake to run moc automatically when needed.

SOURCES += \
    counter.cpp \
    gameboard.cpp \
    main.cpp \
    mainwindow.cpp \
    minetimer.cpp \
    settings.cpp \
    tile.cpp

HEADERS += \
    counter.h \
    gameboard.h \
    mainwindow.h \
    minetimer.h \
    settings.h \
    tile.h

FORMS += \
    mainwindow.ui \
    settings.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resources.qrc

DISTFILES += \
    resources/images/explosion.png \
    resources/images/flag.png \
    resources/images/mine.png \
    resources/images/tada.png \
    resources/images/time.png \
    resources/images/transparent.png \
    resources/images/wrong.png \
    resources/resources.rc \
    resources/stylesheets/tilesheet.qss
