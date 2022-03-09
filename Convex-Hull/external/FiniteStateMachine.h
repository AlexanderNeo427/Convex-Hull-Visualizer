#ifndef _FINITE_STATE_MACHINE_
#define _FINITE_STATE_MACHINE_

#include <unordered_map>
#include <type_traits>
#include <string>
#include <memory>

#include "Events.h"

namespace FSM
{
	template<class T>
	class StateMachine;

	template<class T>
	class State
	{
	public:
		explicit State(const T& stateID,
					   const std::string& name,
					   std::shared_ptr<FSM::StateMachine<T>> pOwner)
			:
			m_stateID(stateID),
			m_name(name),
			m_pOwner(std::move(pOwner))
		{
			static_assert(std::is_enum<T>::value, "T must be of type enum");
		}

		virtual void OnEnter() {};
		virtual void OnUpdate(const float deltaTime) {};
		virtual void OnRender() {};
		virtual void OnExit() {};
		virtual void OnHandleEvent(std::shared_ptr<Event> evt) {};

		void TransitState(const T& stateID) const { m_pOwner->TransitState(stateID); }
		T StateID() const { return m_stateID; }
		const std::string& Name() const { return m_name; }
	private:
		const T m_stateID;
		const std::string m_name;
		std::shared_ptr<FSM::StateMachine<T>> m_pOwner;
	};
}

namespace FSM
{
	template<class T>
	class StateMachine
	{
	public:
		explicit StateMachine()
			:
			m_allStates(),
			m_pCurrentState(nullptr),
			m_pNextState(nullptr)
		{}
		void OnUpdate(const float deltaTime)
		{
			if (m_pCurrentState != m_pNextState)
			{
				m_pCurrentState->OnExit();
				m_pCurrentState = m_pNextState;
				m_pCurrentState->OnEnter();
			}
			m_pCurrentState->OnUpdate(deltaTime);
		}
		void OnRender() { m_pCurrentState->OnRender(); }
		void RegisterState(std::shared_ptr<State<T>> state)
		{
			static_assert(std::is_enum<T>::value, "T must be of type enum");

			if (state == nullptr)
				return;

			m_allStates[state->StateID()] = state;
		}
		void TransitState(const T stateID)
		{
			static_assert(std::is_enum<T>::value, "T must be of type enum");

			std::shared_ptr<FSM::State<T>> nextState = m_allStates[stateID];

			if (m_pCurrentState == nullptr)
			{
				m_pNextState = m_pCurrentState = nextState;
				m_pCurrentState->OnEnter();
				return;
			}
			m_pNextState = nextState;
		}
		void OnHandleEvent(std::shared_ptr<Event> evt)
		{
			m_pCurrentState->OnHandleEvent(evt);
		}
		const std::string& CurrentStateName() const { return m_pCurrentState->Name(); }
	private:
		std::unordered_map<T, std::shared_ptr<FSM::State<T>>> m_allStates;
		std::shared_ptr<FSM::State<T>> m_pCurrentState;
		std::shared_ptr<FSM::State<T>> m_pNextState;
	};
}

#endif
