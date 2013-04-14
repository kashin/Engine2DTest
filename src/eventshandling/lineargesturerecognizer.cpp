#include "lineargesturerecognizer.h"
#include "gestureevent.h"

LinearGestureRecognizer::LinearGestureRecognizer()
{
}

LinearGestureRecognizer::~LinearGestureRecognizer()
{
    if (!mEventsList.empty()) {
        irr::core::list<irr::SEvent*>::ConstIterator it = mEventsList.begin();
        irr::core::list<irr::SEvent*>::ConstIterator end = mEventsList.end();
        while (it != end)
        {
            delete (*it);
            ++it;
        }
        mEventsList.clear();
    }
}

Event *LinearGestureRecognizer::handleScreenEvent(const irr::SEvent &event)
{
    Event* resultedEvent = 0;
    irr::SEvent* newSEvent = new irr::SEvent(event);
    if (newSEvent && newSEvent->EventType == irr::EET_MOUSE_INPUT_EVENT) {
        mEventsList.push_back(newSEvent);
        if (isGestureRecognized()) {
            resultedEvent = new GestureEvent(GestureEvent::Linear);
        }
    }
    return resultedEvent;
}

bool LinearGestureRecognizer::isGestureRecognized()
{
    bool result = false;
    return result;
}
