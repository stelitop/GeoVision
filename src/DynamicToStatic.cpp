#include "dynamicToStatic.h"

GM::Point DTSPoint(int index, std::vector<dynamicPoint> * pointMemory)
{
    return (*pointMemory)[index].coords;
}

GM::Segment DTSSegment(int index, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory)
{
    return GM::Segment((*pointMemory)[(*segmentMemory)[index].pointIndexA].coords, (*pointMemory)[(*segmentMemory)[index].pointIndexB].coords);
}

GM::Line DTSLine(int index, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * lineMemory)
{
    return GM::Line((*pointMemory)[(*lineMemory)[index].pointIndexA].coords, (*pointMemory)[(*lineMemory)[index].pointIndexB].coords);
}

GM::Circle DTSCircleDB2(int index, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2)
{
    GM::Point a = (*pointMemory)[(*circleMemoryDB2)[index].pointIndexA].coords, b = (*pointMemory)[(*circleMemoryDB2)[index].pointIndexB].coords;
    return GM::Circle(a, distanceBetweenPoints(a, b));
}
GM::Circle DTSCircleDB3(int index, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes3> * circleMemoryDB3)
{
    return GM::Circle((*pointMemory)[(*circleMemoryDB3)[index].pointIndexA].coords, (*pointMemory)[(*circleMemoryDB3)[index].pointIndexB].coords, (*pointMemory)[(*circleMemoryDB3)[index].pointIndexC].coords);
}
