#ifndef EVENTRECEIVER_H
#define EVENTRECEIVER_H

#include <irrlicht/IEventReceiver.h>

namespace irr {
    class IrrlichtDevice;
    namespace gui {
        class IGUIListBox;
    }
}

class Field;
// Declare a structure to hold some context for the event receiver so that it
// has it available inside its OnEvent() method.

struct SAppContext
{
        irr::IrrlichtDevice* device;
        irr::s32 counter;
        irr::gui::IGUIListBox *listbox;
        Field* field;
};

// Define some values that we'll use to identify individual GUI controls.
enum
{
        GUI_ID_QUIT_BUTTON = 101,
        GUI_ID_NEW_WINDOW_BUTTON,
        GUI_ID_FILE_OPEN_BUTTON,
        GUI_ID_TRANSPARENCY_SCROLL_BAR
};

class EventReceiver : public irr::IEventReceiver
{
public:
        EventReceiver(SAppContext & context);
        ~EventReceiver();

        virtual bool OnEvent(const irr::SEvent& event);

private:
        SAppContext& mContext;
};

#endif // EVENTRECEIVER_H
