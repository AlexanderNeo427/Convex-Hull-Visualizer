#include "Application.h"

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#undef RAYGUI_IMPLEMENTATION

void Application::OnInitialize()
{
	// Initialize Window
	m_pWindow = std::make_unique<raylib::Window>(SCR_WIDTH, SCR_HEIGHT, "Convex Hull");
	m_pWindow->SetTargetFPS(120);

	// Initialize viewport rect 
	const float rtHeight = static_cast<float>(m_pWindow->GetHeight()) * 0.85f;
	const float rtWidth = rtHeight * RT_AR;
	const int posY = (m_pWindow->GetHeight() - rtHeight) / 2;
	const int posX = m_pWindow->GetWidth() - posY - rtWidth;
	m_viewportRect.SetPosition(posX, posY);
	m_viewportRect.SetWidth(rtWidth);
	m_viewportRect.SetHeight(rtHeight);

	// Initialize renderTexture
	m_pRT2D = std::make_shared<raylib::RenderTexture2D>();
	m_pRT2D->Load(static_cast<int>(rtWidth), static_cast<int>(rtHeight));

	// Initialize stateMachines + app states
	m_pAppFSM = std::make_shared<FSM::StateMachine<APP_STATE>>();
	m_pAppFSM->RegisterState(std::make_shared<Mode2D>(m_pAppFSM, rtWidth, rtHeight));
	m_pAppFSM->RegisterState(std::make_shared<Mode3D>(m_pAppFSM, rtWidth, rtHeight));
	m_pAppFSM->TransitState(APP_STATE::MODE_2D);
}

void Application::OnUpdate(const float deltaTime)
{
	while (!m_eventQueue.empty())
	{
		m_pAppFSM->OnHandleEvent(m_eventQueue.front());
		m_eventQueue.pop();
	}
	m_pAppFSM->OnUpdate(deltaTime);
}

void Application::OnRender()
{
	// Render current scene to mini-viewport
	m_pRT2D->BeginMode();
	{
		m_pWindow->ClearBackground(raylib::Color::Blank());
		m_pAppFSM->OnRender();
	}
	m_pRT2D->EndMode();

	m_pWindow->BeginDrawing();
	m_pWindow->ClearBackground(raylib::Color::Blank());
	{
		{
			// Render GUI elements
			m_numPoints = GuiSlider(Rectangle{ 30, 30, 250, 40 }, "", "", m_numPoints, 0.f, 100.f);
			if (GuiButton(Rectangle{ 30, 100, 180, 40 }, "Generate Points"))
			{
				auto genPtsEvt = std::make_shared<GenPtsEvt>(static_cast<int>(m_numPoints));
				m_eventQueue.push(genPtsEvt);
			}
		}
		{
			// Render viewport + bounds
			m_viewportRect.DrawLines(raylib::Color::White());
			DrawTexture(m_pRT2D->GetTexture(), m_viewportRect.GetX(), 
						m_viewportRect.GetY(), raylib::Color::White());
		}
	}
	m_pWindow->EndDrawing();
}

void Application::OnExit()
{
	m_pRT2D->Unload();
}