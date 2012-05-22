#ifndef BULLET_H
#define BULLET_H

#include "graphicblock.h"

class Bullet : public GraphicBlock
{
public:
    explicit Bullet(irr::video::IVideoDriver* driver,
                    irr::core::vector2d<irr::s32> startPoint,
                    irr::core::vector2d<irr::s32> moveTo,
                    irr::s32 speed,
                    const CollisionType& type = CanCollideType);

    virtual void draw();
};

#endif // BULLET_H
