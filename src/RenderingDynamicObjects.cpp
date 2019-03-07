#include "RenderingDynamicObjects.h"

void renderDynamicObjects(RenderWindow * window, double mouseX, double mouseY, std::vector<dynamicIndex> * selection, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory, std::vector<dynamicPointIndexes2> * lineMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2, std::vector<dynamicPointIndexes3> * circleMemoryDB3, GM::Vector offset, double RECOGNISABLE_DISTANCE, double thickness)
{
    std::set<int> selectedPoints, selectedSegments, selectedLines, selectedCirclesDB2, selectedCirclesDB3;
    const std::set<geometryShape> preferred = {POINT, SEGMENT, LINE, CIRCLE_DB2, CIRCLE_DB3};
    dynamicIndex hovered = selectObject(mouseX, mouseY, selection, pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3, RECOGNISABLE_DISTANCE, preferred);
    if (hovered.shape != NO_SHAPE) selection->pop_back();

    for (unsigned int i=0; i<selection->size(); i++)
    {
        switch (selection->at(i).shape)
        {
        case POINT:
            selectedPoints.insert(selection->at(i).index);
            break;
        case SEGMENT:
            selectedSegments.insert(selection->at(i).index);
            break;
        case LINE:
            selectedLines.insert(selection->at(i).index);
            break;
        case CIRCLE_DB2:
            selectedCirclesDB2.insert(selection->at(i).index);
            break;
        case CIRCLE_DB3:
            selectedCirclesDB3.insert(selection->at(i).index);
            break;
        default:
            break;
        }
    }

    for (unsigned int i=0; i<segmentMemory->size(); i++)
    {
        if ((*segmentMemory)[i].pointIndexA == -1 || (*segmentMemory)[i].interactable == false || (*segmentMemory)[i].visible == false) continue;
        if (selectedSegments.find(i) != selectedSegments.end())
        {
            renderGMShape(window, DTSSegment(i, pointMemory, segmentMemory), SegmentColors(DEFAULT_COLOR_SELECTION, DEFAULT_COLOR_SELECTION), offset, thickness);
            continue;
        }
        if (hovered.shape == SEGMENT && hovered.index == i)
        {
            renderGMShape(window, DTSSegment(i, pointMemory, segmentMemory), SegmentColors(DEFAULT_COLOR_HOVER, DEFAULT_COLOR_HOVER), offset, thickness);
            continue;
        }
        renderGMShape(window, DTSSegment(i, pointMemory, segmentMemory), offset, thickness);
    }
    for (unsigned int i=0; i<lineMemory->size(); i++)
    {
        if ((*lineMemory)[i].pointIndexA == -1 || (*lineMemory)[i].interactable == false || (*lineMemory)[i].visible == false) continue;
        GM::Point a = DTSPoint((*lineMemory)[i].pointIndexA, pointMemory), b = DTSPoint((*lineMemory)[i].pointIndexB, pointMemory);
        if (a == b) continue;
        if (selectedLines.find(i) != selectedLines.end())
        {
            renderGMShape(window, GM::Line(a, b), LineColors(DEFAULT_COLOR_SELECTION), offset, thickness);
            continue;
        }
        if (hovered.shape == LINE && hovered.index == i)
        {
            renderGMShape(window, GM::Line(a, b), LineColors(DEFAULT_COLOR_HOVER), offset, thickness);
            continue;
        }
        renderGMShape(window, GM::Line(a, b), offset, thickness);
    }
    for (unsigned int i=0; i<circleMemoryDB2->size(); i++)
    {
        if ((*circleMemoryDB2)[i].pointIndexA == -1 || (*circleMemoryDB2)[i].interactable == false || (*circleMemoryDB2)[i].visible == false) continue;
        if (selectedCirclesDB2.find(i) != selectedCirclesDB2.end())
        {
            renderGMShape(window, DTSCircleDB2(i, pointMemory, circleMemoryDB2), CircleColors(sf::Color(0, 0, 0, 0), DEFAULT_COLOR_SELECTION), offset, thickness);
            continue;
        }
        if (hovered.shape == CIRCLE_DB2 && hovered.index == i)
        {
            renderGMShape(window, DTSCircleDB2(i, pointMemory, circleMemoryDB2), CircleColors(sf::Color(0, 0, 0, 0), DEFAULT_COLOR_HOVER), offset, thickness);
            continue;
        }
        renderGMShape(window, DTSCircleDB2(i, pointMemory, circleMemoryDB2), offset, thickness);
    }
    for (unsigned int i=0; i<circleMemoryDB3->size(); i++)
    {
        if ((*circleMemoryDB3)[i].pointIndexA == -1 || (*circleMemoryDB3)[i].interactable == false || (*circleMemoryDB3)[i].visible == false) continue;
        GM::Point a = DTSPoint((*circleMemoryDB3)[i].pointIndexA, pointMemory), b = DTSPoint((*circleMemoryDB3)[i].pointIndexB, pointMemory), c = DTSPoint((*circleMemoryDB3)[i].pointIndexC, pointMemory);
        if (a == b && b == c) continue;
        if (selectedCirclesDB3.find(i) != selectedCirclesDB3.end())
        {
            if (a == b || a == c) renderGMShape(window, GM::Line(b, c), LineColors(DEFAULT_COLOR_SELECTION), offset, thickness);
            else if (b == c) renderGMShape(window, GM::Line(a, b), LineColors(DEFAULT_COLOR_SELECTION), offset, thickness);
            else if (GM::Line(a, b).isPointLying(c)) renderGMShape(window, GM::Line(a, b), LineColors(DEFAULT_COLOR_SELECTION), offset, thickness);
            else renderGMShape(window, GM::Circle(a, b, c), CircleColors(sf::Color(0, 0, 0, 0), DEFAULT_COLOR_SELECTION), offset, thickness);
            continue;
        }
        if (hovered.shape == CIRCLE_DB3 && hovered.index == i)
        {
            if (a == b || a == c) renderGMShape(window, GM::Line(b, c), LineColors(DEFAULT_COLOR_HOVER), offset, thickness);
            else if (b == c) renderGMShape(window, GM::Line(a, b), LineColors(DEFAULT_COLOR_HOVER), offset, thickness);
            else if (GM::Line(a, b).isPointLying(c)) renderGMShape(window, GM::Line(a, b), LineColors(DEFAULT_COLOR_HOVER) ,offset, thickness);
            else renderGMShape(window, GM::Circle(a, b, c), CircleColors(sf::Color(0, 0, 0, 0), DEFAULT_COLOR_HOVER), offset, thickness);
            continue;
        }
        if (a == b || a == c) renderGMShape(window, GM::Line(b, c), offset, thickness);
        else if (b == c) renderGMShape(window, GM::Line(a, b), offset, thickness);
        else if (GM::Line(a, b).isPointLying(c)) renderGMShape(window, GM::Line(a, b), offset, thickness);
        else renderGMShape(window, GM::Circle(a, b, c), offset, thickness);
    }
    for (unsigned int i=0; i<pointMemory->size(); i++)
    {
        if ((*pointMemory)[i].pType == NO_POINT || (*pointMemory)[i].interactable == false || (*pointMemory)[i].visible == false) continue;
        if (selectedPoints.find(i) != selectedPoints.end())
        {
            renderGMShape(window, (*pointMemory)[i].coords, PointColors(DEFAULT_COLOR_SELECTION), offset);
            continue;
        }
        if (hovered.shape == POINT && hovered.index == i)
        {
            renderGMShape(window, (*pointMemory)[i].coords, PointColors(DEFAULT_COLOR_HOVER), offset);
            continue;
        }
        renderGMShape(window, (*pointMemory)[i].coords, offset);
    }
}
