#ifndef _MODE2D_STATE_COMPUTING_CONVEX_HULL_
#define _MODE2D_STATE_COMPUTING_CONVEX_HULL_

#include "FiniteStateMachine.h"
#include "../StateEnums.h"
#include "Mode2DContext.h"

#include "Jarvis_March/JarvisMarch2D.h"

class Mode2D_ComputeCH : public FSM::State<MODE_STATE>
{
public:
	explicit Mode2D_ComputeCH(std::shared_ptr<FSM::StateMachine<MODE_STATE>> pOwner,
							  std::shared_ptr<Mode2DContext> pContext)
		:
		FSM::State<MODE_STATE>(MODE_STATE::COMPUTE_CH, "Computing Convex Hull", pOwner),
		m_pM2DCtx(std::move(pContext))
	{
		m_pCH2DAlgo = std::make_shared<FSM::StateMachine<CH2D>>();
		m_pCH2DAlgo->RegisterState(std::make_shared<JarvisMarch2D>(m_pCH2DAlgo, pContext));
		m_pCH2DAlgo->TransitState(CH2D::JARVIS_MARCH);
	};

	void OnEnter() override
	{
		if (m_pM2DCtx->allPoints.size() < 3)
		{
			this->TransitState(MODE_STATE::IDLE);
		}
	}
	void OnUpdate(const float deltaTime) override
	{
		m_pCH2DAlgo->OnUpdate(deltaTime);
	}
	void OnRender() override
	{
		m_pCH2DAlgo->OnRender();
	}
	void OnHandleEvent(std::shared_ptr<Event> evt) override
	{
	}
private:
	std::shared_ptr<FSM::StateMachine<CH2D>> m_pCH2DAlgo;
	std::shared_ptr<Mode2DContext> m_pM2DCtx;
	std::shared_ptr<Mode2DContext> m_pJm2DCtx;
};

#endif
