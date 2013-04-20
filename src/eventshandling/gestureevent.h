#ifndef GESTUREEVENT_H
#define GESTUREEVENT_H

#include "event.h"

class GestureEvent : public Event
{
public:
    enum Type {
        Linear = 0
    };

    GestureEvent(Type gestureType);

    Type getGestureType() { return mGestureType; }

private:
    Type mGestureType;
};

#endif // GESTUREEVENT_H
