#ifndef FIELDNETBLOCK_H
#define FIELDNETBLOCK_H

#include "graphicblock.h"
#include <SColor.h>

class FieldNetBlock : public GraphicBlock
{
public:
    FieldNetBlock(irr::core::vector2d<irr::s32> position, const irr::video::SColor color,
                  irr::video::IVideoDriver* driver, const CollisionType& type = CanNotCollideType);
    virtual ~FieldNetBlock();

    virtual void draw();

    void setBorderColor(const irr::video::SColor color);

    void setBlockSizes(irr::core::dimension2d<irr::u32> blockSizes);

private:
    irr::video::SColor mBorderColor;
};

#endif // FIELDNETBLOCK_H
