QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += core gui widgets

CONFIG += c++17

SOURCES += \
    ball.cpp \
    main.cpp \
    menuwindow.cpp \
    pongscene.cpp \
    pongwindow.cpp \
    racket.cpp \
    scoreboard.cpp

HEADERS += \
    ball.h \
    menuwindow.h \
    pongscene.h \
    pongwindow.h \
    racket.h \
    scoreboard.h

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
