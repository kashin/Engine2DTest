#include "character.h"

#include <irrlicht.h>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;

Character::Character(IVideoDriver *driver)
    : mDriver(driver),
      mTexture(0)
{
    setPosition(vector2d<s32>(0,0));
}

Character::~Character()
{
    if (mTexture)
        delete mTexture;
}

void Character::setTextureName(const path &textureName)
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

void Character::setPosition(vector2d<s32> position)
{
    if (mTexture)
        mCurrentPosition = position - (vector2d<s32>(mTexture->getSize().Width/2, mTexture->getSize().Height/2));
    else
        mCurrentPosition = position;
}

void Character::draw()
{
    if (mTexture && mDriver)
        mDriver->draw2DImage(mTexture, mCurrentPosition);
}
