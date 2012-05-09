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

//! This is a game field class.
/** This class handles some events and moves it to appropriate objects (like characters).
    It is some kind of a Scene manager. It draws all objects on the Game Field
  */
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
