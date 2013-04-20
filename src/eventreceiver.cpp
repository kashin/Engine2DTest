#include "eventreceiver.h"
#include "field.h"
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
    switch(event.EventType)
    {
    case EET_MOUSE_INPUT_EVENT:
        {
            if (mContext.sceneManager)
                mContext.sceneManager->handleEvent(event);
            return true;
        }
    case EET_KEY_INPUT_EVENT:
        {
            if (event.KeyInput.Key == KEY_ESCAPE)
            {
                mContext.device->closeDevice();
            }
            else
            {
                if (mContext.sceneManager)
                    mContext.sceneManager->handleEvent(event);
            }
            return true;
        }
    default:
         break;
    }
    return false;

}
