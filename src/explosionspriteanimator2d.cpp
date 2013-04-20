#include "explosionspriteanimator2d.h"
#include "basesprite.h"

#include <QDebug>

extern "C"
{
#include <lua5.2/lua.h>
#include <lua5.2/lualib.h>
#include <lua5.2/lauxlib.h>
}

#define EXPLOSION_TEXTURE_PATH "data/explosion_sprite.png"

ExplosionSpriteAnimator2D::ExplosionSpriteAnimator2D(irr::core::vector2d<irr::s32> position,
                                                     irr::video::IVideoDriver *driver)
    : Animator2D(ExplosionAnimation),
      mFinished(false),
      mPosition(position),
      mSprite(0)
{
    // getting some config values from config lua script
    lua_State* luaState = luaL_newstate();
    if (!luaState)
        return;
    luaL_openlibs(luaState);

    if(luaL_dofile(luaState,"./data/config.lua"))
    {
        return;
    }
    lua_getglobal(luaState, "explosionFrameWidth");
    irr::u32 frameWidth = lua_tounsigned(luaState, -1);
    lua_getglobal(luaState, "explosionFrameHeight");
    irr::u32 frameHeight = lua_tounsigned(luaState, -1);

    lua_close(luaState);

    mSprite = new BaseSprite(driver, position,
                             EXPLOSION_TEXTURE_PATH,
                             frameWidth, frameHeight);
}

void ExplosionSpriteAnimator2D::runAnimation(GraphicBlock */*graphicBlock*/)
{
    if (mSprite->stopped())
    {
        mFinished = true;
        return;
    }
    mSprite->draw();
}

bool ExplosionSpriteAnimator2D::animationFinished()
{
    return mFinished;
}
