#ifndef CHARACTER_H
#define CHARACTER_H

#include <irrString.h>
#include <vector2d.h>
#include <path.h>
#include <irrTypes.h>

namespace irr {
    namespace video {
        class ITexture;
        class IVideoDriver;
    }
}

class Character
{
public:
    Character(irr::video::IVideoDriver* driver);
    ~Character();

    const irr::io::path textureName() const { return mTextureName; }
    void setTextureName(const irr::io::path& textureName);

    const irr::core::vector2d<irr::s32> getPosition() const { return mCurrentPosition; }
    void setPosition(irr::core::vector2d<irr::s32> position);

    virtual void draw();

protected:
    irr::video::IVideoDriver* mDriver;

private:
    irr::io::path mTextureName;
    irr::core::vector2d<irr::s32> mCurrentPosition;
    irr::video::ITexture* mTexture;
};

#endif // CHARACTER_H
