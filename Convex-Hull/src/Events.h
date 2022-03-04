#ifndef EVENTS
#define EVENTS

struct Event {};

struct OnGeneratePointsBtnClick : public Event
{
	OnGeneratePointsBtnClick(const int numPoints): m_numPoints(numPoints) {}
	const int GetNumPoints() const { return m_numPoints; }
private:
	const int m_numPoints;
};

#endif
