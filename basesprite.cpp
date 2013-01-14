#include "basesprite.h"
#include <irrlicht.h>
#include <QDebug>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;

BaseSprite::BaseSprite(irr::video::IVideoDriver *driver,
                       irr::core::vector2d<irr::s32> position,
                       const irr::io::path &spriteTexturePath,
                       irr::u32 frameWidth,
                       irr::u32 frameHeight,
                       bool replay)
    : /*mPosition(position),*/
      mCurrentAnimationFrame(0),
      mFrameWidth(frameWidth),
      mFrameHeight(frameHeight),
      mReplay(replay),
      mStopped(false),
      mTexture(0),
      mDriver(driver)
{
    vector2d<s32> vect(frameWidth/2, frameHeight/2);
    mDestRect = rect<s32>(position - vect, position + vect);
    setTextureName(spriteTexturePath);

    if (!mTexture)
    {
        mStopped = true;
        return;
    }
    u32 textureWidth = mTexture->getSize().Width;
    u32 textureHeight = mTexture->getSize().Height;

    for (u32 i = 0; i < textureHeight; i+= frameHeight)
    {
        for (u32 j = 0; j < textureWidth; j+= frameWidth)
        {
            mSpriteFrameRectangles.push_front(rect<s32>(j, i, j + frameWidth, i + frameHeight));
        }
    }
}

BaseSprite::~BaseSprite()
{
}

void BaseSprite::draw()
{
    if (mSpriteFrameRectangles.getSize() > mCurrentAnimationFrame)
    {
        irr::core::list< irr::core::rect<irr::s32> >::ConstIterator iter = mSpriteFrameRectangles.begin();
        iter += mCurrentAnimationFrame;
        // FIXME: WTF??? draw2DImage() is not working with destPos argument!
        mDriver->draw2DImage(mTexture, mDestRect, *iter, 0, 0, true);
        ++mCurrentAnimationFrame;
        return;
    }

    if (mReplay)
    {
        mCurrentAnimationFrame = 0;
    }
    else
    {
        mStopped = true;
    }
}

void BaseSprite::setTextureName(const irr::io::path &textureName)
{
    if (mTexture)
    {
        mTexture = 0;
    }
    if (mDriver)
    {
        mTexture = mDriver->findTexture(textureName);
        if (!mTexture)
        {
            mTexture = mDriver->getTexture(textureName);
        }
    }
}

void BaseSprite::setReplay(bool replay)
{
    mReplay = replay;
}

