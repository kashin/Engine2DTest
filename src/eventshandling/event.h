#ifndef EVENT_H
#define EVENT_H

#include <irrlicht/irrList.h>

class Event
{
public:
    enum Type {
        Gesture = 0,
        Combined
    };

    Event(Type type);

    /**
     * @brief getType gets event's type-
     */
    Type getType() { return mType; }

private:
    Type mType;
};

typedef irr::core::list<Event* > EventsList;

#endif // EVENT_H
