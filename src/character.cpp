#include "character.h"
#include "movetoanimator2d.h"
#include "bullet.h"
#include "actiongraphicitem.h"

#include <irrlicht.h>
#include <QDebug>

extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;

static unsigned int KEYMOVEPIXELS = 3;
#define ACTIONTEXTURENAME "data/MenuCircle.png"
#define SPRITE_TEXTURE_PATH "data/tank_sprite.jpg"
#define CHARACTER_TEXTURE_PATH "data/t90.jpg"

Character::Character(IVideoDriver *driver, const CollisionType& type)
    : GraphicBlock(driver, type),
      mLuaState(0),
      mShowMenu(false),
      mMenuActionsCount(0),
      mAnimationFPS(1),
      mCurrentAnimationFrame(0),
      mIsControlPressed(false)
{
    // getting some config values from config lua script
    mLuaState = luaL_newstate();
    if (!mLuaState)
        return;
    luaL_openlibs(mLuaState);

    if(luaL_dofile(mLuaState,"./data/config.lua"))
    {
        const char* err = lua_tostring(mLuaState, -1);
        qDebug() << err;
        return;
    }
    lua_getglobal(mLuaState, "keyMovePixels");
    KEYMOVEPIXELS = lua_tounsigned(mLuaState, -1);
    lua_getglobal(mLuaState, "characterActionsCount");
    mMenuActionsCount = lua_tonumber(mLuaState, -1);
}

Character::~Character()
{
    if (mLuaState)
    {
        lua_close(mLuaState);
    }
    mActionItems.clear();
}

void Character::draw()
{
    if (mDriver && texture())
    {
        if (mAnimationFPS == 1)
        {
            mDriver->draw2DImage(texture(), position() - (vector2d<s32>(texture()->getSize().Width/2, texture()->getSize().Height/2)));
        }
        else
        {
            if (mCurrentAnimationFrame == mAnimationFPS)
            {
                mCurrentAnimationFrame = 0;
            }
            if (mSpriteFrameRectangles.getSize() > mCurrentAnimationFrame)
            {
                irr::core::list< irr::core::rect<irr::s32> >::ConstIterator iter = mSpriteFrameRectangles.begin();
                iter += mCurrentAnimationFrame;
                mDriver->draw2DImage(texture(), getBoundRect(), *iter, 0, 0, true);
                ++mCurrentAnimationFrame;
            }
            else
            {
                mCurrentAnimationFrame = 0;
            }
        }
    }
    irr::core::list< GraphicBlock* >::Iterator it = mBullets.begin();
    irr::core::list< GraphicBlock* >::Iterator end = mBullets.end();
    irr::core::list< irr::core::list< GraphicBlock* >::Iterator> deleteBulletsList;
    while (it != end)
    {
        if ((*it)->animationsFinished())
        {
            deleteBulletsList.push_front(it);
            ++it;
            continue;
        }
        (*it)->drawAll();
        ++it;
    }
    irr::core::list< irr::core::list< GraphicBlock* >::Iterator>::Iterator iter = deleteBulletsList.begin();
    while (iter != deleteBulletsList.end())
    {
        delete *(*iter);
        mBullets.erase((*iter));
        ++iter;
    }

    if (mShowMenu)
    {
        drawMenu();
    }
}

void Character::drawMenu()
{
    s32 radius;
    radius = max_<s32>(getBoundRect().getWidth(), getBoundRect().getHeight());

    mDriver->draw2DPolygon(position(), radius,
                           SColor(255, 125, 80, 255), mMenuActionsCount);

    if (mMenuActionsCount != mActionItems.size())
    {
        //we are recreating all menu items, so let's remove the old one
        clearMenuActions();
        vector2d<s32> vertex;

        for (u32 i=0; i < mMenuActionsCount; ++i)
        {
            f32 p = i / (f32)mMenuActionsCount * (core::PI*2);
            vertex = position() +
                    position2d<s32>( (s32)(sin(p)*radius),
                                     (s32)(cos(p)*radius) );
            addMenuAction(vertex);
        }
    }
    irr::core::list< ActionGraphicItem* >::Iterator it = mActionItems.begin();
    irr::core::list< ActionGraphicItem* >::Iterator end = mActionItems.end();
    while (it != end)
    {
        (*it)->draw();
        ++it;
    }
}

void Character::addMenuAction(const vector2d<s32> &pos)
{
    ActionGraphicItem* item = new ActionGraphicItem(mDriver);
    item->setTextureName(ACTIONTEXTURENAME);
    item->setPosition(pos);
    mActionItems.push_front(item);
}

void Character::showMenu()
{
    if (!mShowMenu)
    {
        mShowMenu = true;
        enableAnimations(false);
        setSpriteAnimation(SPRITE_TEXTURE_PATH, 64, 64);

        irr::core::list< GraphicBlock* >::Iterator it = mBullets.begin();
        irr::core::list< GraphicBlock* >::Iterator end = mBullets.end();
        while (it != end)
        {
            (*it)->enableAnimations(false);
            ++it;
        }
    }
}

void Character::closeMenu()
{
    if (mShowMenu)
    {
        clearMenuActions();
        mShowMenu = false;
        enableAnimations(true);
        setFPS(1);
        setTextureName(CHARACTER_TEXTURE_PATH);

        irr::core::list< GraphicBlock* >::Iterator it = mBullets.begin();
        irr::core::list< GraphicBlock* >::Iterator end = mBullets.end();
        while (it != end)
        {
            (*it)->enableAnimations(true);
            ++it;
        }
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
        break;
    }
    case KEY_LCONTROL:
    {
        mIsControlPressed = event.KeyInput.PressedDown;
        break;
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
        if (!mShowMenu)
        {
            if (mIsControlPressed)
            {
                vector2d<s32> start = getBoundRect().getCenter() + vector2d<s32>(getBoundRect().getWidth(), 0);
                Bullet* bullet = new Bullet(mDriver, start,
                                            vector2d<s32>(event.MouseInput.X, event.MouseInput.Y),
                                            1, CanCollideType);
                mBullets.push_front(bullet);
            }
            else
            {
                MoveToAnimator2D* animator = new MoveToAnimator2D(Animator2D::MoveToAnimation, position(), vector2d<s32>(event.MouseInput.X, event.MouseInput.Y), 2);
                addAnimator(animator);
            }
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
    irr::core::list< ActionGraphicItem* >::Iterator it = mActionItems.begin();
    irr::core::list< ActionGraphicItem* >::Iterator end = mActionItems.end();
    while (it != end)
    {
        (*it)->newMouseEvent(event);
        ++it;
    }
}

void Character::clearMenuActions()
{
    if (!mActionItems.empty())
    {
        mActionItems.clear();
    }
}

void Character::setFPS(const unsigned int fps)
{
    if (fps > 0)
    {
        mAnimationFPS = fps;
        mCurrentAnimationFrame = 0;
    }
}

void Character::setSpriteAnimation(irr::io::path texturePath, irr::u32 frameWidth, irr::u32 frameHeight)
{
    mCurrentAnimationFrame = 0;
    mSpriteFrameRectangles.clear();
    setTextureName(texturePath);
    u32 textureWidth = texture()->getSize().Width;
    u32 textureHeight = texture()->getSize().Height;
    setTextureSize(frameWidth, frameHeight);

    mAnimationFPS = (textureWidth / frameWidth) * (textureHeight / frameHeight);

    for (u32 i = 0; i < textureHeight; i+= frameHeight)
    {
        for (u32 j = 0; j < textureWidth; j+= frameWidth)
        {
            mSpriteFrameRectangles.push_front(rect<s32>(j, i, j + frameWidth, i + frameHeight));
        }
    }
}
