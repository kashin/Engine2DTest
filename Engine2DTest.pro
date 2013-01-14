QT -= gui
CONFIG += link_pkgconfig

LIBS += -L./ -lIrrlicht -llua52
INCLUDEPATH += ../irrlicht-1.7.3/include
INCLUDEPATH += ./include

SOURCES += main.cpp \
    eventreceiver.cpp \
    character.cpp \
    field.cpp \
    animator2d.cpp \
    movetoanimator2d.cpp \
    wallblock.cpp \
    graphicblock.cpp \
    actiongraphicitem.cpp \
    bullet.cpp \
    explosionanimation2d.cpp \
    basesprite.cpp \
    explosionspriteanimator2d.cpp \
    fieldnetblock.cpp

HEADERS += \
    eventreceiver.h \
    character.h \
    field.h \
    animator2d.h \
    movetoanimator2d.h \
    wallblock.h \
    graphicblock.h \
    actiongraphicitem.h \
    bullet.h \
    explosionanimation2d.h \
    basesprite.h \
    explosionspriteanimator2d.h \
    fieldnetblock.h

OTHER_FILES += \
    config.lua \
    generate_field.lua \
    TODO
