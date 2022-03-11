#ifndef _MODE2D_STATE_GENERATING_POINTS_
#define _MODE2D_STATE_GENERATING_POINTS_

#include <glm/gtc/random.hpp>

#include "FiniteStateMachine.h"
#include "../StateEnums.h"
#include "Mode2DContext.h"

class Mode2D_GenPts : public FSM::State<MODE_STATE>
{
public:
	explicit Mode2D_GenPts(std::shared_ptr<FSM::StateMachine<MODE_STATE>> pOwner,
						   std::shared_ptr<Mode2DContext> pContext)
		:
		FSM::State<MODE_STATE>(MODE_STATE::GEN_PTS, "Generating Points", pOwner),
		m_pCtx(std::move(pContext))
	{};

	void OnEnter() override
	{
		m_pCtx->allPoints.clear();
		m_pCtx->hullPoints.clear();

		m_timeElapsed = 0.f;
		m_targetFrameTime = TARGET_GEN_PTS_TIME / m_pCtx->numPointsToGenerate;
	}
	void OnUpdate(const float deltaTime) override
	{
		if (m_pCtx->allPoints.size() >= m_pCtx->numPointsToGenerate)
		{
			this->TransitState(MODE_STATE::IDLE);
		}
		{
			m_timeElapsed += deltaTime;
			if (m_timeElapsed < m_targetFrameTime)
				return;
			m_timeElapsed = 0.f;
		}
		{
			const float rtWidth = static_cast<float>(m_pCtx->Width());
			const float rtHeight = static_cast<float>(m_pCtx->Height());
			const float control = glm::min(rtWidth, rtHeight) * 0.5f;
			const float maxLen = control * 0.8f;

			const glm::vec2 rtCenter(rtWidth * 0.5f, rtHeight * 0.5f);
			const glm::vec2 point = rtCenter + glm::diskRand(maxLen);
			m_pCtx->allPoints.emplace_back(point);
		}
	}
private:
	static constexpr float TARGET_GEN_PTS_TIME = 1.f; 

	std::shared_ptr<Mode2DContext> m_pCtx;

	float m_targetFrameTime = 0.f;
	float m_timeElapsed = 0.f;
};

#endif
