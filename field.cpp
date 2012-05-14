#include "field.h"
#include "character.h"
#include "movetoanimator2d.h"
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

int l_addWallBlock( lua_State* luaState)
{
   path background = lua_tostring(luaState, -3);
   s32 x = lua_tonumber(luaState, -2);
   s32 y = lua_tonumber(luaState, -1);
   field->addWallBlock(background, x, y);
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

    lua_State *luaState = luaL_newstate();
    if (!luaState)
        return;
    luaL_openlibs(luaState);

    lua_register(luaState, "addWallBlock" , l_addWallBlock);

    if(luaL_dofile(luaState,"./generate_field.lua"))
    {
       const char* err = lua_tostring(luaState, -1);
       qDebug() << err;
       return;
    }
}

void Field::deleteField()
{
    if (!field)
        delete field;
}

Field::~Field()
{
    if (mTexture)
        delete mTexture;
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
            (*it)->draw();
            ++it;
        }
    }
    mCharacter->draw();
}

void Field::newEvent(const SEvent &event)
{
    if (mCharacter)
    {
        switch(event.EventType)
        {
        case EET_MOUSE_INPUT_EVENT:
        {
            switch(event.MouseInput.Event)
            {
            case EMIE_LMOUSE_PRESSED_DOWN:
                {
                    {
                        MoveToAnimator2D* animator = new MoveToAnimator2D(Animator2D::MoveToAnimation, mCharacter->getPosition(), vector2d<s32>(event.MouseInput.X, event.MouseInput.Y), 150);
                        mCharacter->addAnimator(animator);
                    }
                    break;
                }
                default:
                    break;
            }
            break;
        }
        default:
            break;
        }
    }
}

void Field::setBackground(const path& backgroundPath)
{
    if (mTexture)
    {
        delete mTexture;
        mTexture = 0;
    }
    mBackgroundTexturePath = backgroundPath;
    if (mDriver)
        mTexture = mDriver->getTexture(BACKGROUND_TEXTURE_PATH);
}

void Field::addWallBlock(const irr::io::path &blocksBackground, const irr::s32 &xCoord,
                         const irr::s32 &yCoord)
{
    qDebug() << Q_FUNC_INFO << blocksBackground.c_str() << xCoord << yCoord;
    WallBlock* wallBlock = new WallBlock(mDriver, vector2d<s32>(xCoord, yCoord));
    wallBlock->setTextureName(blocksBackground);
    mWallBlocks.push_front(wallBlock);
}
