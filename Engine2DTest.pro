CONFIG += link_pkgconfig
PKGCONFIG += libIrrlicht

LIBS += -lIrrlicht

SOURCES += main.cpp \
    eventreceiver.cpp \
    character.cpp \
    field.cpp \
    animator2d.cpp \
    movetoanimator2d.cpp

HEADERS += \
    eventreceiver.h \
    character.h \
    field.h \
    animator2d.h \
    movetoanimator2d.h
