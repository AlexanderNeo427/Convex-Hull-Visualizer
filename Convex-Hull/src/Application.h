#ifndef APPLICATION
#define APPLICATION

#include <raylib-cpp.hpp>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#undef RAYGUI_IMPLEMENTATION

#include <memory>
#include "States.h"

struct Application
{
public:
	void OnInitialize() 
	{
		m_window = std::make_unique<raylib::Window>(1200, 850, "Test window");
		m_window->SetTargetFPS(120);

		m_stateMachine = new FSM::StateMachine<DOOR>();
		m_stateMachine->AddState(new StateOpen(m_stateMachine));
		m_stateMachine->AddState(new StateOpening(m_stateMachine));
		m_stateMachine->AddState(new StateClosed(m_stateMachine));
		m_stateMachine->AddState(new StateClosing(m_stateMachine));
		m_stateMachine->TransitState(DOOR::OPEN);
	}
	void OnUpdate(const float deltaTime)
	{
		m_stateMachine->Update(deltaTime);
	}
	void OnRender()
	{
		auto name = m_stateMachine->CurrentState()->Name().c_str();

		BeginDrawing();
		{
			ClearBackground(raylib::Color::Black());
			DrawText(name, 100, 100, 50, raylib::Color::Green());
		}
		EndDrawing();
	}
	void OnExit() {}
	const bool IsRunning() const { return !m_window->ShouldClose(); }
private:
	FSM::StateMachine<DOOR>* m_stateMachine;
	std::unique_ptr<raylib::Window> m_window;
};

#endif