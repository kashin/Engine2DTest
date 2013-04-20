#include "engineapplication.h"

#include "eventreceiver.h"
#include "field.h"

#include <irrlicht/irrlicht.h>

extern "C"
{
 #include <lua5.2/lua.h>
 #include <lua5.2/lualib.h>
 #include <lua5.2/lauxlib.h>
}

// Don't do this ever again... :)
using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
// end of "Don't do this ever again... :)"

EngineApplication::EngineApplication()
{
}

int EngineApplication::start()
{
    lua_State *luaState = luaL_newstate();
    if (!luaState)
        return 1;
    luaL_openlibs(luaState);

    if(luaL_dofile(luaState,"./data/config.lua"))
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

    SceneManager& sceneManager = SceneManager::createSceneManager(driver);
    SAppContext context;
    context.device = device;
    context.counter = 0;
    context.listbox = 0;
    context.sceneManager = &sceneManager;

    // Then create the event receiver, giving it that context structure.
    EventReceiver receiver(context);

    // And tell the device to use our custom event receiver.
    device->setEventReceiver(&receiver);

    u32 previousTime = device->getTimer()->getRealTime();
    while(device->run() && driver)
    {
        u32 currentTime = device->getTimer()->getRealTime();

        if (currentTime - previousTime < 17)
        {
            continue;
        }

        previousTime = currentTime;

        if (device->isWindowActive())
        {
            driver->beginScene(true, true, SColor(0,200,200,200));

            sceneManager.draw();

            driver->endScene();
        }
    }

    context.sceneManager = 0;
    SceneManager::deleteSceneManager();
    device->drop();

    return 0;
}
