#ifndef _JM_COMPARE_ANGLE_2D_
#define _JM_COMPARE_ANGLE_2D_

#include <raylib-cpp.hpp>
#include "IAnimFrame.h"

struct JmCompareAngle2D : public IAnimFrame2D
{
    explicit JmCompareAngle2D(const int currIdx, const int prevIdx,
                              const int compareIdx, const int hullIndex)
        :
        m_currIdx(currIdx),
        m_prevIdx(prevIdx),
        m_compareIdx(compareIdx),
        m_hullIndex(hullIndex)
    {}
    void OnRender(const std::vector<glm::vec2>& allPoints,
                  const std::vector<glm::vec2>& hullPoints) override
    {
        const glm::vec2& curr = allPoints[m_currIdx];
        const glm::vec2& prev = allPoints[m_prevIdx];
        const glm::vec2& comp = allPoints[m_compareIdx];
        DrawLine(curr.x, curr.y, prev.x, prev.y, raylib::Color::Red());
        DrawLine(curr.x, curr.y, comp.x, comp.y, raylib::Color::Blue());

        for (int i = 0; i < m_hullIndex - 1; i++)
        {
            const int nextIdx = (i == m_hullIndex - 1) ? 0 : (i + 1);
            const glm::vec2& p1 = hullPoints[i];
            const glm::vec2& p2 = hullPoints[nextIdx];
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

#endif
