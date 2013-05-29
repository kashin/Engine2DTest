#include "event.h"

Event::Event(Type type, irr::SEvent event)
    : mType(type),
      mIrrEvent(event)
{
}
