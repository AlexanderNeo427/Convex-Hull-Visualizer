#ifndef _MODE_3D_CONTEXT_
#define _MODE_3D_CONTEXT_

#include <glm/vec3.hpp>
#include <vector>

class Mode3DContext
{
public:
	Mode3DContext(const int width, const int height)
		:
		m_width(width), m_height(height) {}

	const int Width() const { return m_width; }
	const int Height() const { return m_height; }
public:
	std::vector<glm::vec3> points;
private:
	const int m_width;
	const int m_height;
};

#endif