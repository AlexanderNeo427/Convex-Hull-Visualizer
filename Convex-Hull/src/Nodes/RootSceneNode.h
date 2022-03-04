#ifndef ROOT_SCENE_NODE
#define ROOT_SCENE_NODE

#include "../Node.h"
#include "Scene2DNode.h"
#include "Scene3DNode.h"

struct RootSceneNode : public Node, public std::enable_shared_from_this<RootSceneNode>
{
    void OnInitialize() override 
    {
        this->AddChildNode<Scene2DNode>(shared_from_this());
        this->AddChildNode<Scene3DNode>(shared_from_this());
    }
    void OnActivate() override {}
    void OnUpdate(const float deltaTime) override {}
    void OnDeactivate() override {}
};

#endif
