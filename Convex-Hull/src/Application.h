#ifndef _APPLICATION_
#define _APPLICATION_

#include <raylib-cpp.hpp>
#include <memory>
#include <queue>

#include "FiniteStateMachine.h"
#include "Mode2D/Mode2D.h"
#include "Mode3D/Mode3D.h"
#include "StateEnums.h"

struct Application
{
private:
	static const int	   SCR_WIDTH  = 1250;
	static const int	   SCR_HEIGHT = 800;
	static constexpr float RT_AR	  = 0.9f;
public:
	void OnInitialize();
	void OnUpdate(const float deltaTime);
	void OnRender();
	void OnExit();

	const bool IsRunning() const { return !m_pWindow->ShouldClose(); }
private:
	std::unique_ptr<raylib::Window> m_pWindow;
	std::shared_ptr<FSM::StateMachine<APP_STATE>> m_pAppFSM;
	std::shared_ptr<raylib::RenderTexture2D> m_pRT2D;
	std::queue<std::shared_ptr<Event>> m_eventQueue;
	raylib::Rectangle m_viewportRect;
	float m_numPoints = 30.f;
};

#endif