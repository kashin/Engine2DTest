#ifndef EVENT_H
#define EVENT_H

#include <irrlicht/irrList.h>
#include <irrlicht/IEventReceiver.h>

class Event
{
public:
    enum Type {
        Gesture = 0,
        Combined
    };

    Event(Type type, irr::SEvent event);

    /**
     * @brief getType gets event's type-
     */
    Type getType() { return mType; }

    irr::SEvent getIrrEvent() { return mIrrEvent; }

private:
    Type mType;
    irr::SEvent mIrrEvent;
};

typedef irr::core::list<Event* > EventsList;

#endif // EVENT_H
