#ifndef _SCENE_CONVEX_HULL_2D_
#define _SCENE_CONVEX_HULL_2D_

#include <vector>
#include <queue>

#include <raylib-cpp.hpp>

#include <glm/gtc/random.hpp>
#include <glm/vec2.hpp>

#include "../Convex-Hull/IConvexHull.h"
#include "SceneSystem/SceneManager.h"
#include "../Utils.h"

class SceneCH2D : public IScene
{
private:
	enum class STATE
	{
		IDLE,
		GEN_PTS,
		ANIMATING
	};
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
	void RegeneratePoints(const int numPoints);
	void OnEnterState(const STATE state);
private:
	STATE m_state;

	std::vector<glm::vec2> m_allPoints;
	std::vector<glm::vec2> m_hullPoints;

	std::shared_ptr<IConvexHull2D> m_ch2D;
	std::queue<std::shared_ptr<IAnimFrame2D>> m_animFrameQueue;
	std::shared_ptr<IAnimFrame2D> m_pAnimFrame;

	float m_targetTimestep, m_timeElapsed;
	int m_genPtsItr;
};

#endif
