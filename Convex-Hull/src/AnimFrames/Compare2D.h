#ifndef _COMPARE_2D_
#define _COMPARE_2D_

#include <raylib-cpp.hpp>
#include "IAnimFrame.h"

struct Compare2D : public IAnimFrame2D
{
	explicit Compare2D(const int idx1, const int idx2)
		: 
		m_idx1(idx1), m_idx2(idx2) {}

	void OnRender(const std::vector<glm::vec2>& allPoints,
				  const std::vector<glm::vec2>& hullPoints) override
	{
		for (const auto& p : allPoints)
		{
			DrawCircle(p.x, p.y, 3.f, raylib::Color::Green());
		}
		const glm::vec2& p1 = allPoints[m_idx1];
		const glm::vec2& p2 = allPoints[m_idx2];
		DrawCircle(p1.x, p1.y, 6.f, raylib::Color::Red());
		DrawCircle(p2.x, p2.y, 6.f, raylib::Color::Blue());
	}
private:
	const int m_idx1, m_idx2;
};

#endif
