#ifndef _JARVIS_MARCH_2D_
#define _JARVIS_MARCH_2D_

#include "../Utils.h"

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
	Ch2DOutput Compute(const std::vector<glm::vec2>& allPoints) override
	{
        Ch2DOutput out;

        int leftmostIdx = 0;
        for (int i = 0; i < allPoints.size(); i++)
        {
            out.animQueue.push(std::make_shared<JmFindLeftmost2D>(i, leftmostIdx));

            if (allPoints[i].x < allPoints[leftmostIdx].x)
                leftmostIdx = i;
        }

        int p = leftmostIdx, q;
        do
        {
            out.hullIndices.emplace_back(p);

            q = (p + 1) % allPoints.size();
            for (int i = 0; i < allPoints.size(); i++)
            {
                auto animFrame = std::make_shared<JmCompareAngle2D>(p, i, q, out.hullIndices.size());
                out.animQueue.push(animFrame);

                const auto& orient = Utils::Orientation(allPoints[p], allPoints[i], allPoints[q]);
                if (orient == ORIENTATION::COUNTER_CLOCKWISE)
                    q = i;
            }
            p = q;
        } while (p != leftmostIdx); 

        return out;
	}
};

#endif
