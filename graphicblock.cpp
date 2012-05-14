#include "graphicblock.h"
#include <irrlicht/irrlicht.h>
#include <QDebug>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;

GraphicBlock::GraphicBlock(IVideoDriver *driver)
    : mDriver(driver),
      mTexture(0)
{
    setPosition(vector2d<s32>(0,0));
}

GraphicBlock::~GraphicBlock()
{
    if (mTexture)
        delete mTexture;
}

void GraphicBlock::setTextureName(const path &textureName)
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

void GraphicBlock::setPosition(vector2d<s32> position)
{
    mCurrentPosition = position;
}

void GraphicBlock::draw()
{
    if (mTexture && mDriver)
    {
        mDriver->draw2DImage(mTexture, mCurrentPosition - (vector2d<s32>(mTexture->getSize().Width/2, mTexture->getSize().Height/2)));
    }
}

