#ifndef _ICONVEX_HULL_
#define _ICONVEX_HULL_

#include <glm/vec2.hpp>
#include <memory>
#include <queue>

#include "../IAnimFrame.h"

struct Ch2DOutput
{
	std::vector<glm::vec2> hullPoints;
	std::queue<std::shared_ptr<IAnimFrame2D>> animQueue;

	void Clear()
	{
		hullPoints.clear();
		animQueue = {};
	}
};
struct IConvexHull2D
{
	using AnimFrame2D = std::shared_ptr<IAnimFrame2D>;
	using AnimFrame2DQueue = std::queue<AnimFrame2D>;

	virtual Ch2DOutput Compute(const std::vector<glm::vec2>& allPoints) = 0;
protected:
	Ch2DOutput m_data;
};
//===========================================================================
struct Ch3DOutput
{
	std::vector<glm::vec3> hullPoints;
	std::queue<std::shared_ptr<IAnimFrame3D>> animQueue;

	void Clear()
	{
		hullPoints.clear();
		animQueue = {};
	}
};
struct IConvexHull3D
{
	using AnimFrame3D = std::shared_ptr<IAnimFrame3D>;
	using AnimFrame3DQueue = std::queue<AnimFrame3D>;

	virtual Ch3DOutput Compute(const std::vector<glm::vec3>& allPoints) = 0;
protected:
	Ch3DOutput m_data;
};

#endif
