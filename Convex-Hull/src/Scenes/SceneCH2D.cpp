#include "SceneCH2D.h"
#include "../Convex-Hull/ConvexHullAlgos.h"

// Actual implementations
#include "../Convex-Hull/JarvisMarch2D.h"
#include "../Convex-Hull/GrahamScan2D.h"

SceneCH2D::SceneCH2D(std::shared_ptr<SceneManager> pSceneManager, 
					 const std::string& sceneID, 
					 const int width, 
					 const int height)
	:
	IScene(pSceneManager, sceneID, width, height),
	m_state(STATE::IDLE),
	m_targetTimestep(0.f),
	m_timeElapsed(0.f),
	m_genPtsItr(0)
{}

void SceneCH2D::OnInitialize()
{
	RegeneratePoints(50);
	m_ch2D = std::make_shared<GrahamScan2D>();
}

void SceneCH2D::OnUpdate(const float deltaTime)
{
	if (m_state == STATE::ANIMATING)
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
}

void SceneCH2D::OnRender()
{
	switch (m_state)
	{
	case SceneCH2D::STATE::IDLE:
	{
		for (int i = 0; i < m_hullPoints.size(); i++)
		{
			const int nextIdx = (i == m_hullPoints.size() - 1) ? 0 : (i + 1);
			const glm::vec2& p1 = m_hullPoints[i];
			const glm::vec2& p2 = m_hullPoints[nextIdx];
			DrawLine(p1.x, p1.y, p2.x, p2.y, raylib::Color::Yellow());
		}
		for (const glm::vec2& p : m_allPoints)
		{
			DrawCircle(p.x, p.y, 3.f, raylib::Color::Green());
		}
		break;
	}
	case SceneCH2D::STATE::GEN_PTS:
	{
		if (m_genPtsItr >= m_allPoints.size() - 1)
		{
			OnEnterState(STATE::ANIMATING);
			break;
		}
		for (int i = 0; i < m_genPtsItr; i++)
		{
			const glm::vec2& p = m_allPoints[i];
			DrawCircle(p.x, p.y, 3.f, raylib::Color::Green());
		}
		m_genPtsItr++;
		break;
	}
	case SceneCH2D::STATE::ANIMATING:
	{
		if (m_pAnimFrame == nullptr)
		{
			OnEnterState(STATE::IDLE);
			break;
		}
		m_pAnimFrame->OnRender(m_allPoints, m_hullPoints);
		break;
	}
	default: break;
	}
}

void SceneCH2D::OnHandleEvent(const Event& event)
{
	switch (event.type)
	{
	case Event::TYPE::GEN_PTS:
	{
		RegeneratePoints(event.genPtsData.numPoints);
		OnEnterState(STATE::GEN_PTS);
		break;
	}
	case Event::TYPE::COMPUTE_CH:
	{
		if (m_state == STATE::GEN_PTS)
			break;

		m_animFrameQueue = {};
		const Ch2DOutput data = m_ch2D->Compute(m_allPoints);
		m_hullPoints = data.hullPoints;
		m_animFrameQueue = data.animQueue;
		OnEnterState(STATE::ANIMATING);
		break;
	}
	case Event::TYPE::SET_TIMESTEP:
	{
		m_targetTimestep = event.setTimeStepData.timeStep;
		break;
	}
	case Event::TYPE::SET_CH_ALGO:
		switch (event.setChAlgoData.algoType)
		{
		case CH_ALGO::JARVIS_MARCH: 
			m_ch2D = std::make_shared<JarvisMarch2D>();
			break;
		case CH_ALGO::GRAHAM_SCAN:
			m_ch2D = std::make_shared<GrahamScan2D>();
			break;
		}
	default: break;
	}
}

void SceneCH2D::RegeneratePoints(const int numPoints)
{
	m_animFrameQueue = {};
	m_allPoints.clear();
	m_hullPoints.clear();

	const float width = static_cast<float>(Width());
	const float height = static_cast<float>(Height());
	const glm::vec2 center(width * 0.5f, height * 0.5f);
	const float maxLen = glm::min(width, height) * 0.5f * 0.725f;

	for (int i = 0; i < numPoints; i++)
	{
		const glm::vec2& point = center + glm::diskRand(maxLen);
		m_allPoints.emplace_back(point);
	}
}

void SceneCH2D::OnEnterState(const STATE state)
{
	m_state = state;

	switch (state)
	{
	case SceneCH2D::STATE::IDLE: break;
	case SceneCH2D::STATE::GEN_PTS:
	{
		m_genPtsItr = 0;
		break;
	}
	case SceneCH2D::STATE::ANIMATING:
	{
		m_timeElapsed = 0.f;
		if (m_animFrameQueue.empty())
		{
			OnEnterState(STATE::IDLE);
			break;
		}
		m_pAnimFrame = m_animFrameQueue.front();
		m_animFrameQueue.pop();
		break;
	}
	default: break;
	}
}