#ifndef _ANIM_FRAME_
#define _ANIM_FRAME_

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>

struct IAnimFrame2D
{
	virtual void OnRender(const std::vector<glm::vec2> allPoints,
						  const std::vector<int> hullIndices) = 0;
};
struct GenPoint2D : public IAnimFrame2D
{
	explicit GenPoint2D(const int numPointsToShow): m_numPointsToShow(numPointsToShow) {}

	void OnRender(const std::vector<glm::vec2> allPoints,
				  const std::vector<int> hullIndices) override
	{
		for (int i = 0; i < m_numPointsToShow; i++)
		{
			const glm::vec2& p = allPoints[i];
			DrawCircle(p.x, p.y, 3.f, raylib::Color::Green());
		}
	}
private:
	const int m_numPointsToShow;
};
//=================================================================
struct IAnimFrame3D
{
	virtual void OnRender(const std::vector<glm::vec3> allPoints,
						  const std::vector<int> hullIndices) = 0;
};

#endif
