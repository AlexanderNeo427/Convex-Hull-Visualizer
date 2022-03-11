#ifndef _MODE_2D_
#define _MODE_2D_

#include <raylib-cpp.hpp>

#include "FiniteStateMachine.h"
#include "../StateEnums.h"

#include "Mode2D_Idle.h"
#include "Mode2D_GenPts.h"
#include "Mode2D_ComputeCH.h"

class Mode2D : public FSM::State<APP_STATE>
{
public:
	explicit Mode2D(std::shared_ptr<FSM::StateMachine<APP_STATE>> pOwner, 
					const int width, const int height)
		:
		FSM::State<APP_STATE>(APP_STATE::MODE_2D, "Mode 2D", pOwner)
	{
		m_pCtx = std::make_shared<Mode2DContext>(width, height);

		m_pStateMachine = std::make_shared<FSM::StateMachine<MODE_STATE>>();
		m_pStateMachine->RegisterState(std::make_shared<Mode2D_Idle>(m_pStateMachine, m_pCtx));
		m_pStateMachine->RegisterState(std::make_shared<Mode2D_GenPts>(m_pStateMachine, m_pCtx));
		m_pStateMachine->RegisterState(std::make_shared<Mode2D_ComputeCH>(m_pStateMachine, m_pCtx));
		m_pStateMachine->TransitState(MODE_STATE::IDLE);
	}
	void OnUpdate(const float deltaTime) override 
	{
		m_pStateMachine->OnUpdate(deltaTime);
	};
	void OnRender() override 
	{
		for (const glm::vec2& p : m_pCtx->allPoints)
		{
			DrawCircle(p.x, p.y, 3.f, raylib::Color::Green());
		}
		if (m_pCtx->hullPoints.size() >= 2)
		{
			for (int i = 0; i < m_pCtx->hullPoints.size(); i++)
			{
				const glm::vec2& p1 = m_pCtx->hullPoints[i];
				const glm::vec2& p2 = m_pCtx->hullPoints[i + 1];
				DrawLine(p1.x, p1.y, p2.x, p2.y, raylib::Color::RayWhite());
			}
		}
		m_pStateMachine->OnRender();
	};
	void OnHandleEvent(std::shared_ptr<Event> evt) override 
	{
		m_pStateMachine->OnHandleEvent(evt);
	};
private:
	std::shared_ptr<Mode2DContext> m_pCtx;
	std::shared_ptr<FSM::StateMachine<MODE_STATE>> m_pStateMachine;
};

#endif
