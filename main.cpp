#include <irrlicht.h>
#include "eventreceiver.h"
#include "field.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main()
{
        IrrlichtDevice * device = createDevice(EDT_OPENGL, core::dimension2d<u32>(1024, 768));

        if (device == 0)
                return 1; // could not create selected driver.

        /* The creation was successful, now we set the event receiver and
                store pointers to the driver and to the gui environment. */

        device->setWindowCaption(L"Irrlicht Engine - User Interface Demo");
        device->setResizable(true);

        video::IVideoDriver* driver = device->getVideoDriver();
//        scene::ISceneManager* scene = device->getSceneManager(); // we are always can show any 3D mesh with 2D graphic
        IGUIEnvironment* env = device->getGUIEnvironment();

        /*
        To make the font a little bit nicer, we load an external font
        and set it as the new default font in the skin.
        To keep the standard font for tool tip text, we set it to
        the built-in font.
        */

        IGUISkin* skin = env->getSkin();
        IGUIFont* font = env->getFont("../../media/fonthaettenschweiler.bmp");
        if (font)
                skin->setFont(font);

        skin->setFont(env->getBuiltInFont(), EGDF_TOOLTIP);

        /*
        We add three buttons. The first one closes the engine. The second
        creates a window and the third opens a file open dialog. The third
        parameter is the id of the button, with which we can easily identify
        the button in the event receiver.
        */

        env->addButton(rect<s32>(10,240,110,240 + 32), 0, GUI_ID_QUIT_BUTTON,
                        L"Quit", L"Exits Program");
        env->addButton(rect<s32>(10,280,110,280 + 32), 0, GUI_ID_NEW_WINDOW_BUTTON,
                        L"New Window", L"Launches a new Window");
        env->addButton(rect<s32>(10,320,110,320 + 32), 0, GUI_ID_FILE_OPEN_BUTTON,
                        L"File Open", L"Opens a file");

        /*
        Now, we add a static text and a scrollbar, which modifies the
        transparency of all gui elements. We set the maximum value of
        the scrollbar to 255, because that's the maximal value for
        a color value.
        Then we create an other static text and a list box.
        */

        env->addStaticText(L"Transparent Control:", rect<s32>(150,20,350,40), true);
        IGUIScrollBar* scrollbar = env->addScrollBar(true,
                        rect<s32>(150, 45, 350, 60), 0, GUI_ID_TRANSPARENCY_SCROLL_BAR);
        scrollbar->setMax(255);

        // set scrollbar position to alpha value of an arbitrary element
        scrollbar->setPos(env->getSkin()->getColor(EGDC_WINDOW).getAlpha());

        env->addStaticText(L"Logging ListBox:", rect<s32>(50,110,250,130), true);
        IGUIListBox * listbox = env->addListBox(rect<s32>(50, 140, 250, 210));
        env->addEditBox(L"Editable Text", rect<s32>(350, 80, 550, 100));

        // Store the appropriate data in a context structure.

        Field* field = new Field(driver);
        SAppContext context;
        context.device = device;
        context.counter = 0;
        context.listbox = listbox;
        context.field = field;

        // Then create the event receiver, giving it that context structure.
        EventReceiver receiver(context);

        // And tell the device to use our custom event receiver.
        device->setEventReceiver(&receiver);

        /*
        That's all, we only have to draw everything.
        */

        while(device->run() && driver)
        if (device->isWindowActive())
        {
                driver->beginScene(true, true, SColor(0,200,200,200));

                field->draw();
//                env->drawAll();

                driver->endScene();
        }

        context.field = 0;
        delete field;
        device->drop();

        return 0;
}
