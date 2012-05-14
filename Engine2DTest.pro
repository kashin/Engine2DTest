QT -= gui
CONFIG += link_pkgconfig

LIBS += -lIrrlicht -llua5.2

SOURCES += main.cpp \
    eventreceiver.cpp \
    character.cpp \
    field.cpp \
    animator2d.cpp \
    movetoanimator2d.cpp \
    wallblock.cpp \
    graphicblock.cpp

HEADERS += \
    eventreceiver.h \
    character.h \
    field.h \
    animator2d.h \
    movetoanimator2d.h \
    wallblock.h \
    graphicblock.h

OTHER_FILES += \
    config.lua \
    generate_field.lua
