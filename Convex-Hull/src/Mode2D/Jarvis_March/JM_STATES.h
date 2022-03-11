#ifndef _JARVIS_MARCH_STATES_
#define _JARVIS_MARCH_STATES_

#include <vector>
#include <glm/vec2.hpp>
#include <raylib-cpp.hpp>

#include "FiniteStateMachine.h"
#include "../Mode2DContext.h"
#include "../../StateEnums.h"
#include "JM2DContext.h"

struct FindLeftmostPoint : FSM::State<JM_STATE>
{
	explicit FindLeftmostPoint(std::shared_ptr<FSM::StateMachine<JM_STATE>> pOwner,
							   std::shared_ptr<Mode2DContext> pM2DContext, 
							   std::shared_ptr<JM2DContext> pJm2DContext)
		:
		FSM::State<JM_STATE>(JM_STATE::FIND_LEFTMOST_POINT, "Find leftmost point", pOwner),
		m_pM2DCtx(pM2DContext),
		m_pJm2DCtx(pJm2DContext),
		m_leftmostIdx(0), 
		m_currIdx(0)
	{}

	void OnUpdate(const float deltaTime) override
	{
		if (m_currIdx >= m_pM2DCtx->allPoints().size())
		{
			this->TransitState<JM_STATE>(JM_STATE::);
		}
	}
	void OnRender() override
	{
		const auto leftMostPt = m_pM2DCtx->allPoints[m_leftmostIdx];
		const auto currPt = m_pM2DCtx->allPoints[m_currIdx];

		DrawCircle(leftMostPt.x, leftMostPt.y, 5.f, raylib::Color::Red());
		DrawCircle(currPt.x, currPt.y, 5.f, raylib::Color::Green());
	}
private:
	std::shared_ptr<Mode2DContext> m_pM2DCtx;
	std::shared_ptr<JM2DContext> m_pJm2DCtx;

	int m_leftmostIdx;
	int m_currIdx;
};

#endif
