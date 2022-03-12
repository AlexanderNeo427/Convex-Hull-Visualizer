#ifndef _ICONVEX_HULL_
#define _ICONVEX_HULL_

#include <glm/vec2.hpp>
#include <memory>
#include <queue>

#include "../IAnimFrame.h"

struct Ch2DOutput
{
	std::vector<int> hullIndices;
	std::queue<std::shared_ptr<IAnimFrame2D>> animQueue;
};
struct IConvexHull2D
{
	virtual Ch2DOutput Compute(const std::vector<glm::vec2>& allPoints) = 0;
};
//-----------------------------------------------------------------------------
struct Ch3DOutput
{
	std::vector<int> hullIndices;
	std::queue<std::shared_ptr<IAnimFrame3D>> animQueue;
};
struct IConvexHull3D
{
	virtual Ch3DOutput Compute(const std::vector<glm::vec3>& allPoints) = 0;
};

#endif
