#ifndef _MODE_2D_STATES_
#define _MODE_2D_STATES_

#include "FiniteStateMachine.h"
#include "../StateEnums.h"
#include "Mode2DContext.h"

class Mode2D_Idle : public FSM::State<MODE_STATE> 
{
public:
	explicit Mode2D_Idle(std::shared_ptr<FSM::StateMachine<MODE_STATE>> pOwner,
						 std::shared_ptr<Mode2DContext> pContext)
		:
		FSM::State<MODE_STATE>(MODE_STATE::IDLE, "Idle", pOwner),
		m_pContext(std::move(pContext))
	{};
private:
	FSM::StateMachine<MODE_STATE> m_pOwner;
	std::shared_ptr<Mode2DContext> m_pContext;
};
//================================================================================================
class Mode2D_GenPts : public FSM::State<MODE_STATE>
{
public:
	explicit Mode2D_GenPts(std::shared_ptr<FSM::StateMachine<MODE_STATE>> pOwner,
						   std::shared_ptr<Mode2DContext> pContext)
		:
		FSM::State<MODE_STATE>(MODE_STATE::GEN_PTS, "Generating Points", pOwner),
		m_pContext(std::move(pContext))
	{};
private:
	FSM::StateMachine<MODE_STATE> m_pOwner;
	std::shared_ptr<Mode2DContext> m_pContext;
};
//================================================================================================
class Mode2D_ComputeCH : public FSM::State<MODE_STATE>
{
public:
	explicit Mode2D_ComputeCH(std::shared_ptr<FSM::StateMachine<MODE_STATE>> pOwner,
							  std::shared_ptr<Mode2DContext> pContext)
		:
		FSM::State<MODE_STATE>(MODE_STATE::COMPUTE_CH, "Computing Convex Hull", pOwner),
		m_pContext(std::move(pContext))
	{};
private:
	FSM::StateMachine<MODE_STATE> m_pOwner;
	std::shared_ptr<Mode2DContext> m_pContext;
};

#endif
