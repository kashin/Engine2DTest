#include "graphicblock.h"
#include "animator2d.h"
#include <irrlicht/irrlicht.h>
#include <QDebug>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;

GraphicBlock::GraphicBlock(IVideoDriver *driver, const CollisionType& type)
    : mDriver(0),
      mEnableAnimation(true),
      mTexture(0),
      mCollisionType(type),
      mWidth(0),
      mHeight(0)
{
    mDriver = driver;
    setPosition(vector2d<s32>(0,0));
}

GraphicBlock::~GraphicBlock()
{
    irr::core::list< Animator2D* >::ConstIterator it = mAnimations.begin();
    irr::core::list< Animator2D* >::ConstIterator end = mAnimations.end();
    while (it != end)
    {
        delete *it;
        ++it;
    }
}

void GraphicBlock::setTextureName(const path &textureName)
{
    mTextureName = textureName;
    if (mTexture)
    {
        mTexture = 0;
    }
    if (mDriver)
    {
        mTexture = mDriver->findTexture(mTextureName);
        if (!mTexture)
        {
            mTexture = mDriver->getTexture(mTextureName);
        }
        if (mTexture)
        {
            mWidth = mTexture->getSize().Width;
            mHeight = mTexture->getSize().Height;
        }
    }
}

void GraphicBlock::setPosition(vector2d<s32> position)
{
    mCurrentPosition = position;
}

void GraphicBlock::addAnimator(Animator2D *animator)
{
    irr::core::list< Animator2D* >::Iterator it = mAnimations.begin();
    irr::core::list< Animator2D* >::Iterator end = mAnimations.end();
    while (it != end)
    {
        if ((*it)->type() == animator->type())
        {
            delete (*it);
            mAnimations.erase(it);
            break;
        }
    }
    mAnimations.push_front(animator);
}

void GraphicBlock::drawAll()
{
    if (mEnableAnimation && !mAnimations.empty())
    {
        irr::core::list< Animator2D* >::Iterator it = mAnimations.begin();
        irr::core::list< Animator2D* >::Iterator end = mAnimations.end();
        irr::core::list< irr::core::list< Animator2D* >::Iterator> deleteAnimsList;
        while (it != end)
        {
            if ((*it)->animationFinished())
            {
                deleteAnimsList.push_front(it);
                ++it;
                continue;
            }
            (*it)->runAnimation(this);
            ++it;
        }
        irr::core::list< irr::core::list< Animator2D* >::Iterator>::Iterator iter = deleteAnimsList.begin();
        while (iter != deleteAnimsList.end())
        {
            delete *(*iter);
            mAnimations.erase((*iter));
            ++iter;
        }
    }
    draw();
}

void GraphicBlock::draw()
{
    if (mTexture && mDriver)
    {
        mDriver->draw2DImage(mTexture, mCurrentPosition - (vector2d<s32>(mWidth/2, mHeight/2)));
    }
}

const irr::core::rect<irr::s32> GraphicBlock::getBoundRect() const
{
    vector2d<s32> vect(mWidth/2, mHeight/2);
    return rect<irr::s32>(mCurrentPosition - vect,
                          mCurrentPosition + vect);
}


void GraphicBlock::newEvent(const irr::SEvent &event)
{
    switch(event.EventType)
    {
    case EET_MOUSE_INPUT_EVENT:
    {
        newMouseEvent(event);
        break;
    }
    case EET_KEY_INPUT_EVENT:
    {
        newKeyEvent(event);
    }
    default:
        break;
    }
}

void GraphicBlock::newKeyEvent(const irr::SEvent &/*event*/)
{
}

void GraphicBlock::newMouseEvent(const irr::SEvent &/*event*/)
{
}

void GraphicBlock::enableAnimations(bool val)
{
    mEnableAnimation = val;
}

void GraphicBlock::setTextureSize(irr::u32 width, irr::u32 height)
{
    mWidth = width;
    mHeight = height;
}
