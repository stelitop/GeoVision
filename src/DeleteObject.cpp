#include "DeleteObject.h"

void deletePoint(int index, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory, std::vector<dynamicPointIndexes2> * lineMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2, std::vector<dynamicPointIndexes3> * circleMemoryDB3)
{
    (*pointMemory)[index] = dynamicPoint(0, 0, NO_POINT);
    for (int i=0; i<pointMemory->size(); i++)
    {
        if ((*pointMemory)[i].pType == NO_POINT) continue;

        if (((*pointMemory)[i].defShape1 == POINT && (*pointMemory)[i].defIndex1 == index) || ((*pointMemory)[i].defShape2 == POINT && (*pointMemory)[i].defIndex2 == index) || ((*pointMemory)[i].defShape3 == POINT && (*pointMemory)[i].defIndex3 == index)) deletePoint(i, pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3);
    }
    for (int i=0; i<segmentMemory->size(); i++)
    {
        if ((*segmentMemory)[i].pointIndexA == -1) continue;
        if ((*segmentMemory)[i].pointIndexA == index || (*segmentMemory)[i].pointIndexB == index) deleteSegment(i, pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3);
    }
    for (int i=0; i<lineMemory->size(); i++)
    {
        if ((*lineMemory)[i].pointIndexA == -1) continue;
        if ((*lineMemory)[i].pointIndexA == index || (*lineMemory)[i].pointIndexB == index) deleteLine(i, pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3);
    }
    for (int i=0; i<circleMemoryDB2->size(); i++)
    {
        if ((*circleMemoryDB2)[i].pointIndexA == -1) continue;
        if ((*circleMemoryDB2)[i].pointIndexA == index || (*circleMemoryDB2)[i].pointIndexB == index) deleteCircleDB2(i, pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3);
    }
    for (int i=0; i<circleMemoryDB3->size(); i++)
    {
        if ((*circleMemoryDB3)[i].pointIndexA == -1) continue;
        if ((*circleMemoryDB3)[i].pointIndexA == index || (*circleMemoryDB3)[i].pointIndexB == index || (*circleMemoryDB3)[i].pointIndexC == index) deleteCircleDB3(i, pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3);
    }
}

void deleteSegment(int index, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory, std::vector<dynamicPointIndexes2> * lineMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2, std::vector<dynamicPointIndexes3> * circleMemoryDB3)
{
    (*segmentMemory)[index].pointIndexA = -1;
    (*segmentMemory)[index].pointIndexB = -1;
    for (int i=0; i<pointMemory->size(); i++)
    {
        if ((*pointMemory)[i].pType == NO_POINT) continue;

        if ((*pointMemory)[i].defShape1 == SEGMENT && (*pointMemory)[i].defIndex1 == index ||
            (*pointMemory)[i].defShape2 == SEGMENT && (*pointMemory)[i].defIndex2 == index ||
            (*pointMemory)[i].defShape3 == SEGMENT && (*pointMemory)[i].defIndex3 == index)
                deletePoint(i, pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3);

    }
}

void deleteLine(int index, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory, std::vector<dynamicPointIndexes2> * lineMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2, std::vector<dynamicPointIndexes3> * circleMemoryDB3)
{
    (*lineMemory)[index].pointIndexA = -1;
    (*lineMemory)[index].pointIndexB = -1;
    for (int i=0; i<pointMemory->size(); i++)
    {
        if ((*pointMemory)[i].pType == NO_POINT) continue;

        if ((*pointMemory)[i].defShape1 == LINE && (*pointMemory)[i].defIndex1 == index ||
            (*pointMemory)[i].defShape2 == LINE && (*pointMemory)[i].defIndex2 == index ||
            (*pointMemory)[i].defShape3 == LINE && (*pointMemory)[i].defIndex3 == index)
                deletePoint(i, pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3);
    }
}

void deleteCircleDB2(int index, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory, std::vector<dynamicPointIndexes2> * lineMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2, std::vector<dynamicPointIndexes3> * circleMemoryDB3)
{
    (*circleMemoryDB2)[index].pointIndexA = -1;
    (*circleMemoryDB2)[index].pointIndexB = -1;
    for (int i=0; i<pointMemory->size(); i++)
    {
        if ((*pointMemory)[i].pType == NO_POINT) continue;

        if ((*pointMemory)[i].defShape1 == CIRCLE_DB2 && (*pointMemory)[i].defIndex1 == index ||
            (*pointMemory)[i].defShape2 == CIRCLE_DB2 && (*pointMemory)[i].defIndex2 == index ||
            (*pointMemory)[i].defShape3 == CIRCLE_DB2 && (*pointMemory)[i].defIndex3 == index)
                deletePoint(i, pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3);
    }
}

void deleteCircleDB3(int index, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory, std::vector<dynamicPointIndexes2> * lineMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2, std::vector<dynamicPointIndexes3> * circleMemoryDB3)
{
    (*circleMemoryDB3)[index].pointIndexA = -1;
    (*circleMemoryDB3)[index].pointIndexB = -1;
    (*circleMemoryDB3)[index].pointIndexC = -1;
    for (int i=0; i<pointMemory->size(); i++)
    {
        if ((*pointMemory)[i].pType == NO_POINT) continue;

        if ((*pointMemory)[i].defShape1 == CIRCLE_DB3 && (*pointMemory)[i].defIndex1 == index ||
            (*pointMemory)[i].defShape2 == CIRCLE_DB3 && (*pointMemory)[i].defIndex2 == index ||
            (*pointMemory)[i].defShape3 == CIRCLE_DB3 && (*pointMemory)[i].defIndex3 == index)
                deletePoint(i, pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3);
    }
}
