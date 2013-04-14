#include "actiongraphicitem.h"

#include "irrlicht/irrlicht.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;

ActionGraphicItem::ActionGraphicItem(IVideoDriver* driver)
    : GraphicBlock(driver),
      mHighlighted(false)
{
}

ActionGraphicItem::~ActionGraphicItem()
{
}

void ActionGraphicItem::newMouseEvent(const irr::SEvent &event)
{
    if (getBoundRect().isPointInside(vector2d<s32>(event.MouseInput.X, event.MouseInput.Y)))
    {
        mHighlighted = true;
    }
    else
    {
        mHighlighted = false;
    }
}

void ActionGraphicItem::draw()
{
    // FIXME: replace rect by vector2d.
    // I have no idea atm why draw2DImage with destPosition as a second argument is not working properly here,
    // so that's where that ugly hack came from :)
    s32 width = texture()->getSize().Width;
    s32 height = texture()->getSize().Height;
    SColor* color = mHighlighted ? (new SColor(200,255,255,255) ) : 0 ;
    mDriver->draw2DImage(texture(),
                         rect<s32>(position().X - width/2, position().Y - height/2, position().X + width/2, position().Y + height/2),
                         rect<s32>(0,0,width,height), 0, color, true);
}
