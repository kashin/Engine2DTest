#include "explosionanimation2d.h"
#include "graphicblock.h"
#include "explosionspriteanimator2d.h"
#include <QDebug>

ExplosionAnimation2D::ExplosionAnimation2D(Animator2D::AnimationType type,
                                           irr::core::vector2d<irr::s32> startPosition,
                                           irr::core::vector2d<irr::s32> moveToPosition,
                                           irr::s32 animationSpeed)
    : MoveToAnimator2D(type, startPosition, moveToPosition, animationSpeed)
{
}

void ExplosionAnimation2D::finishAnimation(GraphicBlock *graphicBlock, bool collided)
{
    if (collided)
    {
        ExplosionSpriteAnimator2D* anim = new ExplosionSpriteAnimator2D(graphicBlock->position(), graphicBlock->driver());
        graphicBlock->addAnimator(anim);
    }
    setFinished(true);
}
