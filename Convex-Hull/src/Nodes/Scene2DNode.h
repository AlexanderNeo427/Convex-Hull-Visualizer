#ifndef SCENE_2D_NODE
#define SCENE_2D_NODE

#include "../Node.h"
#include <memory>

class Scene2DContext {};
class Scene2DNode : public Node
{
public:
    void OnInitialize() override {}
    void OnActivate() override {}
    void OnUpdate(const float deltaTime) override {}
    void OnDeactivate() override {}
private:
    Scene2DContext m_context;
};

#endif
