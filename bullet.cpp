#include "bullet.h"
#include "movetoanimator2d.h"

#include "irrlicht/irrlicht.h"

#define BULLET_TEXTURE_PATH "bullet.png"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;

Bullet::Bullet(irr::video::IVideoDriver *driver,
               irr::core::vector2d<irr::s32> startPoint,
               vector2d<s32> moveTo,
               irr::s32 speed,
               const CollisionType &type)
    : GraphicBlock(driver, type)
{
    setPosition(startPoint);
    setTextureName(BULLET_TEXTURE_PATH);

    MoveToAnimator2D* anim = new MoveToAnimator2D(Animator2D::FireToAnimation,
                                              position(), moveTo, speed);
    addAnimator(anim);
}

void Bullet::draw()
{
    GraphicBlock::draw();
    if (animationsFinished())
    {
        // TODO: add explosion animation here :)
    }
}
