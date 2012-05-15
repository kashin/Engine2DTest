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
    case EET_GUI_EVENT:
        {
            s32 id = event.GUIEvent.Caller->getID();
            IGUIEnvironment* env = mContext.device->getGUIEnvironment();

            switch(event.GUIEvent.EventType)
            {

        /*
                    If a scrollbar changed its scroll position, and it is
                    'our' scrollbar (the one with id GUI_ID_TRANSPARENCY_SCROLL_BAR), then we change
                    the transparency of all gui elements. This is a very
                    easy task: There is a skin object, in which all color
                    settings are stored. We simply go through all colors
                    stored in the skin and change their alpha value.
                    */
            case EGET_SCROLL_BAR_CHANGED:
                if (id == GUI_ID_TRANSPARENCY_SCROLL_BAR)
                {
                    s32 pos = ((IGUIScrollBar*)event.GUIEvent.Caller)->getPos();

                    for (u32 i=0; i<EGDC_COUNT ; ++i)
                    {
                        SColor col = env->getSkin()->getColor((EGUI_DEFAULT_COLOR)i);
                        col.setAlpha(pos);
                        env->getSkin()->setColor((EGUI_DEFAULT_COLOR)i, col);
                    }

                }
                break;

            /*
                    If a button was clicked, it could be one of 'our'
                    three buttons. If it is the first, we shut down the engine.
                    If it is the second, we create a little window with some
                    text on it. We also add a string to the list box to log
                    what happened. And if it is the third button, we create
                    a file open dialog, and add also this as string to the list box.
                    That's all for the event receiver.
                    */
            case EGET_BUTTON_CLICKED:
                switch(id)
                {
                case GUI_ID_QUIT_BUTTON:
                    mContext.device->closeDevice();
                    return true;

                case GUI_ID_NEW_WINDOW_BUTTON:
                {
                    mContext.listbox->addItem(L"Window created");
                    mContext.counter += 30;
                    if (mContext.counter > 200)
                        mContext.counter = 0;

                    IGUIWindow* window = env->addWindow(
                            rect<s32>(100 + mContext.counter, 100 + mContext.counter, 300 + mContext.counter, 200 + mContext.counter),
                            false, // modal?
                            L"Test window");

                    env->addStaticText(L"Please close me",
                                   rect<s32>(35,35,140,50),
                                   true,
                                   false,
                                   window);
                }
                    return true;

                case GUI_ID_FILE_OPEN_BUTTON:
                    mContext.listbox->addItem(L"File open");
                    env->addFileOpenDialog(L"Please choose a file.");
                    return true;

                default:
                    return false;
                }
                break;

            default:
                break;
            }
            break;
        }
    case EET_MOUSE_INPUT_EVENT:
        {
            switch(event.MouseInput.Event)
            {
                case EMIE_MOUSE_MOVED:
                    break;
                default:
                {
                    if (mContext.field)
                        mContext.field->newEvent(event);
                    return true;
                }
            }
            break;
        }
    case EET_KEY_INPUT_EVENT:
        {
            if (event.KeyInput.Key == KEY_ESCAPE)
            {
                mContext.device->closeDevice();
                return true;
            }
            else
            {
                if (mContext.field)
                    mContext.field->newEvent(event);
                return true;
            }
        }
    default:
         break;
    }
    return false;

}
