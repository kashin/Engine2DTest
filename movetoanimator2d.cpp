#include "movetoanimator2d.h"
#include "character.h"

#include <QDebug>

#define SKIP_FRAMES 100

MoveToAnimator2D::MoveToAnimator2D(Animator2D::AnimationType type,
                                   irr::core::vector2d<irr::s32> startPosition,
                                   irr::core::vector2d<irr::s32> moveToPosition,
                                   irr::s32 animationSpeed)
    : Animator2D(type),
      mFinished(false),
      mSkipFrames(SKIP_FRAMES),
      mAnimationSpeed(animationSpeed),
      mEndPostion(moveToPosition)
{
    // FIXME:  Argh, how to make appropriate speed vector???
    irr::core::vector2d<irr::s32> vec = (mEndPostion - startPosition);
    mSpeedVector = irr::core::vector2d<irr::s32>(vec.X > 0 ? animationSpeed : vec.X == 0 ? 0 : -1 *animationSpeed,
                                                 vec.Y > 0 ? animationSpeed : vec.Y == 0 ? 0 : -1 *animationSpeed);
}

void MoveToAnimator2D::runAnimation(GraphicBlock *graphicBlock)
{
    irr::core::vector2d<irr::s32> currentPosition = graphicBlock->position();
    if (currentPosition.equals(mEndPostion))
    {
        mFinished = true;
        return;
    }
    if (mSkipFrames > 0)
    {
        --mSkipFrames;
        return;
    }
    else
    {
        mSkipFrames = SKIP_FRAMES;
    }
    irr::core::vector2d<irr::s32> nextPosition(0,0);
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

    if ( ((currentPosition + mSpeedVector) >= mEndPostion &&
          (currentPosition < mEndPostion)) ||
         ((currentPosition + mSpeedVector) <= mEndPostion &&
                   (currentPosition > mEndPostion)))
    {
        graphicBlock->setPosition(mEndPostion);
        mFinished = true;
    }
    else
    {
        graphicBlock->setPosition(currentPosition + mSpeedVector);
    }
}

bool MoveToAnimator2D::animationFinished()
{
    return mFinished;
}
