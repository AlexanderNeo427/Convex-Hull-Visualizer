#ifndef _MODE_3D_
#define _MODE_3D_

#include <raylib-cpp.hpp>

#include "FiniteStateMachine.h"
#include "../StateEnums.h"
#include "Mode3D_States.h"

class Mode3D : public FSM::State<APP_STATE>
{
public:
	explicit Mode3D(std::shared_ptr<FSM::StateMachine<APP_STATE>> pOwner,
					const int width, const int height)
		:
		FSM::State<APP_STATE>(APP_STATE::MODE_3D, "Mode 3D", pOwner)
	{
		m_pContext = std::make_shared<Mode3DContext>(width, height);

		m_pStateMachine = std::make_shared<FSM::StateMachine<MODE_STATE>>();
		m_pStateMachine->RegisterState(std::make_shared<Mode3D_Idle>(m_pStateMachine, m_pContext));
		m_pStateMachine->RegisterState(std::make_shared<Mode3D_GenPts>(m_pStateMachine, m_pContext));
		m_pStateMachine->RegisterState(std::make_shared<Mode3D_ComputeCH>(m_pStateMachine, m_pContext));
		m_pStateMachine->TransitState(MODE_STATE::IDLE);
	}

	void OnUpdate(const float deltaTime) override
	{
		m_pStateMachine->OnUpdate(deltaTime);
	};
	void OnRender() override
	{
		m_pStateMachine->OnRender();
	};
	void OnHandleEvent(std::shared_ptr<Event> evt) override
	{
		m_pStateMachine->OnHandleEvent(evt);
	};
private:
	std::shared_ptr<Mode3DContext> m_pContext;
	std::shared_ptr<FSM::StateMachine<MODE_STATE>> m_pStateMachine;
};

#endif
