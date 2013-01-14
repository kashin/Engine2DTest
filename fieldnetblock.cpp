#include "fieldnetblock.h"
#include <irrlicht.h>

FieldNetBlock::FieldNetBlock(irr::core::vector2d<irr::s32> position, const irr::video::SColor color,
                             irr::video::IVideoDriver *driver, const CollisionType &type)
    : GraphicBlock(driver, type),
      mBorderColor(color)
{
    setPosition(position);
}

FieldNetBlock::~FieldNetBlock()
{
}

void FieldNetBlock::draw()
{
    if (mDriver)
    {
        mDriver->draw2DRectangleOutline(getBoundRect(), mBorderColor);
    }
}

void FieldNetBlock::setBorderColor(const irr::video::SColor color)
{
    mBorderColor = color;
}

void FieldNetBlock::setBlockSizes(irr::core::dimension2d<irr::u32> blockSizes)
{
    setTextureSize(blockSizes.Width, blockSizes.Height);
}
