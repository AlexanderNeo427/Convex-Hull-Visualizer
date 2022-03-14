#ifndef _GRAHAM_SCAN_2D_
#define _GRAHAM_SCAN_2D_

#include <stack>
#include <queue>

#include "IConvexHull.h"
#include "../IAnimFrame.h"
#include "../Utils.h"

class GrahamScan2D : public IConvexHull2D
{
public:
	Ch2DOutput Compute(const std::vector<glm::vec2>& allPoints) override
	{
		m_data.Clear();

		// Get bottom-most point
		int bottomMostIdx = GetBottomMostPoint(allPoints);

		// Sort all other points (by polar angle) relative to the bottom-most point
		std::vector<glm::vec2> sortedPts = allPoints;
		std::swap(sortedPts[0], sortedPts[bottomMostIdx]);
		sortedPts = SortPolarAngle(allPoints[bottomMostIdx], sortedPts);

		for (int i = 1; i < sortedPts.size(); i++)
		{
			const glm::vec2& curr = sortedPts[i];

			while (true)
			{
				if (m_data.hullPoints.size() < 2) break;

				const glm::vec2& last = m_data.hullPoints[m_data.hullPoints.size() - 1];
				const glm::vec2& beforeLast = m_data.hullPoints[m_data.hullPoints.size() - 2];

				const ORIENTATION& orient = Utils::Orientation(beforeLast, last, curr);
				if (orient != ORIENTATION::COUNTER_CLOCKWISE)
				{
					m_data.hullPoints.pop_back();
				}
				else break;
			}
			m_data.hullPoints.emplace_back(curr);
		}
		return m_data;
	}
private:
	int GetBottomMostPoint(const std::vector<glm::vec2>& allPoints) const
	{
		int bottomMostIdx = 0;
		for (int i = 0; i < allPoints.size(); i++)
		{
			if (allPoints[bottomMostIdx].y < allPoints[i].y)
				bottomMostIdx = i;
		}
		return bottomMostIdx;
	}
	std::vector<glm::vec2>& SortPolarAngle(const glm::vec2& anchorPt, std::vector<glm::vec2>& points)
	{
		std::sort(points.begin(), points.end(),
			[=, *this](const glm::vec2& p1, const glm::vec2& p2)
			{
				const float m1 = (p1.y - anchorPt.y) / (p1.x - anchorPt.x);
				const float m2 = (p2.y - anchorPt.y) / (p2.x - anchorPt.x);
				return m1 < m2;
			});
		return points;
	}

};

#endif
