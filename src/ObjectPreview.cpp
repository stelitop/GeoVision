#include "ObjectPreview.h"

void objectPreview(RenderWindow * window, std::vector<dynamicIndex> * indexSelection, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory, std::vector<dynamicPointIndexes2> * lineMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2, std::vector<dynamicPointIndexes3> * circleMemoryDB3, geometricToolSelected toolSelection, GM::Vector offset, double RECOGNISABLE_DISTANCE, double thickness)
{
    Vector2i mouse = Mouse::getPosition(*window);
    GM::Point mousePoint(mouse.x + offset.x, window->getSize().y - mouse.y + offset.y);

    switch (toolSelection)
    {
        case CREATE_SEGMENT:
        {
            GM::Point p = DTSPoint((*indexSelection)[0].index, pointMemory);
            if ((*indexSelection)[0].shape == POINT)
                renderGMShape(window, GM::Segment(p, mousePoint), SegmentColors(DEFAULT_COLOR_PREVIEW, DEFAULT_COLOR_PREVIEW), offset, thickness);
            break;
        }
        case CREATE_LINE:
        {
            GM::Point p = DTSPoint((*indexSelection)[0].index, pointMemory);
            if (p == mousePoint) break;
            if ((*indexSelection)[0].shape == POINT)
                renderGMShape(window, GM::Line(p, mousePoint), LineColors(DEFAULT_COLOR_PREVIEW), offset, thickness);
            break;
        }
        case CREATE_CIRCLE_DB2:
        {
            GM::Point p = DTSPoint((*indexSelection)[0].index, pointMemory);
            if ((*indexSelection)[0].shape == POINT)
                renderGMShape(window, GM::Circle(p, GM::Segment(p, mousePoint).lenght()), CircleColors(sf::Color(0, 0, 0, 0), DEFAULT_COLOR_PREVIEW), offset, thickness);
            break;
        }
        case CREATE_CIRCLE_DB3:
        {
            if (indexSelection->size() == 2 && (*indexSelection)[0].shape == POINT && (*indexSelection)[1].shape == POINT)
            {
                GM::Point a = DTSPoint((*indexSelection)[0].index, pointMemory), b = DTSPoint((*indexSelection)[1].index, pointMemory), c = mousePoint;
                if (a == b && b == c) break;
                if (a == b || a == c) renderGMShape(window, GM::Line(b, c), LineColors(DEFAULT_COLOR_PREVIEW), offset, thickness);
                else if (b == c) renderGMShape(window, GM::Line(a, b), LineColors(DEFAULT_COLOR_PREVIEW), offset, thickness);
                else if (GM::Line(a, b).isPointLying(c)) renderGMShape(window, GM::Line(a, b), LineColors(DEFAULT_COLOR_PREVIEW), offset, thickness);
                else renderGMShape(window, GM::Circle(a, b, c), CircleColors(sf::Color(0, 0, 0, 0), DEFAULT_COLOR_PREVIEW), offset, thickness);
            }
            break;
        }
        case CREATE_MIDPOINT:
        {
            GM::Point p = DTSPoint((*indexSelection)[0].index, pointMemory);
            if ((*indexSelection)[0].shape == POINT)
                renderGMShape(window, midpoint(p, mousePoint), PointColors(DEFAULT_COLOR_PREVIEW), offset);
            break;
        }
        case CREATE_PERPENDICULAR_BISECTOR:
        {
            GM::Point p = DTSPoint((*indexSelection)[0].index, pointMemory);
            if (p == mousePoint) break;
            if ((*indexSelection)[0].shape == POINT)
                renderGMShape(window, perpendicularBisector(GM::Segment(p, mousePoint)), LineColors(DEFAULT_COLOR_PREVIEW), offset, thickness);
            break;
        }
        case CREATE_ALTITUDE_FOOT:
        {
            if ((*indexSelection)[0].shape == LINE)
            {
                GM::Segment s = altitude(mousePoint, DTSLine((*indexSelection)[0].index, pointMemory, lineMemory));
                renderGMShape(window, s, SegmentColors(DEFAULT_COLOR_PREVIEW, DEFAULT_COLOR_PREVIEW), offset, thickness);
                renderGMShape(window, s.b, PointColors(DEFAULT_COLOR_PREVIEW), offset);
            }
            else if ((*indexSelection)[0].shape == SEGMENT)
            {
                GM::Segment s = altitude(mousePoint, DTSSegment((*indexSelection)[0].index, pointMemory, segmentMemory));
                renderGMShape(window, s, SegmentColors(DEFAULT_COLOR_PREVIEW, DEFAULT_COLOR_PREVIEW), offset, thickness);
                renderGMShape(window, s.b, PointColors(DEFAULT_COLOR_PREVIEW), offset);
            }
            else if ((*indexSelection)[0].shape == POINT)
            {
                const std::set<geometryShape> preferred = {SEGMENT, LINE};
                dynamicIndex ret = selectObject(mousePoint.x, mousePoint.y, indexSelection, pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3, RECOGNISABLE_DISTANCE, preferred);
                if (ret.shape != NO_SHAPE)
                {
                    if (ret.shape == SEGMENT)
                    {
                        GM::Segment s = altitude(DTSPoint((*indexSelection)[0].index, pointMemory), DTSSegment((*indexSelection)[1].index, pointMemory, segmentMemory));
                        renderGMShape(window, s, SegmentColors(DEFAULT_COLOR_PREVIEW, DEFAULT_COLOR_PREVIEW), offset, thickness);
                        renderGMShape(window, s.b, PointColors(DEFAULT_COLOR_PREVIEW), offset);
                    }
                    else
                    {
                        GM::Segment s = altitude(DTSPoint((*indexSelection)[0].index, pointMemory), DTSLine((*indexSelection)[1].index, pointMemory, lineMemory));
                        renderGMShape(window, s, SegmentColors(DEFAULT_COLOR_PREVIEW, DEFAULT_COLOR_PREVIEW), offset, thickness);
                        renderGMShape(window, s.b, PointColors(DEFAULT_COLOR_PREVIEW), offset);
                    }
                    indexSelection->pop_back();
                }
                else
                {
                    GM::Segment s(mousePoint, DTSPoint((*indexSelection)[0].index, pointMemory));
                    renderGMShape(window, s, SegmentColors(DEFAULT_COLOR_PREVIEW, DEFAULT_COLOR_PREVIEW), offset, thickness);
                }
            }
            break;
        }
        case CREATE_ANGLE_BISECTOR:
        {
            if (indexSelection->size() == 2 && (*indexSelection)[0].shape == POINT && (*indexSelection)[1].shape == POINT)
            {
                GM::Point a = DTSPoint((*indexSelection)[0].index, pointMemory), b = DTSPoint((*indexSelection)[1].index, pointMemory), c = mousePoint;
                GM::Line l = angleBisector(a, b, c);
                renderGMShape(window, l, LineColors(DEFAULT_COLOR_PREVIEW), offset, thickness);
            }
            break;
        }
        case CREATE_OUTSIDE_ANGLE_BISECTOR:
        {
            if (indexSelection->size() == 2 && (*indexSelection)[0].shape == POINT && (*indexSelection)[1].shape == POINT)
            {
                GM::Point a = DTSPoint((*indexSelection)[0].index, pointMemory), b = DTSPoint((*indexSelection)[1].index, pointMemory), c = mousePoint;
                GM::Line l = angleBisector(a, b, c);
                GM::Line l2;
                if (l.straight()) l2 = GM::Line(0, b.y);
                else if (l.getM() == 0) l2 = GM::Line(b, b + GM::Vector(0, 100));
                else l2 = GM::Line( -1/l.getM() , b.y + b.x/l.getM() );
                renderGMShape(window, l2, LineColors(DEFAULT_COLOR_PREVIEW), offset, thickness);
            }
            break;
        }
    default:
        break;

    }
}
