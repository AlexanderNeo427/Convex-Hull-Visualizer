#ifndef _EVENTS_
#define _EVENTS_

#include <glm/vec2.hpp>

struct Event 
{
	enum class TYPE { GEN_PTS };

	struct GenPointsEvent { int numPoints; };

	union 
	{
		GenPointsEvent genPtsEvt;
	};
public:
	TYPE type;

};

#endif
