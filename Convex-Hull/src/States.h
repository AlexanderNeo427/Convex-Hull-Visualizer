#ifndef FSM_STATE_EXAMPLES
#define FSM_STATE_EXAMPLES

#include "FiniteStateMachine.h"

enum class DOOR { OPEN, OPENING, CLOSED, CLOSING };

struct StateOpen : public FSM::State<DOOR>
{
	StateOpen(FSM::StateMachine<DOOR>* owner)
		: 
		FSM::State<DOOR>(DOOR::OPEN, "Door is Open", owner) {}

	void OnEnter() override {}
	void OnUpdate(const float deltaTime) override 
	{
		if (IsKeyPressed(KEY_SPACE)) 
		{
			this->TransitState(DOOR::CLOSING);
		}
	}
	void OnExit() override {}
};

struct StateOpening : public FSM::State<DOOR>
{
	StateOpening(FSM::StateMachine<DOOR>* owner)
		:
		FSM::State<DOOR>(DOOR::OPENING, "Door opening...", owner) {}

	void OnEnter() override { m_timer = 0.f; }
	void OnUpdate(const float deltaTime) override 
	{
		m_timer += deltaTime;
 		if (m_timer >= 3.f)
			this->TransitState(DOOR::OPEN);
	}
	void OnExit() override {}
private:
	float m_timer = 0.f;
};

struct StateClosed : public FSM::State<DOOR>
{
	StateClosed(FSM::StateMachine<DOOR>* owner)
		:
		FSM::State<DOOR>(DOOR::CLOSED, "Door is closed", owner) {}

	void OnEnter() override {}
	void OnUpdate(const float deltaTime) override 
	{
		if (IsKeyPressed(KEY_SPACE))
		{
			this->TransitState(DOOR::OPENING);
		}
	}
	void OnExit() override {}
};

struct StateClosing : public FSM::State<DOOR>
{
	StateClosing(FSM::StateMachine<DOOR>* owner)
		:
		FSM::State<DOOR>(DOOR::CLOSING, "Door closing....", owner) {}

	void OnEnter() override { m_timer = 0.f; }
	void OnUpdate(const float deltaTime) override 
	{
		m_timer += deltaTime;
		if (m_timer >= 3.f)
			this->TransitState(DOOR::CLOSED);
	}
	void OnExit() override {}
private:
	float m_timer = 0.f;
};

#endif