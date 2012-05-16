#include "character.h"
#include "movetoanimator2d.h"

#include <irrlicht/irrlicht.h>
#include <QDebug>

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

static unsigned int KEYMOVEPIXELS = 3;

Character::Character(IVideoDriver *driver, const CollisionType& type)
    : GraphicBlock(driver, type),
      mShowMenu(false),
      mMenuActionsCount(0),
      mMenuCircleTexture(0)
{

    // getting some config values from config lua script
    lua_State* luaState = luaL_newstate();
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
    lua_getglobal(luaState, "characterActionsCount");
    mMenuActionsCount = lua_tonumber(luaState, -1);

    lua_close(luaState);
}

Character::~Character()
{
    if (mMenuCircleTexture)
    {
        delete mMenuCircleTexture;
        mMenuCircleTexture = 0;
    }
}

void Character::draw()
{
    if (mDriver && texture())
    {
        mDriver->draw2DImage(texture(), position() - (vector2d<s32>(texture()->getSize().Width/2, texture()->getSize().Height/2)));
    }
    if (mShowMenu)
    {
        drawMenu();
    }
}

void Character::drawMenu()
{
    s32 radius = max_<s32>(texture()->getSize().Width, texture()->getSize().Height);

    mDriver->draw2DPolygon(position(), radius,
                           SColor(255, 125, 80, 255), mMenuActionsCount);
    if (mMenuCircleTexture == 0)
    {
        mMenuCircleTexture  = mDriver->getTexture("MenuCircle.png");
    }
    vector2d<s32> vertex;

    for (s32 i=0; i < mMenuActionsCount; ++i)
    {
        f32 p = i / (f32)mMenuActionsCount * (core::PI*2);
        vertex = position() +
                position2d<s32>( (s32)(sin(p)*radius),
                                 (s32)(cos(p)*radius) );
        drawMenuAction(vertex);
    }
}

void Character::drawMenuAction(const vector2d<s32> &pos)
{
    // FIXME: replace rect by vector2d.
    // I have no idea atm why draw2DImage with destPosition as a second argument is not working properly here,
    // so that's where that ugly hack came from :)
    s32 width = mMenuCircleTexture->getSize().Width;
    s32 height = mMenuCircleTexture->getSize().Height;
    mDriver->draw2DImage(mMenuCircleTexture, rect<s32>(pos.X - width/2, pos.Y - height/2, pos.X + width/2, pos.Y + height/2),
                         rect<s32>(0,0,width,height), 0, 0, true);
}

void Character::showMenu()
{
    if (!mShowMenu)
    {
        mShowMenu = true;
        enableAnimations(false);
    }
}

void Character::closeMenu()
{
    if (mShowMenu)
    {
        mShowMenu = false;
        enableAnimations(true);
    }
}

void Character::newKeyEvent(const irr::SEvent &event)
{
    switch(event.KeyInput.Key)
    {
    case KEY_LEFT:
    {
        if (event.KeyInput.PressedDown)
        {
            MoveToAnimator2D* animator = new MoveToAnimator2D(Animator2D::MoveToAnimation, position(),
                                                              position() + vector2d<s32>(-KEYMOVEPIXELS,0), 2);
            addAnimator(animator);
        }
        break;
    }
    case KEY_RIGHT:
    {
        if (event.KeyInput.PressedDown)
        {
            MoveToAnimator2D* animator = new MoveToAnimator2D(Animator2D::MoveToAnimation, position(),
                                                              position() + vector2d<s32>(KEYMOVEPIXELS,0), 2);
            addAnimator(animator);
        }
        break;
    }
    case KEY_UP:
    {
        if (event.KeyInput.PressedDown)
        {
            MoveToAnimator2D* animator = new MoveToAnimator2D(Animator2D::MoveToAnimation, position(),
                                                              position() + vector2d<s32>(0, -KEYMOVEPIXELS), 2);
            addAnimator(animator);
        }
        break;
    }
    case KEY_DOWN:
    {
        if (event.KeyInput.PressedDown)
        {
            MoveToAnimator2D* animator = new MoveToAnimator2D(Animator2D::MoveToAnimation, position(),
                                                              position() + vector2d<s32>(0, KEYMOVEPIXELS), 2);
            addAnimator(animator);
        }
        break;
    }
    case KEY_SPACE:
    {
        closeMenu();
    }
    default:
        break;
    }
}

void Character::newMouseEvent(const irr::SEvent &event)
{
    switch(event.MouseInput.Event)
    {
    case EMIE_LMOUSE_PRESSED_DOWN:
    {
        {
            MoveToAnimator2D* animator = new MoveToAnimator2D(Animator2D::MoveToAnimation, position(), vector2d<s32>(event.MouseInput.X, event.MouseInput.Y), 2);
            addAnimator(animator);
        }
        break;
    }
    case EMIE_RMOUSE_PRESSED_DOWN:
    {
        if (getBoundRect().isPointInside(vector2d<s32>(event.MouseInput.X, event.MouseInput.Y)))
        {
            showMenu();
        }
        else if (mShowMenu)
        {
            closeMenu();
        }
    }
    default:
        break;
    }
}
