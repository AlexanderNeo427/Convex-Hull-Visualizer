#ifndef _JARVIS_MARCH_2D_
#define _JARVIS_MARCH_2D_

#include <vector>
#include <glm/vec2.hpp>
#include <raylib-cpp.hpp>

#include "FiniteStateMachine.h"
#include "../Mode2DContext.h"
#include "../../StateEnums.h"
#include "JM_STATES.h"
#include "JM2DContext.h"

class JarvisMarch2D : public FSM::State<CH2D>
{
public:
	explicit JarvisMarch2D(std::shared_ptr<FSM::StateMachine<CH2D>> pOwner, 
						   std::shared_ptr<Mode2DContext> pContext)
		:
		FSM::State<CH2D>(CH2D::JARVIS_MARCH, "Jarvis March", pOwner)
		// m_pCtx(std::move(pContext))
	{
		m_pJmStates = std::make_shared<FSM::StateMachine<JM_STATE>>();
		m_pJmStates->RegisterState(std::make_shared<FindLeftmostPoint>(m_pJmStates));
		m_pJmStates->TransitState(JM_STATE::FIND_LEFTMOST_POINT);
	}
	void OnUpdate(const float deltaTime) override
	{
		m_pJmStates->OnUpdate(deltaTime);
	}
	void OnRender() override
	{
		m_pJmStates->OnRender();
	}
private:
	std::shared_ptr<Mode2DContext> m_pM2D_Ctx;
	std::shared_ptr<FSM::StateMachine<JM_STATE>> m_pJmStates;
};

#endif
