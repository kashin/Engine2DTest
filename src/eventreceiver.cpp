#include "eventreceiver.h"
#include "engineapplication.h"
#include <irrlicht/irrlicht.h>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

EventReceiver::EventReceiver(SAppContext & context)
    : mContext(context)
{
}

EventReceiver::~EventReceiver()
{
}

bool EventReceiver::OnEvent(const SEvent &event)
{
    if (mContext.engineApplication)
    {
        return mContext.engineApplication->handleEvent(event);
    }
    return false;
}
