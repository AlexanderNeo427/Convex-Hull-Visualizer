#ifndef _MODE2D_STATE_IDLE_
#define _MODE2D_STATE_IDLE_

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
		m_pCtx(std::move(pContext))
	{};
	void OnHandleEvent(std::shared_ptr<Event> evt) override
	{
		auto genPtsEvt = std::dynamic_pointer_cast<GenPtsEvt>(evt);
		if (genPtsEvt != nullptr)
		{
			m_pCtx->numPointsToGenerate = genPtsEvt->NumPoints();
			this->TransitState(MODE_STATE::GEN_PTS);
		}
	}
private:
	std::shared_ptr<Mode2DContext> m_pCtx;
};

#endif
