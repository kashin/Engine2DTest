#ifndef SCENE_H
#define SCENE_H

#include "iscenenode.h"

class Scene: public ISceneNode
{
public:
    Scene(ISceneNode* parent = 0);
};

#endif // SCENE_H
