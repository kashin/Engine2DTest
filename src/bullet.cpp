#include "bullet.h"
#include "explosionanimation2d.h"

#include "irrlicht/irrlicht.h"

#define BULLET_TEXTURE_PATH "data/bullet.png"

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

    ExplosionAnimation2D* anim = new ExplosionAnimation2D(Animator2D::FireToAnimation,
                                              position(), moveTo, speed);
    addAnimator(anim);
}

void Bullet::draw()
{
    if (texture() && mDriver && !animationsFinished(Animator2D::FireToAnimation) )
    {
        mDriver->draw2DImage(texture(), position());
    }
}
