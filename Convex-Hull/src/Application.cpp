#include "Application.h"

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#undef RAYGUI_IMPLEMENTATION

#include "Scenes/SceneCH2D.h"

Application::Application()
	:
	m_pWindow(nullptr),
	m_pSceneManager(nullptr),
	m_pRT2D(nullptr),
	m_eventQueue(),
	m_viewportRect(),
	m_numPtsToGen(0),
	m_targetTimestep(0.f)
{
	m_numPtsToGen = (MAX_POINTS - MIN_POINTS) / 2;
	m_targetTimestep = (TIMESTEP_MAX - TIMESTEP_MIN) * 0.1f;
}

void Application::OnInitialize()
{
	// Initialize Window
	m_pWindow = std::make_unique<raylib::Window>(SCR_WIDTH, SCR_HEIGHT, "Convex Hull Visualizer");
	m_pWindow->SetTargetFPS(144);

	// Initialize viewport rect 
	const float rtHeight = static_cast<float>(m_pWindow->GetHeight()) * 0.88f;
	const float rtWidth = rtHeight * RT_AR;
	const int posY = (m_pWindow->GetHeight() - rtHeight) / 2;
	const int posX = m_pWindow->GetWidth() - posY - rtWidth;
	m_viewportRect.SetPosition(posX, posY);
	m_viewportRect.SetWidth(rtWidth);
	m_viewportRect.SetHeight(rtHeight);

	// Initialize renderTexture2D
	m_pRT2D = std::make_shared<raylib::RenderTexture2D>();
	m_pRT2D->Load(static_cast<int>(rtWidth), static_cast<int>(rtHeight));

	// Initialize scenes
	m_pSceneManager = std::make_shared<SceneManager>();
	auto scene2D = std::make_shared<SceneCH2D>(m_pSceneManager, "SceneCH2D", rtWidth, rtHeight);
	m_pSceneManager->AddScene(scene2D);

	SetConfigFlags(FLAG_MSAA_4X_HINT);
	GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
}

void Application::OnUpdate()
{
	while (!m_eventQueue.empty())
	{
		const Event& event = m_eventQueue.front();
		m_pSceneManager->OnHandleEvent(event);
		m_eventQueue.pop();
	}
	const float deltaTime = m_pWindow->GetFrameTime();
	m_pSceneManager->OnUpdate(deltaTime);
}

void Application::OnRender()
{
	// Draw current scene to renderTexture2D
	 m_pRT2D->BeginMode();
	 {
		 m_pWindow->ClearBackground(raylib::Color::Blank());
		 m_pSceneManager->OnRender();
	 }
	 m_pRT2D->EndMode();

	// Draw GUI elements
	m_pWindow->BeginDrawing();
	m_pWindow->ClearBackground(raylib::Color::Blank());
	DrawFPS(25, 20);
	{
		// Draw GUI elements
		m_numPtsToGen = GuiSlider(Rectangle{ 130, 120, 370, 30 }, "No. points ",
								  std::to_string(m_numPtsToGen).c_str(),
								  m_numPtsToGen, MIN_POINTS, MAX_POINTS);

		if (GuiButton(Rectangle{ 130, 170, 200, 38 }, "Generate Points"))
		{
			Event evt;
			evt.type = Event::TYPE::GEN_PTS;
			evt.genPtsData.numPoints = m_numPtsToGen;
			m_eventQueue.push(evt);
		}
		{
			m_targetTimestep = GuiSlider(Rectangle{ 130, 400, 370, 30 }, "Timestep ",
										 std::to_string(m_targetTimestep).c_str(),
										 m_targetTimestep, TIMESTEP_MIN, TIMESTEP_MAX);
			Event evt;
			evt.type = Event::TYPE::SET_TIMESTEP;
			evt.setTimeStepData.timeStep = m_targetTimestep;
			m_eventQueue.push(evt);
		}
		if (GuiButton(Rectangle{ 130, 450, 250, 45 }, "Compute Convex Hull"))
		{
			Event evt;
			evt.type = Event::TYPE::COMPUTE_CH;
			m_eventQueue.push(evt);
		}

		// Draw renderTexture2D + viewport bounds
		DrawTexture(
			m_pRT2D->GetTexture(), 
			m_viewportRect.GetX(), 
			m_viewportRect.GetY(), 
			raylib::Color::White()
		);
		DrawRectangleLines(
			m_viewportRect.GetX() - 1,
			m_viewportRect.GetY() - 1,
			m_viewportRect.GetWidth() + 1,
			m_viewportRect.GetHeight() + 1,
			raylib::Color::White()
		);
	}
	m_pWindow->EndDrawing();
}

void Application::OnExit()
{
	m_pRT2D->Unload();
}