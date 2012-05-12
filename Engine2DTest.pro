QT -= gui
CONFIG += link_pkgconfig

LIBS += -lIrrlicht -llua5.2

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

OTHER_FILES += \
    config.lua
