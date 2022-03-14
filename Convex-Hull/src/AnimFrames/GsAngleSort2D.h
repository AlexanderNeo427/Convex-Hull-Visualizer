#ifndef _GS_ANGLE_SORT_2D_
#define _GS_ANGLE_SORT_2D_

#include <raylib-cpp.hpp>
#include "IAnimFrame.h"

struct GsAngleSort2D : public IAnimFrame2D
{
    explicit GsAngleSort2D(const glm::vec2 anchorPt,
                           const std::vector<glm::vec2>& sortedPoints,
                           const int sortedIndex)
        :
        m_anchorPt(anchorPt),
        m_sortedPoints(sortedPoints),
        m_sortedIndex(sortedIndex)
    {}
    void OnRender(const std::vector<glm::vec2>& allPoints,
                  const std::vector<glm::vec2>& hullPoints) override
    {
        for (int i = 0; i < m_sortedIndex; i++)
        {
            const glm::vec2& p1 = m_anchorPt;
            const glm::vec2& p2 = m_sortedPoints[i];
            DrawLine(p1.x, p1.y, p2.x, p2.y, raylib::Color::DarkPurple());
        }
        for (const auto& p : allPoints)
        {
            DrawCircle(p.x, p.y, 3.f, raylib::Color::Green());
        }
    }
private:
    const glm::vec2 m_anchorPt;
    const std::vector<glm::vec2> m_sortedPoints;
    const int m_sortedIndex;
};

#endif
