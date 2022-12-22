QT       += core gui statemachine

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Instruct CMake to run moc automatically when needed.

SOURCES += \
    model/src/counter.cpp \
    mon/src/gameboard.cpp \
    model/src/help.cpp \
    main.cpp \
    model/src/mainwindow.cpp \
    model/src/minetimer.cpp \
    model/src/settings.cpp \
    model/src/stats.cpp \
    mon/src/tile.cpp

HEADERS += \
    model/header/counter.h \
    mon/header/gameboard.h \
    model/header/help.h \
    model/header/mainwindow.h \
    model/header/minetimer.h \
    model/header/settings.h \
    model/header/stats.h \
    mon/header/tile.h

FORMS += \
    view/help.ui \
    view/mainwindow.ui \
    view/settings.ui \
    view/stats.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

copydata.commands = $(COPY_DIR) $$PWD/stats.json $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

RESOURCES += \
    resources/resources.qrc \

DISTFILES += \
    resources/images/explosion.png \
    resources/images/flag.png \
    resources/images/mine.png \
    resources/images/time.png \
    resources/resources.rc \
    resources/stylesheets/tilesheet.qss
