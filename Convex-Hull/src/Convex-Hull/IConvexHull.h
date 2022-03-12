#ifndef _ICONVEX_HULL_
#define _ICONVEX_HULL_

#include <glm/vec2.hpp>
#include <memory>
#include <queue>

#include "../IAnimFrame.h"

struct IConvexHull2D
{
	using Points2D	  = std::vector<glm::vec2>;
	using AnimQueue2D = std::queue<std::shared_ptr<IAnimFrame2D>>;

	virtual std::pair<Points2D, AnimQueue2D> Compute(const Points2D& allPoints) = 0;
};

struct IConvexHull3D
{
	using Points3D	  = std::vector<glm::vec3>;
	using AnimQueue3D = std::queue<std::shared_ptr<IAnimFrame3D>>;

	virtual std::pair<Points3D, AnimQueue3D> Compute(const Points3D& allPoints) = 0;
};

#endif
