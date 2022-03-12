#ifndef _UTILS_
#define _UTILS_

#include <glm/vec2.hpp>

enum class ORIENTATION
{
	CLOCKWISE,
	COUNTER_CLOCKWISE,
	COLLINEAR
};

struct Utils
{
	static ORIENTATION Orientation(const glm::vec2& p, 
								   const glm::vec2& q, 
								   const glm::vec2& r)
	{
		int val = (q.y - p.y) * (r.x - q.x) -
				  (q.x - p.x) * (r.y - q.y);

		if (val == 0) 
			return ORIENTATION::COLLINEAR;  

		return (val > 0) ? ORIENTATION::CLOCKWISE :
						   ORIENTATION::COUNTER_CLOCKWISE; 
	}
};

#endif
