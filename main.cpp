#include "eventreceiver.h"
#include "field.h"

#include <irrlicht/irrlicht.h>

extern "C"
{
 #include <lua5.2/lua.h>
 #include <lua5.2/lualib.h>
 #include <lua5.2/lauxlib.h>
}


using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main()
{
    lua_State *luaState = luaL_newstate();
    if (!luaState)
        return 1;
    luaL_openlibs(luaState);

    if(luaL_dofile(luaState,"./config.lua"))
    {
       const char* err = lua_tostring(luaState, -1);
       printf("%s\n", err);
       return 2;
    }
    lua_getglobal(luaState, "windowWidth");
    u32 screenWidth = (u32)lua_tonumber(luaState, -1);
    lua_getglobal(luaState, "windowHeight");
    u32 screenHeight = (u32)lua_tonumber(luaState, -1);

    IrrlichtDevice * device = createDevice(EDT_OPENGL, core::dimension2d<u32>(screenWidth, screenHeight));

    lua_close(luaState);
    if (device == 0)
        return 3; // could not create selected driver.

    /* The creation was successful, now we set the event receiver and
                store pointers to the driver and to the gui environment. */

    device->setWindowCaption(L"Irrlicht Engine Test");

    video::IVideoDriver* driver = device->getVideoDriver();
//    scene::ISceneManager* scene = device->getSceneManager(); // we are always can show any 3D mesh with 2D graphic
//    IGUIEnvironment* env = device->getGUIEnvironment();

    // Store the appropriate data in a context structure.

    Field& field = Field::createField(driver);
    SAppContext context;
    context.device = device;
    context.counter = 0;
    context.listbox = 0;
    context.field = &field;

    // Then create the event receiver, giving it that context structure.
    EventReceiver receiver(context);

    // And tell the device to use our custom event receiver.
    device->setEventReceiver(&receiver);

    while(device->run() && driver)
        if (device->isWindowActive())
        {
            driver->beginScene(true, true, SColor(0,200,200,200));

            field.draw();

            driver->endScene();
        }

    context.field = 0;
    Field::deleteField();
    device->drop();

    return 0;
}
