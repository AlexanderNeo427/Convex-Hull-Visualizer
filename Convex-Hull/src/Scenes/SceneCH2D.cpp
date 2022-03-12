#include "SceneCH2D.h"
#include "../Convex-Hull/JarvisMarch2D.h"

SceneCH2D::SceneCH2D(std::shared_ptr<SceneManager> pSceneManager, 
					 const std::string& sceneID, 
					 const int width, 
					 const int height)
	:
	IScene(pSceneManager, sceneID, width, height),
	m_targetTimestep(0.f), m_timeElapsed(0.f)
{}

void SceneCH2D::OnInitialize()
{
	this->RegeneratePoints(50);
	m_ch2D = std::make_shared<JarvisMarch2D>();
}

void SceneCH2D::OnUpdate(const float deltaTime)
{
	m_timeElapsed += deltaTime;
	if (m_timeElapsed >= m_targetTimestep)
	{
		m_timeElapsed = 0.f;

		if (m_animFrameQueue.empty())
			m_pAnimFrame = nullptr;
		else
		{
			m_pAnimFrame = m_animFrameQueue.front();
			m_animFrameQueue.pop();
		}
	}
}

void SceneCH2D::OnRender()
{
	if (m_pAnimFrame == nullptr)
	{
		for (int i = 0; i < m_hullIndices.size(); i++)
		{
			const int nextIdx = (i == m_hullIndices.size() - 1) ? 0 : (i + 1);
			const glm::vec2& p1 = m_allPoints[m_hullIndices[i]];
			const glm::vec2& p2 = m_allPoints[m_hullIndices[nextIdx]];
			DrawLine(p1.x, p1.y, p2.x, p2.y, raylib::Color::Yellow());
		}
		for (const glm::vec2& p : m_allPoints)
		{
			DrawCircle(p.x, p.y, 3.f, raylib::Color::Green());
		}
	}
	else
	{
		m_pAnimFrame->OnRender(m_allPoints, m_hullIndices);
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
		const Ch2DOutput out = m_ch2D->Compute(m_allPoints);
		m_hullIndices = out.hullIndices;
		m_animFrameQueue = out.animQueue;
		break;
	}
	case Event::TYPE::SET_TIMESTEP:
	{
		m_targetTimestep = event.setTimeStepData.timeStep;
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
	m_animFrameQueue = {};
	m_allPoints.clear();
	m_hullIndices.clear();

	const float width = static_cast<float>(Width());
	const float height = static_cast<float>(Height());
	const glm::vec2 center(width * 0.5f, height * 0.5f);
	const float maxLen = glm::min(width, height) * 0.5f * 0.725f;

	for (int i = 0; i < numPoints; i++)
	{
		const glm::vec2& point = center + glm::diskRand(maxLen);
		m_allPoints.emplace_back(point);

		auto anim = std::make_shared<GenPoint2D>(i);
		m_animFrameQueue.push(anim);
	}
}
