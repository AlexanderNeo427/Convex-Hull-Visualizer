#include "SceneCH2D.h"

#include "../Convex-Hull/JarvisMarch2D.h"

SceneCH2D::SceneCH2D(std::shared_ptr<SceneManager> pSceneManager, 
					 const std::string& sceneID, 
					 const int width, 
					 const int height)
	:
	IScene(pSceneManager, sceneID, width, height)
{}

void SceneCH2D::OnInitialize()
{
	this->RegeneratePoints(30);

	// TODO: Initialize convex hull algorithm
}

void SceneCH2D::OnUpdate(const float deltaTime)
{
}

void SceneCH2D::OnRender()
{
	if (m_animFrameQueue.empty())
	{
		for (const glm::vec2& p : m_allPoints)
		{
			DrawCircle(p.x, p.y, 2.5f, raylib::Color::Green());
		}
	}
	else
	{
		m_animFrameQueue.front()->OnRender(m_allPoints, m_hullPoints);
		m_animFrameQueue.pop();
	}
}

void SceneCH2D::OnHandleEvent(const Event& event)
{
	switch (event.type)
	{
	case Event::TYPE::GEN_PTS:
	{
		this->RegeneratePoints(event.genPtsData.numPoints);
		break;
	}
	case Event::TYPE::COMPUTE_CH:
	{
		m_animFrameQueue = {};
		auto const &[hullPoints, animFrames] = m_ch2D->Compute(m_allPoints);
		m_hullPoints = hullPoints;
		m_animFrameQueue = animFrames;
		break;
	}
	case Event::TYPE::SET_CH_ALGO:
		break;
	default:
		break;
	}
}

void SceneCH2D::RegeneratePoints(const int numPoints)
{
	m_allPoints.clear();
	m_hullPoints.clear();

	const float width = static_cast<float>(Width());
	const float height = static_cast<float>(Height());
	const glm::vec2 center(width * 0.5f, height * 0.5f);
	const float maxLen = glm::min(width, height) * 0.5f * 0.75f;

	for (int i = 0; i < numPoints; i++)
	{
		const glm::vec2& point = center + glm::diskRand(maxLen);
		m_allPoints.emplace_back(point);
	}
}
