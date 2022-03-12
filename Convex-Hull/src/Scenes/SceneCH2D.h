#ifndef _SCENE_CONVEX_HULL_2D_
#define _SCENE_CONVEX_HULL_2D_

#include <queue>

#include "SceneSystem/SceneManager.h"
#include "../SceneContext.h"
#include "../IAnimFrame.h"

class SceneCH2D : public IScene
{
public:
	explicit SceneCH2D(std::shared_ptr<SceneManager> pSceneManager,
					   const std::string& sceneID,
					   const int width,
					   const int height);
	
	void OnInitialize() override;
	void OnUpdate(const float deltaTime) override;
	void OnRender() override;
	void OnHandleEvent(const Event& event) override;
private:
	std::queue<std::shared_ptr<IAnimFrame>> m_animFrameQueue;
};

#endif
