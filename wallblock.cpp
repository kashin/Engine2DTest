#include "wallblock.h"

#include <irrlicht/irrlicht.h>


using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;

WallBlock::WallBlock(IVideoDriver* driver, vector2d<s32> position)
    : mDriver(driver),
      mTexture(0)
{
    setPosition(position);
}

WallBlock::~WallBlock()
{
    if (mTexture)
        delete mTexture;
}

void WallBlock::setTextureName(const path &textureName)
{
    mTextureName = textureName;
    if (mTexture)
    {
        delete mTexture;
        mTexture = 0;
    }
    if (mDriver)
        mTexture = mDriver->getTexture(mTextureName);
}

void WallBlock::setPosition(vector2d<s32> position)
{
    mCurrentPosition = position;
}

void WallBlock::draw()
{
    if (mTexture && mDriver)
    {
        mDriver->draw2DImage(mTexture, mCurrentPosition - (vector2d<s32>(mTexture->getSize().Width/2, mTexture->getSize().Height/2)));
    }
}
