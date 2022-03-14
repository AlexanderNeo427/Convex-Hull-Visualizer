#ifndef _GS_MAIN_2D_
#define _GS_MAIN_2D_

#include <raylib-cpp.hpp>
#include "IAnimFrame.h"

struct GsMain2D : public IAnimFrame2D
{
	explicit GsMain2D(const std::vector<glm::vec2>& hull, 
					  const glm::vec2& comparePt)
		: 
		m_hull(hull),
		m_comparePt(comparePt)
	{}

	void OnRender(const std::vector<glm::vec2>& allPoints,
				  const std::vector<glm::vec2>& hullPoints) override
	{
		if (m_hull.size() >= 2)
		{
			for (int i = 0; i < m_hull.size() - 1; i++)
			{
				const glm::vec2& p1 = m_hull[i];
				const glm::vec2& p2 = m_hull[i + 1];
				DrawLine(p1.x, p1.y, p2.x, p2.y, raylib::Color::Yellow());
			}
		}
		{
			const glm::vec2& lastPt = m_hull[m_hull.size() - 1];
			DrawLine(lastPt.x, lastPt.y, m_comparePt.x, m_comparePt.y, raylib::Color::Red());
		}
		for (const glm::vec2& p : allPoints)
		{
			DrawCircle(p.x, p.y, 3.f, raylib::Color::Green());
		}
	}
private:
	const std::vector<glm::vec2> m_hull;
	const glm::vec2 m_comparePt;
};

#endif
