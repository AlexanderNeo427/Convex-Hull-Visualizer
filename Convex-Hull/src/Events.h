#ifndef _EVENTS_
#define _EVENTS_

#include <glm/vec2.hpp>

struct Event 
{
	Event() {};
	virtual ~Event() {};
};
//------------------------------------------------------------------
struct PosChangeEvt : public Event 
{
	explicit PosChangeEvt(const glm::vec2& pos): m_pos(pos) {}
	const glm::vec2& Position() const { return m_pos; }
private:
	const glm::vec2 m_pos;
};
//------------------------------------------------------------------
struct GenPtsEvt : public Event
{
	explicit GenPtsEvt(const int numPoints): m_numPoints(numPoints) {}
	const int NumPoints() const { return m_numPoints; }
private:
	const int m_numPoints;
};
//------------------------------------------------------------------

#endif
