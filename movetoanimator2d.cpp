#include "field.h"
#include "movetoanimator2d.h"
#include "character.h"

#include <QDebug>

#define SKIP_FRAMES 30

MoveToAnimator2D::MoveToAnimator2D(Animator2D::AnimationType type,
                                   irr::core::vector2d<irr::s32> startPosition,
                                   irr::core::vector2d<irr::s32> moveToPosition,
                                   irr::s32 animationSpeed)
    : Animator2D(type),
      mFinished(false),
      mEndPostion(moveToPosition)
{
    // FIXME:  Argh, how to make appropriate speed vector???
    irr::core::vector2d<irr::s32> vec = (mEndPostion - startPosition);
    mSpeedVector = irr::core::vector2d<irr::s32>(vec.X > 0 ? animationSpeed : vec.X == 0 ? 0 : -1 *animationSpeed,
                                                 vec.Y > 0 ? animationSpeed : vec.Y == 0 ? 0 : -1 *animationSpeed);
}

MoveToAnimator2D::~MoveToAnimator2D()
{
}

void MoveToAnimator2D::runAnimation(GraphicBlock *graphicBlock)
{
    if (!graphicBlock)
    {
        // OUCH, grpahicBlock is 0, so let's finish this animation.
        qDebug() << Q_FUNC_INFO << "graphicBlock is 0!";
        finishAnimation(graphicBlock);
        return;
    }
    irr::core::vector2d<irr::s32> currentPosition = graphicBlock->position();
    if (currentPosition.equals(mEndPostion))
    {
        finishAnimation(graphicBlock);
        return;
    }

    irr::core::vector2d<irr::s32> nextPosition = currentPosition + mSpeedVector;
    if ((mSpeedVector.X != 0) && (((currentPosition.X + mSpeedVector.X >= mEndPostion.X ) &&
         (currentPosition.X < mEndPostion.X)) ||
        ((currentPosition.X > mEndPostion.X)&&
             (currentPosition.X + mSpeedVector.X <= mEndPostion.X))))
    {
        nextPosition.X = mEndPostion.X;
        mSpeedVector.X = 0;
    }

    if ((mSpeedVector.Y != 0) && (((currentPosition.Y + mSpeedVector.Y >= mEndPostion.Y ) &&
         (currentPosition.Y < mEndPostion.Y)) ||
        ((currentPosition.Y > mEndPostion.Y)&&
             (currentPosition.Y + mSpeedVector.Y <= mEndPostion.Y))))
    {
        nextPosition.Y = mEndPostion.Y;
        mSpeedVector.Y = 0;
    }

    const GraphicBlock* block = Field::instance().isCollided(graphicBlock->getBoundRect() + mSpeedVector);
    if (block == 0 || block == graphicBlock)
    {
        graphicBlock->setPosition(nextPosition);
    }
    else
    {
        finishAnimation(graphicBlock, true);
    }
}

bool MoveToAnimator2D::animationFinished()
{
    return mFinished;
}

void MoveToAnimator2D::finishAnimation(GraphicBlock */*graphicBlock*/, bool /*collided*/)
{
    mFinished = true;
}

void MoveToAnimator2D::setFinished(bool val)
{
    mFinished = val;
}
