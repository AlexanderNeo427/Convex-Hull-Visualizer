#ifndef FINITE_STATE_MACHINE
#define FINITE_STATE_MACHINE

#include <unordered_map>
#include <type_traits>
#include <string>

/**
 * - StateFactory 
 *		- Call OnInitialize() when states are created
 * - Convert raw ptrs to smart ptrs
 * - EventSystems
 *		- States implement OnHandleEvent()
 *		- EventPropagator??
 */

namespace FSM
{
	template<class T> 
	class StateMachine;

	template<class T>
	class State
	{
	public:
		explicit State(const T stateID,
					   const std::string& name,
					   const StateMachine<T>* owner)
			:
			m_stateID(stateID),
			m_name(name),
			m_owner(owner)
		{
			static_assert(std::is_enum(T), "T must be of type enum");
		}

		virtual void OnInitialize() = 0;
		virtual void OnEnter() = 0;
		virtual void OnUpdate(const float deltaTime) = 0;
		virtual void OnExit() = 0;

		T StateID() const { return m_stateID; }
		const std::string& Name() const { return m_name; }
	private:
		const T m_stateID;
		const std::string m_name;
		const StateMachine<T>* m_owner;
	};
}

namespace FSM
{
	template<class T>
	class StateMachine
	{
	public:
		void Update(const float deltaTime)
		{
			m_currentState->OnUpdate(deltaTime);
		}
		void AddState(State<T>* state)
		{
			static_assert(std::is_enum(T), "T must be of type enum");

			if (state == nullptr)
				return;

			m_allStates[state->m_stateID()] = state;
		}
		void TransitState(const T& stateID)
		{
			static_assert(std::is_enum(T), "T must be of type enum");

			State<T>* nextState = m_allStates[stateID];

			if (m_currentState == nullptr)
			{
				m_currentState = nextState;
				m_currentState->OnEnter();
				return;
			}
			m_currentState->OnExit();
			m_currentState = nextState;
			m_currentState->OnEnter();
		}
	private:
		std::unordered_map<T, State<T>*> m_allStates;
		State<T>* m_currentState;
	};
}

namespace FSM
{
	template<class T>
	class StateFactory
	{
	};
}

#endif
