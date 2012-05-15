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
static unsigned int KEYMOVEPIXELS = 3;

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

    // getting some config values from config lua script
    luaState = luaL_newstate();
    if (!luaState)
        return;
    luaL_openlibs(luaState);

    if(luaL_dofile(luaState,"./config.lua"))
    {
       const char* err = lua_tostring(luaState, -1);
       qDebug() << err;
       return;
    }
    lua_getglobal(luaState, "keyMovePixels");
    KEYMOVEPIXELS = lua_tounsigned(luaState, -1);

    lua_close(luaState);
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
        switch(event.EventType)
        {
        case EET_MOUSE_INPUT_EVENT:
        {
            switch(event.MouseInput.Event)
            {
            case EMIE_LMOUSE_PRESSED_DOWN:
                {
                    {
                        MoveToAnimator2D* animator = new MoveToAnimator2D(Animator2D::MoveToAnimation, mCharacter->position(), vector2d<s32>(event.MouseInput.X, event.MouseInput.Y), 2);
                        mCharacter->addAnimator(animator);
                    }
                    break;
                }
            case EMIE_RMOUSE_PRESSED_DOWN:
                {
                    mCharacter->newEvent(event);
                }
            default:
                break;
            }
            break;
        }
        case EET_KEY_INPUT_EVENT:
        {
            switch(event.KeyInput.Key)
            {
            case KEY_LEFT:
                {
                    if (event.KeyInput.PressedDown)
                    {
                        MoveToAnimator2D* animator = new MoveToAnimator2D(Animator2D::MoveToAnimation, mCharacter->position(),
                                                                      mCharacter->position() + vector2d<s32>(-KEYMOVEPIXELS,0), 2);
                        mCharacter->addAnimator(animator);
                    }
                    break;
                }
            case KEY_RIGHT:
                {
                    if (event.KeyInput.PressedDown)
                    {
                        MoveToAnimator2D* animator = new MoveToAnimator2D(Animator2D::MoveToAnimation, mCharacter->position(),
                                                                          mCharacter->position() + vector2d<s32>(KEYMOVEPIXELS,0), 2);
                        mCharacter->addAnimator(animator);
                    }
                    break;
                }
            case KEY_UP:
                {
                    if (event.KeyInput.PressedDown)
                    {
                        MoveToAnimator2D* animator = new MoveToAnimator2D(Animator2D::MoveToAnimation, mCharacter->position(),
                                                                          mCharacter->position() + vector2d<s32>(0, -KEYMOVEPIXELS), 2);
                        mCharacter->addAnimator(animator);
                    }
                    break;
                }
            case KEY_DOWN:
                {
                    if (event.KeyInput.PressedDown)
                    {
                        MoveToAnimator2D* animator = new MoveToAnimator2D(Animator2D::MoveToAnimation, mCharacter->position(),
                                                                          mCharacter->position() + vector2d<s32>(0, KEYMOVEPIXELS), 2);
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

bool Field::isCollided(const irr::core::rect<irr::s32>& objRect) const
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
