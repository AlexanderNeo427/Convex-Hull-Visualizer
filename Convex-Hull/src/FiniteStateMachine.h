#ifndef FINITE_STATE_MACHINE
#define FINITE_STATE_MACHINE

#include <unordered_map>
#include <type_traits>
#include <string>

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
					   StateMachine<T>* owner)
			:
			m_stateID(stateID),
			m_name(name),
			m_owner(owner)
		{
			static_assert(std::is_enum<T>::value, "T must be of type enum");
		}

		virtual void OnEnter() = 0;
		virtual void OnUpdate(const float deltaTime) = 0;
		virtual void OnExit() = 0;

		void TransitState(const T& stateID) const { m_owner->TransitState(stateID); }
		T StateID() const { return m_stateID; }
		const std::string& Name() const { return m_name; }
	private:
		const T m_stateID;
		const std::string m_name;
		StateMachine<T>* m_owner;
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
			static_assert(std::is_enum<T>::value, "T must be of type enum");

			if (state == nullptr)
				return;

			m_allStates[state->StateID()] = state;
		}
		void TransitState(const T stateID)
		{
			static_assert(std::is_enum<T>::value, "T must be of type enum");

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
		State<T>* CurrentState() const { return m_currentState; }
	private:
		std::unordered_map<T, State<T>*> m_allStates;
		State<T>* m_currentState;
	};
}

#endif
