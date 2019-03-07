#include "distanceToMouse.h"

bool operator< (const indexDist a, const indexDist b)
{
    if (a.distance < b.distance) return true;
    else if (a.distance > b.distance) return false;
    else if (a.index < b.index) return true;
    else return false;
}

std::vector<indexDist> findClosestPoint(double mouseX, double mouseY, std::vector<dynamicPoint> * pointMemory, double RECOGNISABLE_DISTANCE)
{
    std::vector<indexDist> ret;
    GM::Point mousePos = GM::Point(mouseX, mouseY);
    for (unsigned int i=0; i<pointMemory->size(); i++)
    {
        if (pointMemory->at(i).pType == NO_POINT || pointMemory->at(i).interactable == false || pointMemory->at(i).visible == false) continue;
        double dist = distanceBetweenPoints(pointMemory->at(i).coords, mousePos);
        if (dist <= RECOGNISABLE_DISTANCE)
        {
            ret.emplace_back(i, dist);
        }
    }
    sort(ret.begin(), ret.end());
    return ret;
}

std::vector<indexDist> findClosestSegment(double mouseX, double mouseY, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory, double RECOGNISABLE_DISTANCE)
{
    std::vector<indexDist> ret;
    GM::Point mousePos = GM::Point(mouseX, mouseY);
    for (unsigned int i=0; i<segmentMemory->size(); i++)
    {
        if (segmentMemory->at(i).pointIndexA == -1 || segmentMemory->at(i).interactable == false || segmentMemory->at(i).visible == false) continue;
        GM::Segment seg = DTSSegment(i, pointMemory, segmentMemory);
        GM::Segment alt = altitude(seg, mousePos);
        if (std::max(distanceBetweenPoints(seg.a, alt.b), distanceBetweenPoints(seg.b, alt.b)) < seg.lenght())
        {
            if (alt.lenght() <= RECOGNISABLE_DISTANCE)
            {
                ret.emplace_back(i, alt.lenght());
            }
        }
    }
    sort(ret.begin(), ret.end());
    return ret;
}

std::vector<indexDist> findClosestLine(double mouseX, double mouseY, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * lineMemory, double RECOGNISABLE_DISTANCE)
{
    std::vector<indexDist> ret;
    GM::Point mousePos = GM::Point(mouseX, mouseY);
    for (unsigned int i=0; i<lineMemory->size(); i++)
    {
        if (lineMemory->at(i).pointIndexA == -1 || lineMemory->at(i).interactable == false || lineMemory->at(i).visible == false) continue;
        GM::Line l = DTSLine(i, pointMemory, lineMemory);
        double dist = altitude(l, mousePos).lenght();
        if (dist <= RECOGNISABLE_DISTANCE)
        {
            ret.emplace_back(i, dist);
        }
    }
    sort(ret.begin(), ret.end());
    return ret;
}

std::vector<indexDist> findClosestCircleDB2(double mouseX, double mouseY, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2, double RECOGNISABLE_DISTANCE)
{
    std::vector<indexDist> ret;
    GM::Point mousePos = GM::Point(mouseX, mouseY);
    for (unsigned int i=0; i<circleMemoryDB2->size(); i++)
    {
        if (circleMemoryDB2->at(i).pointIndexA == -1 || circleMemoryDB2->at(i).interactable == false || circleMemoryDB2->at(i).visible == false) continue;
        GM::Circle c = DTSCircleDB2(i, pointMemory, circleMemoryDB2);
        double dist = distanceBetweenPoints(c.center, mousePos) - c.radius;
        if (dist < 0) dist*=-1;
        if (dist <= RECOGNISABLE_DISTANCE)
        {
            ret.emplace_back(i, dist);
        }
    }
    sort(ret.begin(), ret.end());
    return ret;
}

std::vector<indexDist> findClosestCircleDB3(double mouseX, double mouseY, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes3> * circleMemoryDB3, double RECOGNISABLE_DISTANCE)
{
    std::vector<indexDist> ret;
    GM::Point mousePos = GM::Point(mouseX, mouseY);
    for (unsigned int i=0; i<circleMemoryDB3->size(); i++)
    {
        if (circleMemoryDB3->at(i).pointIndexA == -1 || circleMemoryDB3->at(i).interactable == false || circleMemoryDB3->at(i).visible == false) continue;
        GM::Circle c = DTSCircleDB3(i, pointMemory, circleMemoryDB3);
        double dist = distanceBetweenPoints(c.center, mousePos) - c.radius;
        if (dist < 0) dist*=-1;
        if (dist <= RECOGNISABLE_DISTANCE)
        {
            ret.emplace_back(i, dist);
        }
    }
    sort(ret.begin(), ret.end());
    return ret;
}
