#ifndef GESTUREEVENT_H
#define GESTUREEVENT_H

#include "event.h"

class GestureEvent : public Event
{
public:
    enum Type {
        Linear = 0
    };

    GestureEvent(Type gestureType, irr::SEvent event);

    Type getGestureType() { return mGestureType; }

private:
    Type mGestureType;
};

#endif // GESTUREEVENT_H
