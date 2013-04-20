#include "lineargesturerecognizer.h"
#include "gestureevent.h"

LinearGestureRecognizer::LinearGestureRecognizer()
{
}

LinearGestureRecognizer::~LinearGestureRecognizer()
{
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
