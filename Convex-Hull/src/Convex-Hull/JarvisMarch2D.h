#ifndef _JARVIS_MARCH_2D_
#define _JARVIS_MARCH_2D_

#include "IConvexHull.h"
#include "../IAnimFrame.h"
#include "../Utils.h"
#include <queue>

struct JmFindLeftmost2D : public IAnimFrame2D
{
    explicit JmFindLeftmost2D(const int leftmostIdx, const int compareIdx)
        :
        m_currLeftmostIdx(leftmostIdx), m_compareIdx(compareIdx)
    {}
    void OnRender(const std::vector<glm::vec2> allPoints,
                  const std::vector<int> hullIndices) override
    {
        for (const glm::vec2& p : allPoints)
        {
            DrawCircle(p.x, p.y, 3.f, raylib::Color::Green());
        }
        const glm::vec2& curr = allPoints[m_currLeftmostIdx];
        const glm::vec2& cmp = allPoints[m_compareIdx];
        DrawCircle(curr.x, curr.y, 5.5f, raylib::Color::Red());
        DrawCircle(cmp.x, cmp.y, 5.5f, raylib::Color::Blue());
    }
private:
    int m_currLeftmostIdx, m_compareIdx;
};
//===============================================================================================
struct JmCompareAngle2D: public IAnimFrame2D
{
    explicit JmCompareAngle2D(const int currIdx, const int prevIdx,
                             const int compareIdx, const int hullIndex)
        :
        m_currIdx(currIdx), m_prevIdx(prevIdx), m_compareIdx(compareIdx), m_hullIndex(hullIndex)
    {}
    void OnRender(const std::vector<glm::vec2> allPoints,
                  const std::vector<int> hullIndices) override
    {
        const glm::vec2& curr = allPoints[m_currIdx];
        const glm::vec2& prev = allPoints[m_prevIdx];
        const glm::vec2& comp = allPoints[m_compareIdx];
        DrawLine(curr.x, curr.y, prev.x, prev.y, raylib::Color::Red());
        DrawLine(curr.x, curr.y, comp.x, comp.y, raylib::Color::Blue());

        for (int i = 0; i < m_hullIndex - 1; i++)
        {
            const int nextIdx = (i == m_hullIndex - 1) ? 0 : (i + 1);
            const glm::vec2& p1 = allPoints[hullIndices[i]];
            const glm::vec2& p2 = allPoints[hullIndices[i + 1]];
            DrawLine(p1.x, p1.y, p2.x, p2.y, raylib::Color::Yellow());
        }
        for (const glm::vec2& p : allPoints)
        {
            DrawCircle(p.x, p.y, 3.f, raylib::Color::Green());
        }
    }
private:
    int m_currIdx, m_prevIdx, m_compareIdx, m_hullIndex;
};
//===============================================================================================
struct JarvisMarch2D : public IConvexHull2D
{
public:
	Ch2DOutput Compute(const std::vector<glm::vec2>& allPoints) override
	{
        Ch2DOutput out;

        auto [leftmostIdx, frameQueue] = GetLeftmostPoint(allPoints);
        while (!frameQueue.empty())
        {
            auto animFrame = frameQueue.front();
            frameQueue.pop();
            out.animQueue.push(animFrame);
        }

        int currIdx = leftmostIdx;
        int compareIdx = 0;
        do
        {
            out.hullIndices.emplace_back(currIdx);

            compareIdx = (currIdx + 1) % allPoints.size();
            for (int i = 0; i < allPoints.size(); i++)
            {
                auto animFrame = std::make_shared<JmCompareAngle2D>(currIdx, i, compareIdx, out.hullIndices.size());
                out.animQueue.push(animFrame);

                const ORIENTATION& orient = Utils::Orientation(allPoints[currIdx], allPoints[i], allPoints[compareIdx]);
                if (orient == ORIENTATION::COUNTER_CLOCKWISE)
                    compareIdx = i;
            }
            currIdx = compareIdx;
        } while (currIdx != leftmostIdx); 

        return out;
	}
private:
    std::pair<int, AnimFrame2DQueue> GetLeftmostPoint(const std::vector<glm::vec2>& allPoints) const
    {
        AnimFrame2DQueue frameQueue;

        int leftmostIdx = 0;
        for (int i = 0; i < allPoints.size(); i++)
        {
            auto animFrame = std::make_shared<JmFindLeftmost2D>(i, leftmostIdx);
            frameQueue.push(animFrame);

            if (allPoints[i].x < allPoints[leftmostIdx].x)
                leftmostIdx = i;
        }
        return { leftmostIdx, frameQueue };
    }
};

#endif
