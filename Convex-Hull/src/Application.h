#ifndef APPLICATION
#define APPLICATION

#include <raylib-cpp.hpp>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#undef RAYGUI_IMPLEMENTATION

#include "NodeManager.h"
#include "Nodes/RootSceneNode.h"

struct Application
{
	void Run()
	{
		m_window = std::make_unique<raylib::Window>(1450, 900, "Convex Hull");
		m_window->SetTargetFPS(120);

		auto root = std::make_shared<RootSceneNode>();
		root->SetParent(nullptr);
		m_nodeManager = std::make_unique<NodeManager>(root);

		while (!m_window->ShouldClose())
		{
			m_nodeManager->Update(GetFrameTime());
			RenderGUI();
		}
	}
	void RenderGUI()
	{
		static const float scrWidth = static_cast<float>(GetScreenWidth());
		static const float scrHeight = static_cast<float>(GetScreenHeight());

		BeginDrawing();
		ClearBackground(raylib::Color::Black());
		{
			m_numPoints = GuiSlider(Rectangle{40, 40, 250, 50},
				"10", "150", m_numPoints, 10, 150
			);

			if (GuiButton(Rectangle {40, 120, 120, 50}, "Generate points"))
			{
				OnGeneratePointsBtnClick evt(m_numPoints);
				m_nodeManager->PropagateEvent(evt);
			}
		}
		EndDrawing();
	}
private:
	std::unique_ptr<raylib::Window> m_window;
	std::unique_ptr<NodeManager>	m_nodeManager;

	int m_numPoints;
};

#endif