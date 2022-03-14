#ifndef _JARVIS_MARCH_2D_
#define _JARVIS_MARCH_2D_

#include <queue>

#include "IConvexHull.h"
#include "../Utils.h"
#include "../AnimFrames/Compare2D.h"
#include "../AnimFrames/JmCompareAngle2D.h"

struct JarvisMarch2D : public IConvexHull2D
{
public:
	Ch2DOutput Compute(const std::vector<glm::vec2>& allPoints) override
	{
        m_data.Clear();

        int leftmostIdx = GetLeftmostPoint(allPoints);

        // Find leftmost point relative to curr
        // Set that point as curr
        // Repeat (until curr reaches the initial point)
        int currIdx = leftmostIdx;
        do
        {
            m_data.hullPoints.emplace_back(allPoints[currIdx]);

            int compareIdx = 0;
            for (int i = 0; i < allPoints.size(); i++)
            {
                auto animFrame = std::make_shared<JmCompareAngle2D>(currIdx, i, compareIdx, m_data.hullPoints.size());
                m_data.animQueue.push(animFrame);

                const glm::vec2& p1 = allPoints[currIdx];
                const glm::vec2& p2 = allPoints[i];
                const glm::vec2& p3 = allPoints[compareIdx];
                const ORIENTATION& orient = Utils::Orientation(p1, p2, p3);

                if (orient == ORIENTATION::COUNTER_CLOCKWISE)
                    compareIdx = i;
            }
            currIdx = compareIdx;
        } while (currIdx != leftmostIdx); // If back to first point, finish
   
        return m_data;
	}
private:
    int GetLeftmostPoint(const std::vector<glm::vec2>& allPoints) 
    {
        int leftmostIdx = 0;
        for (int i = 0; i < allPoints.size(); i++)
        {
            auto animFrame = std::make_shared<Compare2D>(i, leftmostIdx);
            m_data.animQueue.push(animFrame);

            if (allPoints[i].x < allPoints[leftmostIdx].x)
                leftmostIdx = i;
        }
        return leftmostIdx;
    }
};

#endif
