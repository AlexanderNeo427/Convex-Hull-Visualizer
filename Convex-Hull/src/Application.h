#ifndef _APPLICATION_
#define _APPLICATION_

#include <raylib-cpp.hpp>
#include <memory>
#include <queue>

#include "Events.h"
#include "FiniteStateMachine.h"
#include "SceneSystem/SceneManager.h"

struct Application
{
private:
	static constexpr int   SCR_WIDTH  = 1300;
	static constexpr int   SCR_HEIGHT = 800;
	static constexpr float RT_AR	  = 0.8f;

	static constexpr int MIN_POINTS = 10;
	static constexpr int MAX_POINTS = 100;

	static constexpr float TIMESTEP_MIN = 0.f;
	static constexpr float TIMESTEP_MAX = 0.3f;
public:
	explicit Application();

	void OnInitialize();
	void OnUpdate();
	void OnRender();
	void OnExit();

	bool IsRunning() const { return !m_pWindow->ShouldClose(); }
private:
	std::unique_ptr<raylib::Window>	m_pWindow;
	std::shared_ptr<SceneManager> m_pSceneManager;
	std::shared_ptr<raylib::RenderTexture2D> m_pRT2D;
	std::queue<Event> m_eventQueue;
	raylib::Rectangle m_viewportRect;
private: 
	// GUI state
	int m_numPtsToGen;
	float m_targetTimestep;

	int m_dropdownChoice;
	bool m_isDropdownEditMode;
};

#endif