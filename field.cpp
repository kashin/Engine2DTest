#include "field.h"
#include "character.h"
#include "wallblock.h"

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

#define CHARACTER_TEXTURE_PATH "t90.jpg"
#define BACKGROUND_TEXTURE_PATH "background.jpg"

static Field* field = NULL;


// Wrapper to call from lua script to add a WallBlock
int l_addWallBlock(lua_State* luaState)
{
    path background = lua_tostring(luaState, -3);
    s32 x = lua_tonumber(luaState, -2);
    s32 y = lua_tonumber(luaState, -1);
    Field::instance().addWallBlock(background, x, y);
    return 1;
}

// Wrapper to call from lua script. Sets a Character's position
int l_setCharacterPosition(lua_State* luaState)
{
    s32 x = lua_tonumber(luaState, -2);
    s32 y = lua_tonumber(luaState, -1);
    Field::instance().setCharacterPosition(x, y);
    return 1;
}

Field::Field(IVideoDriver* driver)
    : mDriver(driver),
      mTexture(0)
{
    mCharacter = new Character(mDriver);
    mCharacter->setTextureName(CHARACTER_TEXTURE_PATH);
    setBackground(BACKGROUND_TEXTURE_PATH);
}


Field & Field::instance()
{
    return *field;
}

Field & Field::createField(irr::video::IVideoDriver *driver)
{
    if (!field)
    {
        field = new Field(driver);
        field->init();
    }
    return *field;
}

void Field::init()
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

    if(luaL_dofile(luaState,"./generate_field.lua"))
    {
        const char* err = lua_tostring(luaState, -1);
        qDebug() << err;
        return;
    }
    lua_close(luaState);
}

void Field::deleteField()
{
    if (!field)
        delete field;
}

Field::~Field()
{
    if (mCharacter)
        delete mCharacter;
}

void Field::draw()
{
    mDriver->draw2DImage(mTexture, position2d<s32>(0,0));
    if (!mWallBlocks.empty())
    {
        irr::core::list< WallBlock* >::Iterator it = mWallBlocks.begin();
        irr::core::list< WallBlock* >::Iterator end = mWallBlocks.end();
        while (it != end)
        {
            (*it)->drawAll();
            ++it;
        }
    }
    mCharacter->drawAll();
}

void Field::newEvent(const SEvent &event)
{
    if (mCharacter)
    {
        // Remove this if statement if there is no other events received by
        // Field in the future.
        if (event.EventType == EET_MOUSE_INPUT_EVENT ||
                event.EventType == EET_KEY_INPUT_EVENT)
        {
            mCharacter->newEvent(event);
        }
    }
}

void Field::setBackground(const path& backgroundPath)
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

void Field::setCharacterPosition(const irr::s32 &xCoord, const irr::s32 &yCoord)
{
    if (mCharacter)
    {
        mCharacter->setPosition(vector2d<s32>(xCoord, yCoord));
    }
}

void Field::addWallBlock(const irr::io::path &blocksBackground, const irr::s32 &xCoord,
                         const irr::s32 &yCoord)
{
    WallBlock* wallBlock = new WallBlock(mDriver, vector2d<s32>(xCoord, yCoord));
    wallBlock->setTextureName(blocksBackground);
    mWallBlocks.push_front(wallBlock);
}

bool Field::isCollidedWithWall(const irr::core::rect<irr::s32>& objRect) const
{
    if (!mWallBlocks.empty())
    {
        irr::core::list< WallBlock* >::ConstIterator it = mWallBlocks.begin();
        irr::core::list< WallBlock* >::ConstIterator end = mWallBlocks.end();
        while (it != end)
        {
            if ((*it)->collisionType() == GraphicBlock::CanCollideType && objRect.isRectCollided((*it)->getBoundRect()))
                return true;
            ++it;
        }
    }
    return false;
}
