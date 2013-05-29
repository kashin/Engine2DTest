#include "gestureevent.h"

GestureEvent::GestureEvent(Type gestureType, irr::SEvent event)
    : Event(Gesture, event),
      mGestureType(gestureType)
{
}
