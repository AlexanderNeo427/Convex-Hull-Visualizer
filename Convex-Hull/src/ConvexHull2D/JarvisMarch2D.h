#ifndef _JARVIS_MARCH_2D_
#define _JARVIS_MARCH_2D_

#include <vector>
#include <glm/vec2.hpp>
#include <raylib-cpp.hpp>

#include "FiniteStateMachine.h"
#include "../StateEnums.h"

class JarvisMarch2D : public FSM::State<CH2D>
{
public:
	enum class STATE 
	{
		FIND_LEFTMOST_POINT,

	};
public:
	explicit JarvisMarch2D(std::shared_ptr<FSM::StateMachine<CH2D>> pOwner, 
						   std::vector<glm::vec2> allPoints)
		:
		FSM::State<CH2D>(CH2D::JARVIS_MARCH, "Jarvis March", pOwner),
		m_allPoints(allPoints)
	{}

	void OnUpdate(const float deltaTime) override
	{
		switch (m_state)
		{
		case JarvisMarch2D::STATE::FIND_LEFTMOST_POINT:
			break;
		default:
			break;
		}
	}
	void OnRender() override
	{
		if (m_hullPoints.size() < 2)
			return;

		for (int i = 0; i < m_hullPoints.size() - 1; i++)
		{
			const glm::vec2& p1 = m_hullPoints[i];
			const glm::vec2& p2 = m_hullPoints[i];
			DrawLine(p1.x, p1.y, p2.x, p2.y, raylib::Color::RayWhite());
		}
	}
private:
	const std::vector<glm::vec2> m_allPoints;
	std::vector<glm::vec2> m_hullPoints;

	STATE m_state;
};

#endif
