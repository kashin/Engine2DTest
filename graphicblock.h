#ifndef GRAPHICBLOCK_H
#define GRAPHICBLOCK_H

#include "animator2d.h"

#include <irrlicht/vector2d.h>
#include <irrlicht/path.h>
#include <irrlicht/irrTypes.h>
#include <irrlicht/irrList.h>
#include <irrlicht/rect.h>

namespace irr {
    namespace video {
        class ITexture;
        class IVideoDriver;
    }
    class SEvent;
}

class GraphicBlock
{
public:
    enum CollisionType {
        CanCollideType = 0,
        CanNotCollideType
    };

    explicit GraphicBlock(irr::video::IVideoDriver* driver, const CollisionType& type = CanNotCollideType);
    ~GraphicBlock();

    const CollisionType& collisionType() const { return mCollisionType; }

    const irr::io::path textureName() const { return mTextureName; }
    void setTextureName(const irr::io::path& textureName);

    const irr::core::vector2d<irr::s32> position() const { return mCurrentPosition; }
    virtual void setPosition(irr::core::vector2d<irr::s32> position);

    virtual const irr::core::rect<irr::s32> getBoundRect() const;

    /** Adds new animator or replaces any previous animator
        with the same animation type.
        After this call GraphicBlock will free the Animator's memory when it is needed,
        so no need to free this memory manually.
      */
    void addAnimator(Animator2D* animator);

    virtual void draw();
    void drawAll();

    void enableAnimations(bool val);

    //! Handles new events like Mouse/Key clicked, moved, etc.
    void newEvent(const irr::SEvent& event);
    virtual void newKeyEvent(const irr::SEvent& event);
    virtual void newMouseEvent(const irr::SEvent& event);

    bool animationsFinished(Animator2D::AnimationType type = Animator2D::AllAnimations);

    irr::video::IVideoDriver* driver() { return mDriver; }

protected:
    const irr::video::ITexture* texture() const { return mTexture; }

    //! This will have effect on a bounded rect size, sprite animation, etc.
    void setTextureSize(irr::u32 width, irr::u32 height);

protected:
    irr::video::IVideoDriver* mDriver;

private:
    bool mEnableAnimation;
    irr::io::path mTextureName;
    irr::core::vector2d<irr::s32> mCurrentPosition;
    irr::video::ITexture* mTexture;
    irr::core::list<Animator2D*> mAnimations;
    CollisionType mCollisionType;
    irr::u32 mWidth;
    irr::u32 mHeight;
};

#endif // GRAPHICBLOCK_H
