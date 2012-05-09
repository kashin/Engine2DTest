CONFIG += link_pkgconfig
PKGCONFIG += libIrrlicht

LIBS += -lIrrlicht

SOURCES += main.cpp \
    eventreceiver.cpp \
    character.cpp \
    field.cpp

HEADERS += \
    eventreceiver.h \
    character.h \
    field.h
