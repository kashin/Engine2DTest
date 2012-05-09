#ifndef FIELD_H
#define FIELD_H

#include <path.h>

namespace irr {
namespace video {
    class ITexture;
    class IVideoDriver;
}
    class SEvent;
}

class Character;

class Field
{
public:
    Field(irr::video::IVideoDriver* driver);
    ~Field();

    void newEvent(const irr::SEvent& event);
    virtual void draw();

    void setBackground(irr::io::path backgroundPath);

protected:
    irr::video::IVideoDriver* mDriver;

private:
    Character* mCharacter;
    irr::io::path mBackgroundTexturePath;
    irr::video::ITexture* mTexture;
};

#endif // FIELD_H
