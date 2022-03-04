#ifndef SCENE_3D_NODE
#define SCENE_3D_NODE

#include "../Node.h"
#include <memory>

struct Scene3DContext {};

class Scene3DNode : public Node
{
public:
    void OnInitialize() override {}
    void OnActivate() override {}
    void OnUpdate(const float deltaTime) override {}
    void OnDeactivate() override {}
private:
    Scene3DContext m_context;
};

#endif
