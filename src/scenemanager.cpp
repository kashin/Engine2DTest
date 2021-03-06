#include "scenemanager.h"
#include "character.h"
#include "wallblock.h"
#include "fieldnetblock.h"
#include "scene.h"
#include "eventshandling/lineargesturerecognizer.h"

#include <QDebug>
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

#define CHARACTER_TEXTURE_PATH "data/t90.jpg"
#define BACKGROUND_TEXTURE_PATH "data/background.jpg"

static SceneManager* manager = NULL;


// Wrapper to call from lua script to add a WallBlock
int l_addWallBlock(lua_State* luaState)
{
    path background = lua_tostring(luaState, -3);
    s32 x = lua_tonumber(luaState, -2);
    s32 y = lua_tonumber(luaState, -1);
    SceneManager::instance().addWallBlock(background, x, y);
    return 1;
}

// Wrapper to call from lua script. Sets a Character's position
int l_setCharacterPosition(lua_State* luaState)
{
    s32 x = lua_tonumber(luaState, -2);
    s32 y = lua_tonumber(luaState, -1);
    SceneManager::instance().setCharacterPosition(x, y);
    return 1;
}

SceneManager::SceneManager(IVideoDriver* driver)
    : mDriver(driver),
      mCurrentScene(0),
      mTexture(0)
{
    mCharacter = new Character(mDriver);
    mCharacter->setTextureName(CHARACTER_TEXTURE_PATH);
    setBackground(BACKGROUND_TEXTURE_PATH);
}


SceneManager & SceneManager::instance()
{
    return *manager;
}

SceneManager* SceneManager::createSceneManager(irr::video::IVideoDriver *driver)
{
    if (!manager)
    {
        manager = new SceneManager(driver);
        manager->init();
    }
    return manager;
}

void SceneManager::init()
{
    // Generating walls in lua script
    lua_State *luaState = luaL_newstate();
    if (!luaState)
        return;
    luaL_openlibs(luaState);

    // Pushing addWallBlock function to lua (so, now it is available in the script)
    // to generate level's walls.
    lua_register(luaState, "addWallBlock" , l_addWallBlock);
    // The same thing is for setCharacterPosition.
    lua_register(luaState, "setCharacterPosition" , l_setCharacterPosition);

    if(luaL_dofile(luaState,"./data/generate_field.lua"))
    {
        const char* err = lua_tostring(luaState, -1);
        qDebug() << err;
        return;
    }
    lua_close(luaState);
    luaState = 0;

    // Reading some config values here
    luaState = luaL_newstate();
    if (!luaState)
        return;
    if(luaL_dofile(luaState,"./data/config.lua"))
    {
       const char* err = lua_tostring(luaState, -1);
       printf("%s\n", err);
       return;
    }
    lua_getglobal(luaState, "blockWidth");
    mBlockSizes.Width = (u32)lua_tonumber(luaState, -1);
    lua_getglobal(luaState, "blockHeight");
    mBlockSizes.Height = (u32)lua_tonumber(luaState, -1);
    lua_close(luaState);

    addFieldNet();
}

void SceneManager::addFieldNet()
{
    if (mBlockSizes.Width == 0 && mBlockSizes.Height == 0)
    {
        qDebug() << "Ups, looks like some nasty is in mBlockSizes: " << mBlockSizes.Width << mBlockSizes.Height;
        return;
    }
    u32 horizontalPosition = mBlockSizes.Width / 2;
    for (u32 i = 0; i < mDriver->getScreenSize().Width / mBlockSizes.Width + 1;
         i++ , horizontalPosition += mBlockSizes.Width)
    {
        u32 verticalPosition = mBlockSizes.Height / 2;
        for (u32 j = 0; j < mDriver->getScreenSize().Height / mBlockSizes.Height + 1;
             j++ , verticalPosition += mBlockSizes.Height)
        {
            FieldNetBlock* netBlock =
                    new FieldNetBlock(vector2d<s32>(horizontalPosition, verticalPosition), SColor(0xFF, 0x00, 0xFF, 0x00),
                                      mDriver);
            netBlock->setBlockSizes(mBlockSizes);
            mFieldsNetGraphicBlocks.push_front(netBlock);
        }
    }
}

void SceneManager::deleteSceneManager()
{
    if (!manager)
        delete manager;
}

SceneManager::~SceneManager()
{
    if (mCharacter)
        delete mCharacter;
    if (!mGraphicBlocks.empty())
    {
        irr::core::list< GraphicBlock* >::Iterator it = mGraphicBlocks.begin();
        irr::core::list< GraphicBlock* >::Iterator end = mGraphicBlocks.end();
        while (it != end)
        {
            delete (*it);
            ++it;
        }
        mGraphicBlocks.clear();
    }
    if (!mFieldsNetGraphicBlocks.empty())
    {
        irr::core::list< GraphicBlock* >::Iterator it = mFieldsNetGraphicBlocks.begin();
        irr::core::list< GraphicBlock* >::Iterator end = mFieldsNetGraphicBlocks.end();
        while (it != end)
        {
            delete (*it);
            ++it;
        }
        mFieldsNetGraphicBlocks.clear();
    }
}

void SceneManager::draw()
{
    //Background
    mDriver->draw2DImage(mTexture, position2d<s32>(0,0));
    //Field's net
    if (!mFieldsNetGraphicBlocks.empty())
    {
        irr::core::list< GraphicBlock* >::Iterator it = mFieldsNetGraphicBlocks.begin();
        irr::core::list< GraphicBlock* >::Iterator end = mFieldsNetGraphicBlocks.end();
        while (it != end)
        {
            (*it)->drawAll();
            ++it;
        }
    }
    //All Graphic blocks (walls, etc.)
    if (!mGraphicBlocks.empty())
    {
        irr::core::list< GraphicBlock* >::Iterator it = mGraphicBlocks.begin();
        irr::core::list< GraphicBlock* >::Iterator end = mGraphicBlocks.end();
        while (it != end)
        {
            (*it)->drawAll();
            ++it;
        }
    }
    // Character
    mCharacter->drawAll();
}

bool SceneManager::handleEvent(const SEvent &event)
{
    if (mCharacter)
    {
        if (event.EventType == EET_MOUSE_INPUT_EVENT ||
                event.EventType == EET_KEY_INPUT_EVENT)
        {
            mCharacter->newEvent(event);
        }
    }
    return true;
}

void SceneManager::setBackground(const path& backgroundPath)
{
    if (mTexture)
    {
        mTexture = 0;
    }
    mBackgroundTexturePath = backgroundPath;
    if (mDriver)
    {
        mTexture = mDriver->findTexture(BACKGROUND_TEXTURE_PATH);
        if (!mTexture)
        {
            mTexture = mDriver->getTexture(BACKGROUND_TEXTURE_PATH);
        }
    }
}

void SceneManager::setCharacterPosition(const irr::s32 &xCoord, const irr::s32 &yCoord)
{
    if (mCharacter)
    {
        mCharacter->setPosition(vector2d<s32>(xCoord, yCoord));
    }
}

void SceneManager::addWallBlock(const irr::io::path &blocksBackground, const irr::s32 &xCoord,
                         const irr::s32 &yCoord)
{
    WallBlock* wallBlock = new WallBlock(mDriver, vector2d<s32>(xCoord, yCoord));
    wallBlock->setTextureName(blocksBackground);
    mGraphicBlocks.push_front(wallBlock);
}

bool SceneManager::isCollidedWithWall(const irr::core::rect<irr::s32>& objRect) const
{
    if (!mGraphicBlocks.empty())
    {
        irr::core::list< GraphicBlock* >::ConstIterator it = mGraphicBlocks.begin();
        irr::core::list< GraphicBlock* >::ConstIterator end = mGraphicBlocks.end();
        while (it != end)
        {
            if ((*it)->collisionType() == GraphicBlock::CanCollideType &&
                objRect.isRectCollided((*it)->getBoundRect()))
                return true;
            ++it;
        }
    }
    return false;
}

const GraphicBlock* SceneManager::isCollided(const irr::core::rect<irr::s32> &checkRect) const
{
    if (!mGraphicBlocks.empty())
    {
        irr::core::list< GraphicBlock* >::ConstIterator it = mGraphicBlocks.begin();
        irr::core::list< GraphicBlock* >::ConstIterator end = mGraphicBlocks.end();
        while (it != end)
        {
            if ((*it)->collisionType() == GraphicBlock::CanCollideType &&
                checkRect.isRectCollided((*it)->getBoundRect()))
                return (*it);
            ++it;
        }
    }
    if (mCharacter && mCharacter->collisionType() == GraphicBlock::CanCollideType &&
        checkRect.isRectCollided(mCharacter->getBoundRect()))
    {
        return mCharacter;
    }
    return 0;
}

void SceneManager::setCurrentScene(Scene *newScene)
{
    if ( mCurrentScene != newScene) {
        delete mCurrentScene;
        mCurrentScene = newScene;
    }
}
