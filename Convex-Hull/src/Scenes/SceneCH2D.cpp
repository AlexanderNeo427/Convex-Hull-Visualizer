#include "SceneCH2D.h"

SceneCH2D::SceneCH2D(std::shared_ptr<SceneManager> pSceneManager, 
					 const std::string& sceneID, 
					 const int width, 
					 const int height)
	:
	IScene(pSceneManager, sceneID, width, height)
{}

void SceneCH2D::OnInitialize()
{
	// Generate points
}

void SceneCH2D::OnUpdate(const float deltaTime)
{
}

void SceneCH2D::OnRender()
{
	if (m_animFrameQueue.empty())
	{
		// Draw as per normal
	}
	else
	{
		//m_animFrameQueue.front()->OnRender();
		m_animFrameQueue.pop();
	}
}

void SceneCH2D::OnHandleEvent(const Event& event)
{
	switch (event.type)
	{
	case Event::TYPE::GEN_PTS:
		break;
	default:
		break;
	}
}
