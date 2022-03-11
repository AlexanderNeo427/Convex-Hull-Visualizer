#ifndef _MODE_2D_CONTEXT_
#define _MODE_2D_CONTEXT_

#include <glm/vec2.hpp>
#include <vector>

struct Mode2DContext
{
public:
	Mode2DContext(const int width, const int height)
		:
		m_width(width), m_height(height) {}

	const int Width() const { return m_width; }
	const int Height() const { return m_height; }

	std::vector<glm::vec2> allPoints;
	std::vector<glm::vec2> hullPoints;

	int numPointsToGenerate = 0;
private:
	const int m_width, m_height;
};

#endif