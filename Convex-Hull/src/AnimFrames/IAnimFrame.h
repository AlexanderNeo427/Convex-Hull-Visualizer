#ifndef _ANIM_FRAME_
#define _ANIM_FRAME_

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>

struct IAnimFrame2D
{
	virtual void OnRender(const std::vector<glm::vec2>& allPoints,
						  const std::vector<glm::vec2>& hullPoints) = 0;
};
//=================================================================
struct IAnimFrame3D
{
	virtual void OnRender(const std::vector<glm::vec3>& allPoints,
						  const std::vector<glm::vec3>& hullPoints) = 0;
};

#endif
