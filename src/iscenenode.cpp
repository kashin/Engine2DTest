#include "iscenenode.h"

#include <irrlicht/irrlicht.h>

ISceneNode::ISceneNode(ISceneNode *parent)
    : mParent(parent)
{
}

ISceneNode::~ISceneNode()
{
    irr::core::list< ISceneNode* >::Iterator it = mChilds.begin();
    irr::core::list< ISceneNode* >::Iterator end = mChilds.end();
    while(it != end) {
        delete (*it);
        ++it;
    }
    mChilds.clear();
}

void ISceneNode::draw()
{
    irr::core::list< ISceneNode* >::Iterator it = mChilds.begin();
    irr::core::list< ISceneNode* >::Iterator end = mChilds.end();
    while(it != end) {
        (*it)->draw();
        ++it;
    }
}

void ISceneNode::handleEvent(const irr::SEvent &/*event*/)
{
    // default Scene Node ignores events
}

ISceneNode *ISceneNode::getParent()
{
    return mParent;
}

void ISceneNode::setParent(ISceneNode *parent)
{
    if (mParent != parent) {
        if (mParent) {
            mParent->removeChildNode(this);
        }
        mParent = parent;
    }
}

void ISceneNode::appendChildNode(ISceneNode *node)
{
    if (!isSceneNodeAppended(node)) {
        node->setParent(this);
        mChilds.push_front(node);
    }
}

void ISceneNode::removeChildNode(ISceneNode *node)
{
    if (isSceneNodeAppended(node)) {
        irr::core::list< ISceneNode* >::Iterator it = mChilds.begin();
        irr::core::list< ISceneNode* >::Iterator end = mChilds.end();
        while(it != end) {
            if ( (*it) == node) {
                mChilds.erase(it);
                break;
            }
            ++it;
        }
    }
}

irr::u32 ISceneNode::getChildCount()
{
    return mChilds.size();
}

bool ISceneNode::isSceneNodeAppended(ISceneNode *node)
{
    bool result = false;
    irr::core::list< ISceneNode* >::Iterator it = mChilds.begin();
    irr::core::list< ISceneNode* >::Iterator end = mChilds.end();
    while(it != end) {
        if ( (*it) == node) {
            result = true;
            break;
        }
        ++it;
    }
    return result;
}
