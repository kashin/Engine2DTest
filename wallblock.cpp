#include "wallblock.h"

#include <irrlicht.h>


using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;

WallBlock::WallBlock(IVideoDriver* driver, vector2d<s32> position, const CollisionType& type)
    : GraphicBlock(driver, type)
{
    setPosition(position);
}

WallBlock::~WallBlock()
{
}

void WallBlock::draw()
{
    if (texture() && mDriver)
    {
        mDriver->draw2DImage(texture(), position() - (vector2d<s32>(texture()->getSize().Width/2, texture()->getSize().Height/2)));
    }
}
