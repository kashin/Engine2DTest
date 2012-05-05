CONFIG += link_pkgconfig
PKGCONFIG += libIrrlicht

LIBS += -lIrrlicht

SOURCES += main.cpp \
    eventreceiver.cpp

HEADERS += \
    eventreceiver.h
