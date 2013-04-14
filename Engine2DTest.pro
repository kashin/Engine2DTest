QT -= gui
CONFIG += link_pkgconfig

LIBS += -L./ -lIrrlicht -llua52
INCLUDEPATH += ../irrlicht-1.7.3/include
INCLUDEPATH += ./include

SOURCES += src/main.cpp \
    src/eventreceiver.cpp \
    src/character.cpp \
    src/field.cpp \
    src/animator2d.cpp \
    src/movetoanimator2d.cpp \
    src/wallblock.cpp \
    src/graphicblock.cpp \
    src/actiongraphicitem.cpp \
    src/bullet.cpp \
    src/explosionanimation2d.cpp \
    src/basesprite.cpp \
    src/explosionspriteanimator2d.cpp \
    src/fieldnetblock.cpp \
    src/engineapplication.cpp \
    src/eventshandling/igesturerecognizer.cpp \
    src/eventshandling/event.cpp \
    src/eventshandling/lineargesturerecognizer.cpp \
    src/eventshandling/gestureevent.cpp

HEADERS += \
    src/eventreceiver.h \
    src/character.h \
    src/field.h \
    src/animator2d.h \
    src/movetoanimator2d.h \
    src/wallblock.h \
    src/graphicblock.h \
    src/actiongraphicitem.h \
    src/bullet.h \
    src/explosionanimation2d.h \
    src/basesprite.h \
    src/explosionspriteanimator2d.h \
    src/fieldnetblock.h \
    src/engineapplication.h \
    src/eventshandling/igesturerecognizer.h \
    src/eventshandling/event.h \
    src/eventshandling/lineargesturerecognizer.h \
    src/eventshandling/gestureevent.h

OTHER_FILES += \
    data/* \
    TODO
