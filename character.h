#ifndef CHARACTER_H
#define CHARACTER_H

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

class Animator2D;

class Character
{
public:
    Character(irr::video::IVideoDriver* driver);
    ~Character();

    const irr::io::path textureName() const { return mTextureName; }
    void setTextureName(const irr::io::path& textureName);

    virtual const irr::core::vector2d<irr::s32> getPosition() const { return mCurrentPosition; }
    virtual void setPosition(irr::core::vector2d<irr::s32> position);

    void addAnimator(Animator2D* animator);

    virtual void draw();

protected:
    irr::video::IVideoDriver* mDriver;

private:
    irr::io::path mTextureName;
    irr::core::vector2d<irr::s32> mCurrentPosition;
    irr::video::ITexture* mTexture;
    irr::core::list<Animator2D*> mAnimations;
};

#endif // CHARACTER_H
