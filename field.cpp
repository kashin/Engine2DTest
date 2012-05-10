#include "field.h"
#include "character.h"
#include "movetoanimator2d.h"

#include <irrlicht/irrlicht.h>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;

#define CHARACTER_TEXTURE_PATH "t90.jpg"
#define BACKGROUND_TEXTURE_PATH "background-porsche.jpg"

Field::Field(IVideoDriver* driver)
    : mDriver(driver),
      mTexture(0)
{
    mCharacter = new Character(mDriver);
    mCharacter->setTextureName(CHARACTER_TEXTURE_PATH);
    setBackground(BACKGROUND_TEXTURE_PATH);
}

Field::~Field()
{
    if (mTexture)
        delete mTexture;
    if (mCharacter)
        delete mCharacter;
}

void Field::draw()
{
    mDriver->draw2DImage(mTexture, position2d<s32>(0,0));
    mCharacter->draw();
}

void Field::newEvent(const SEvent &event)
{
    if (mCharacter)
    {
        switch(event.EventType)
        {
        case EET_MOUSE_INPUT_EVENT:
        {
            switch(event.MouseInput.Event)
            {
            case EMIE_LMOUSE_PRESSED_DOWN:
                {
                    {
                        MoveToAnimator2D* animator = new MoveToAnimator2D(Animator2D::MoveToAnimation, mCharacter->getPosition(), vector2d<s32>(event.MouseInput.X, event.MouseInput.Y), 150);
                        mCharacter->addAnimator(animator);
                    }
                    break;
                }
                default:
                    break;
            }
            break;
        }
        default:
            break;
        }
    }
}

void Field::setBackground(path backgroundPath)
{
    if (mTexture)
    {
        delete mTexture;
        mTexture = 0;
    }
    mBackgroundTexturePath = backgroundPath;
    if (mDriver)
        mTexture = mDriver->getTexture(BACKGROUND_TEXTURE_PATH);
}
