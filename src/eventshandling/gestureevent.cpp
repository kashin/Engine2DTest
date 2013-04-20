#include "gestureevent.h"

GestureEvent::GestureEvent(Type gestureType)
    : Event(Gesture),
      mGestureType(gestureType)
{
}
