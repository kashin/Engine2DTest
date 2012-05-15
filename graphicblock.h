#ifndef GRAPHICBLOCK_H
#define GRAPHICBLOCK_H

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
}

class Animator2D;

class GraphicBlock
{
public:
    enum CollisionType {
        CanCollideType = 0,
        CanNotCollideType
    };

    GraphicBlock(irr::video::IVideoDriver* driver, const CollisionType& type = CanNotCollideType);
    ~GraphicBlock();

    const CollisionType& collisionType() const { return mCollisionType; }

    const irr::io::path textureName() const { return mTextureName; }
    void setTextureName(const irr::io::path& textureName);

    const irr::core::vector2d<irr::s32> position() const { return mCurrentPosition; }
    virtual void setPosition(irr::core::vector2d<irr::s32> position);

    virtual const irr::core::rect<irr::s32> getBoundRect() const;

    virtual void addAnimator(Animator2D* animator);
    virtual void draw();
    void drawAll();

protected:
    const irr::video::ITexture* texture() const { return mTexture; }

protected:
    irr::video::IVideoDriver* mDriver;

private:
    irr::io::path mTextureName;
    irr::core::vector2d<irr::s32> mCurrentPosition;
    irr::video::ITexture* mTexture;
    irr::core::list<Animator2D*> mAnimations;
    CollisionType mCollisionType;
};

#endif // GRAPHICBLOCK_H
