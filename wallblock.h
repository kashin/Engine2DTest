#ifndef WALLBLOCK_H
#define WALLBLOCK_H

#include "graphicblock.h"

#include <irrString.h>
#include <vector2d.h>
#include <path.h>
#include <irrTypes.h>
#include <irrList.h>

namespace irr {
    namespace video {
        class ITexture;
        class IVideoDriver;
    }
}

class WallBlock: public GraphicBlock
{
public:
    explicit WallBlock(irr::video::IVideoDriver* driver, irr::core::vector2d<irr::s32> position,
                       const CollisionType& type = CanCollideType);
    ~WallBlock();

    virtual void draw();

private:
};

#endif // WALLBLOCK_H
