#include "MemoryManagement.h"

int getNextFreePoint(std::vector<dynamicPoint> * pointMemory)
{
    for (unsigned int i=0; i<pointMemory->size(); i++)
    {
        if (pointMemory->at(i).pType == NO_POINT) return i;
    }
    pointMemory->emplace_back();
    return pointMemory->size()-1;
}
int getNextFreeSegment(std::vector<dynamicPointIndexes2> * segmentMemory)
{
    for (unsigned int i=0; i<segmentMemory->size(); i++)
    {
        if (segmentMemory->at(i).pointIndexA == -1) return i;
    }
    segmentMemory->emplace_back();
    return segmentMemory->size()-1;
}
int getNextFreeLine(std::vector<dynamicPointIndexes2> * lineMemory)
{
    for (unsigned int i=0; i<lineMemory->size(); i++)
    {
        if (lineMemory->at(i).pointIndexA == -1) return i;
    }
    lineMemory->emplace_back();
    return lineMemory->size()-1;
}
int getNextFreeCircleDB2(std::vector<dynamicPointIndexes2> * circleMemoryDB2)
{
    for (unsigned int i=0; i<circleMemoryDB2->size(); i++)
    {
        if (circleMemoryDB2->at(i).pointIndexA == -1) return i;
    }
    circleMemoryDB2->emplace_back();
    return circleMemoryDB2->size()-1;
}
int getNextFreeCircleDB3(std::vector<dynamicPointIndexes3> * circleMemoryDB3)
{
    for (unsigned int i=0; i<circleMemoryDB3->size(); i++)
    {
        if (circleMemoryDB3->at(i).pointIndexA == -1) return i;
    }
    circleMemoryDB3->emplace_back();
    return circleMemoryDB3->size()-1;
}

void cleanTemporaryData(std::vector<dynamicIndex> * indexSelection, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory, std::vector<dynamicPointIndexes2> * lineMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2, std::vector<dynamicPointIndexes3> * circleMemoryDB3)
{
    indexSelection->clear();
    for (int i=0; i<pointMemory->size(); i++)
    {
        if ((*pointMemory)[i].pType < 0)
        {
            (*pointMemory)[i] = dynamicPoint(0, 0, NO_POINT);

            for (unsigned int j=0; j<segmentMemory->size(); j++)
            {
                dynamicPointIndexes2 cur = segmentMemory->at(j);
                if (cur.pointIndexA == i || cur.pointIndexB == i)
                {
                    (*segmentMemory)[j] = dynamicPointIndexes2(-1, -1);
                }
            }
            for (unsigned int j=0; j<lineMemory->size(); j++)
            {
                dynamicPointIndexes2 cur = lineMemory->at(j);
                if (cur.pointIndexA == i || cur.pointIndexB == i)
                {
                    (*lineMemory)[j] = dynamicPointIndexes2(-1, -1);
                }
            }
            for (unsigned int j=0; j<circleMemoryDB2->size(); j++)
            {
                dynamicPointIndexes2 cur = circleMemoryDB2->at(j);
                if (cur.pointIndexA == i || cur.pointIndexB == i)
                {
                    (*circleMemoryDB2)[j] = dynamicPointIndexes2(-1, -1);
                }
            }
            for (unsigned int j=0; j<circleMemoryDB3->size(); j++)
            {
                dynamicPointIndexes3 cur = circleMemoryDB3->at(j);
                if (cur.pointIndexA == i || cur.pointIndexB == i || cur.pointIndexC == i)
                {
                    (*circleMemoryDB3)[j] = dynamicPointIndexes3(-1, -1, -1);
                }
            }
        }
    }
}

void restoreOldPositions(std::vector<pointPos> * oldPointPositions, std::vector<dynamicPoint> * pointMemory)
{
    for (unsigned int i=0; i<oldPointPositions->size(); i++)
    {
        pointPos cur = oldPointPositions->at(i);
        (*pointMemory)[cur.index].coords = GM::Point(cur.x, cur.y);
        (*pointMemory)[cur.index].arg = cur.arg;
    }
    oldPointPositions->clear();
}

dynamicIndex selectObject(double mouseX, double mouseY, std::vector<dynamicIndex> * indexSelection, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory, std::vector<dynamicPointIndexes2> * lineMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2, std::vector<dynamicPointIndexes3> * circleMemoryDB3, double RECOGNISABLE_DISTANCE, const std::set<geometryShape> preferredShape)
{
    std::vector<indexDist> closePoints = findClosestPoint(mouseX, mouseY, pointMemory, RECOGNISABLE_DISTANCE);
    std::vector<indexDist> closeSegments = findClosestSegment(mouseX, mouseY, pointMemory, segmentMemory, RECOGNISABLE_DISTANCE);
    std::vector<indexDist> closeLines = findClosestLine(mouseX, mouseY, pointMemory, lineMemory, RECOGNISABLE_DISTANCE);
    std::vector<indexDist> closeCirclesDB2 = findClosestCircleDB2(mouseX, mouseY, pointMemory, circleMemoryDB2, RECOGNISABLE_DISTANCE);
    std::vector<indexDist> closeCirclesDB3 = findClosestCircleDB3(mouseX, mouseY, pointMemory, circleMemoryDB3, RECOGNISABLE_DISTANCE);
    int szPoints = closePoints.size(), szSegments = closeSegments.size(), szLines = closeLines.size(), szCirclesDB2 = closeCirclesDB2.size(), szCirclesDB3 = closeCirclesDB3.size();
    dynamicIndex ret(-1, NO_SHAPE);
    double bestDist = RECOGNISABLE_DISTANCE + 1000;

    if (preferredShape.find(POINT) != preferredShape.end())
        if (szPoints > 0)
            if (closePoints[0].distance < bestDist)
            {
                ret = dynamicIndex(closePoints[0].index, POINT);
                bestDist = closePoints[0].distance;
                indexSelection->push_back(ret);
                return ret;

            }
    if (preferredShape.find(SEGMENT) != preferredShape.end())
        if (szSegments > 0)
            if (closeSegments[0].distance < bestDist)
            {
                ret = dynamicIndex(closeSegments[0].index, SEGMENT);
                bestDist = closeSegments[0].distance;
            }

    if (preferredShape.find(LINE) != preferredShape.end())
        if (szLines > 0)
            if (closeLines[0].distance < bestDist)
            {
                ret = dynamicIndex(closeLines[0].index, LINE);
                bestDist = closeLines[0].distance;
            }

    if (preferredShape.find(CIRCLE_DB2) != preferredShape.end())
        if (szCirclesDB2 > 0)
            if (closeCirclesDB2[0].distance < bestDist)
            {
                ret = dynamicIndex(closeCirclesDB2[0].index, CIRCLE_DB2);
                bestDist = closeCirclesDB2[0].distance;
            }

    if (preferredShape.find(CIRCLE_DB3) != preferredShape.end())
        if (szCirclesDB3 > 0)
            if (closeCirclesDB3[0].distance < bestDist)
            {
                ret = dynamicIndex(closeCirclesDB3[0].index, CIRCLE_DB3);
                bestDist = closeCirclesDB3[0].distance;
            }

    if (ret.index != -1)
    {
        indexSelection->push_back(ret);
    }
    return ret;
}

int createPoint(double mouseX, double mouseY, std::vector<dynamicIndex> * indexSelection, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory, std::vector<dynamicPointIndexes2> * lineMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2, std::vector<dynamicPointIndexes3> * circleMemoryDB3, double RECOGNISABLE_DISTANCE)
{
    std::vector<indexDist> closePoints = findClosestPoint(mouseX, mouseY, pointMemory, RECOGNISABLE_DISTANCE);
    std::vector<indexDist> closeSegments = findClosestSegment(mouseX, mouseY, pointMemory, segmentMemory, RECOGNISABLE_DISTANCE);
    std::vector<indexDist> closeLines = findClosestLine(mouseX, mouseY, pointMemory, lineMemory, RECOGNISABLE_DISTANCE);
    std::vector<indexDist> closeCirclesDB2 = findClosestCircleDB2(mouseX, mouseY, pointMemory, circleMemoryDB2, RECOGNISABLE_DISTANCE);
    std::vector<indexDist> closeCirclesDB3 = findClosestCircleDB3(mouseX, mouseY, pointMemory, circleMemoryDB3, RECOGNISABLE_DISTANCE);

    if (closePoints.size() > 0) return -1;

    int next = getNextFreePoint(pointMemory);
    int closeObjectsAmount = closeSegments.size() + closeLines.size() + closeCirclesDB2.size() + closeCirclesDB3.size();

    if (closeObjectsAmount == 0)
    {
        (*pointMemory)[next] = dynamicPoint(mouseX, mouseY, FREE);
        return next;
    }

    std::vector<dynamicIndex> closeObjects;
    for (int i=0; i<std::min(int(closePoints.size()), 2); i++) closeObjects.emplace_back(i, POINT);
    for (int i=0; i<std::min(int(closeSegments.size()), 2); i++) closeObjects.emplace_back(i, SEGMENT);
    for (int i=0; i<std::min(int(closeLines.size()), 2); i++) closeObjects.emplace_back(i, LINE);
    for (int i=0; i<std::min(int(closeCirclesDB2.size()), 2); i++) closeObjects.emplace_back(i, CIRCLE_DB2);
    for (int i=0; i<std::min(int(closeCirclesDB3.size()), 2); i++) closeObjects.emplace_back(i, CIRCLE_DB3);

    if (closeObjects.size() == 1)
    {
        if (closeObjects[0].shape == POINT) return createRelativePoint(mouseX, mouseY, dynamicIndex(closePoints[closeObjects[0].index].index, POINT), pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3);
        else if (closeObjects[0].shape == SEGMENT)return createRelativePoint(mouseX, mouseY, dynamicIndex(closeSegments[closeObjects[0].index].index, SEGMENT), pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3);
        else if (closeObjects[0].shape == LINE) return createRelativePoint(mouseX, mouseY, dynamicIndex(closeLines[closeObjects[0].index].index, LINE), pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3);
        else if (closeObjects[0].shape == CIRCLE_DB2) return createRelativePoint(mouseX, mouseY, dynamicIndex(closeCirclesDB2[closeObjects[0].index].index, CIRCLE_DB2), pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3);
        else if (closeObjects[0].shape == CIRCLE_DB3) return createRelativePoint(mouseX, mouseY, dynamicIndex(closeCirclesDB3[closeObjects[0].index].index, CIRCLE_DB3), pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3);
    }

    for (int i=0; i<closeObjects.size(); i++)
    {
        for (int j=closeObjects.size()-2; j>=i; j--)
        {
            double dist1=INT_MAX, dist2=INT_MAX;
            if (closeObjects[j].shape == POINT) dist1 = closePoints[closeObjects[j].index].distance;
            else if (closeObjects[j].shape == SEGMENT) dist1 = closeSegments[closeObjects[j].index].distance;
            else if (closeObjects[j].shape == LINE) dist1 = closeLines[closeObjects[j].index].distance;
            else if (closeObjects[j].shape == CIRCLE_DB2) dist1 = closeCirclesDB2[closeObjects[j].index].distance;
            else if (closeObjects[j].shape == CIRCLE_DB3) dist1 = closeCirclesDB3[closeObjects[j].index].distance;

            if (closeObjects[j+1].shape == POINT) dist2 = closePoints[closeObjects[j+1].index].distance;
            else if (closeObjects[j+1].shape == SEGMENT) dist2 = closeSegments[closeObjects[j+1].index].distance;
            else if (closeObjects[j+1].shape == LINE) dist2 = closeLines[closeObjects[j+1].index].distance;
            else if (closeObjects[j+1].shape == CIRCLE_DB2) dist2 = closeCirclesDB2[closeObjects[j+1].index].distance;
            else if (closeObjects[j+1].shape == CIRCLE_DB3) dist2 = closeCirclesDB3[closeObjects[j+1].index].distance;

            if (dist1 > dist2) std::swap(closeObjects[j], closeObjects[j+1]);
        }
    }

    dynamicIndex object1 = closeObjects[0], object2 = closeObjects[1];

    if (object1.shape == POINT) object1.index = closePoints[object1.index].index;
    else if (object1.shape == SEGMENT) object1.index = closeSegments[object1.index].index;
    else if (object1.shape == LINE) object1.index = closeLines[object1.index].index;
    else if (object1.shape == CIRCLE_DB2) object1.index = closeCirclesDB2[object1.index].index;
    else if (object1.shape == CIRCLE_DB3) object1.index = closeCirclesDB3[object1.index].index;

    if (object2.shape == POINT) object2.index = closePoints[object2.index].index;
    else if (object2.shape == SEGMENT) object2.index = closeSegments[object2.index].index;
    else if (object2.shape == LINE) object2.index = closeLines[object2.index].index;
    else if (object2.shape == CIRCLE_DB2) object2.index = closeCirclesDB2[object2.index].index;
    else if (object2.shape == CIRCLE_DB3) object2.index = closeCirclesDB3[object2.index].index;

    if ((object1.shape == LINE || object1.shape == SEGMENT) && (object2.shape == LINE || object2.shape == SEGMENT))
    {
        GM::Point crossP;
        GM::Line l1, l2;

        if (object1.shape == LINE) l1 = DTSLine(object1.index, pointMemory, lineMemory);
        else l1 = GM::Line(DTSSegment(object1.index, pointMemory, segmentMemory));
        if (object2.shape == LINE) l2 = DTSLine(object2.index, pointMemory, lineMemory);
        else l2 = GM::Line(DTSSegment(object2.index, pointMemory, segmentMemory));

        if (l1.getB() == l2.getB())
        {
            (*pointMemory)[next] = dynamicPoint(mouseX, mouseY, FREE);
            return next;
        }
        crossP = crossPoints(l1, l2)[0];
        if (distanceBetweenPoints(crossP, GM::Point(mouseX, mouseY)) > RECOGNISABLE_DISTANCE)
        {
            return createRelativePoint(mouseX, mouseY, closeObjects[0], pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3);
        }
        (*pointMemory)[next] = dynamicPoint(mouseX, mouseY, LOCKED_CROSSPOINT, object1.shape, object2.shape, object1.index, object2.index);
        return next;
    }
    else if (object1.shape == CIRCLE_DB2 || object1.shape == CIRCLE_DB3 || object2.shape == CIRCLE_DB2 || object2.shape == CIRCLE_DB3)
    {
        if (object1.shape == LINE || object1.shape == SEGMENT || object2.shape == LINE || object2.shape == SEGMENT)
        {
            GM::Circle c;
            GM::Line l;
            GM::Point defPoint1, defPoint2;

            if (object1.shape == LINE)
            {
                l = DTSLine(object1.index, pointMemory, lineMemory);
                defPoint1 = DTSPoint( (*lineMemory)[object1.index].pointIndexA, pointMemory );
                defPoint2 = DTSPoint( (*lineMemory)[object1.index].pointIndexB, pointMemory );
            }
            else if (object1.shape == SEGMENT)
            {
                l = GM::Line(DTSSegment(object1.index, pointMemory, segmentMemory));
                defPoint1 = DTSPoint( (*segmentMemory)[object1.index].pointIndexA, pointMemory );
                defPoint2 = DTSPoint( (*segmentMemory)[object1.index].pointIndexB, pointMemory );
            }
            else if (object2.shape == LINE)
            {
                l = DTSLine(object2.index, pointMemory, lineMemory);
                defPoint1 = DTSPoint( (*lineMemory)[object2.index].pointIndexA, pointMemory );
                defPoint2 = DTSPoint( (*lineMemory)[object2.index].pointIndexB, pointMemory );
            }
            else if (object2.shape == SEGMENT)
            {
                l = GM::Line(DTSSegment(object2.index, pointMemory, segmentMemory));
                defPoint1 = DTSPoint( (*segmentMemory)[object2.index].pointIndexA, pointMemory );
                defPoint2 = DTSPoint( (*segmentMemory)[object2.index].pointIndexB, pointMemory );
            }

            if (object1.shape == CIRCLE_DB2)      c = DTSCircleDB2(object1.index, pointMemory, circleMemoryDB2);
            else if (object1.shape == CIRCLE_DB3) c = DTSCircleDB3(object1.index, pointMemory, circleMemoryDB3);
            else if (object2.shape == CIRCLE_DB2) c = DTSCircleDB2(object2.index, pointMemory, circleMemoryDB2);
            else if (object2.shape == CIRCLE_DB3) c = DTSCircleDB3(object2.index, pointMemory, circleMemoryDB3);

            std::vector<GM::Point> CP = crossPoints(c, l);

            if (CP.size() == 0)
            {
                return createRelativePoint(mouseX, mouseY, closeObjects[0], pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3);
            }
            else
            {
                (*pointMemory)[next] = dynamicPoint(0, 0, LOCKED_CROSSPOINT, object1.shape, object2.shape, object1.index, object2.index);

                if (CP.size() == 2)
                {
                    int best = -1;
                    if (distanceBetweenPoints(GM::Point(mouseX, mouseY), CP[0]) <= distanceBetweenPoints(GM::Point(mouseX, mouseY), CP[1])) best = 0;
                    else best = 1;

                    if (l.straight())
                    {
                        if ( (CP[best].y < CP[1-best].y && defPoint1.y < defPoint2.y) || (CP[best].y > CP[1-best].y && defPoint1.y > defPoint2.y)) (*pointMemory)[next].arg = 0;
                        else (*pointMemory)[next].arg = 1;
                    }
                    else
                    {
                        if ( (CP[best].x < CP[1-best].x && defPoint1.x < defPoint2.x) || (CP[best].x > CP[1-best].x && defPoint1.x > defPoint2.x)) (*pointMemory)[next].arg = 0;
                        else (*pointMemory)[next].arg = 1;
                    }
                }

                return next;
            }
        }
        else if ((object1.shape == CIRCLE_DB2 || object1.shape == CIRCLE_DB3) && (object2.shape == CIRCLE_DB2 || object2.shape == CIRCLE_DB3))
        {
            GM::Circle c1, c2;
            if (object1.shape == CIRCLE_DB2)      c1 = DTSCircleDB2(object1.index, pointMemory, circleMemoryDB2);
            else if (object1.shape == CIRCLE_DB3) c1 = DTSCircleDB3(object1.index, pointMemory, circleMemoryDB3);
            if (object2.shape == CIRCLE_DB2)      c2 = DTSCircleDB2(object2.index, pointMemory, circleMemoryDB2);
            else if (object2.shape == CIRCLE_DB3) c2 = DTSCircleDB3(object2.index, pointMemory, circleMemoryDB3);

            std::vector<GM::Point> CP = crossPoints(c1, c2);

            if (CP.size() == 2)
            {
                GM::Vector v = c2.center.toVector() - c1.center.toVector(), v1 = CP[0].toVector() - c1.center.toVector(), v2 = CP[1].toVector() - c1.center.toVector();
                double an = atan2(v.y, v.x), an1 = atan2(v1.y, v1.x), an2 = atan2(v2.y, v2.x);
                if (an < 0) an+=2*PI;
                if (an1 < 0) an1+=2*PI;
                if (an2 < 0) an2+=2*PI;

                if ((an1 > an2 && an2 > an) || (an2 > an && an > an1) || (an > an1 && an1 > an2)) std::swap(CP[0], CP[1]);

                (*pointMemory)[next] = dynamicPoint(0, 0, LOCKED_CROSSPOINT, object1.shape, object2.shape, object1.index, object2.index);

                if (distanceBetweenPoints(GM::Point(mouseX, mouseY), CP[0]) < distanceBetweenPoints(GM::Point(mouseX, mouseY), CP[1])) (*pointMemory)[next].arg = 0;
                else (*pointMemory)[next].arg = 1;

                return next;
            }
            else
            {
                return createRelativePoint(mouseX, mouseY, closeObjects[0], pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3);
            }
        }
    }

    (*pointMemory)[next] = dynamicPoint(mouseX, mouseY, FREE);
    return next;
}

int createRelativePoint(double mouseX, double mouseY, dynamicIndex object, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory, std::vector<dynamicPointIndexes2> * lineMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2, std::vector<dynamicPointIndexes3> * circleMemoryDB3)
{
    std::cout<<object.index<<" "<<object.shape<<std::endl;
    int index = getNextFreePoint(pointMemory);
    (*pointMemory)[index] = dynamicPoint(0, 0, RELATIVE, object.shape, object.index);
    switch (object.shape)
    {
        case LINE:
        {
            GM::Line l = DTSLine(object.index, pointMemory, lineMemory);
            GM::Segment alt = altitude(l, GM::Point(mouseX, mouseY));
            GM::Point p1 = DTSPoint((*lineMemory)[object.index].pointIndexA, pointMemory), p2 = DTSPoint((*lineMemory)[object.index].pointIndexB, pointMemory);
            double dx = p2.x - p1.x, dy = p2.y - p1.y, dx2 = alt.b.x - p1.x, dy2 = alt.b.y - p1.x;
            if (dx == 0 || dy == 0) break;
            if (l.straight())
            {
                (*pointMemory)[index].arg = dy2/dy;
            }
            else
            {
                (*pointMemory)[index].arg = dx2/dx;
            }
            break;
        }
        case SEGMENT:
        {
            GM::Line l = GM::Line(DTSSegment(object.index, pointMemory, segmentMemory));
            GM::Segment alt = altitude(l, GM::Point(mouseX, mouseY));
            GM::Point p1 = DTSPoint((*segmentMemory)[object.index].pointIndexA, pointMemory), p2 = DTSPoint((*segmentMemory)[object.index].pointIndexB, pointMemory);
            double dx = p2.x - p1.x, dy = p2.y - p1.y, dx2 = alt.b.x - p1.x, dy2 = alt.b.y - p1.x;
            if (dx == 0 || dy == 0) break;
            if (l.straight())
            {
                (*pointMemory)[index].arg = dy2/dy;
            }
            else
            {
                (*pointMemory)[index].arg = dx2/dx;
            }
            break;
        }
        case CIRCLE_DB2:
        {
            GM::Circle c = DTSCircleDB2(object.index, pointMemory, circleMemoryDB2);
            std::vector<GM::Point> pts = crossPoints(c, GM::Line(c.center, GM::Point(mouseX, mouseY)));
            GM::Point p = pts[0];
            if (distanceBetweenPoints(GM::Point(mouseX, mouseY), pts[0]) > distanceBetweenPoints(GM::Point(mouseX, mouseY), pts[1])) p = pts[1];
            (*pointMemory)[index].arg = atan2(p.y - c.center.y, p.x - c.center.x);
            break;
        }
        case CIRCLE_DB3:
        {
            GM::Circle c = DTSCircleDB3(object.index, pointMemory, circleMemoryDB3);
            std::vector<GM::Point> pts = crossPoints(c, GM::Line(c.center, GM::Point(mouseX, mouseY)));
            GM::Point p = pts[0];
            if (distanceBetweenPoints(GM::Point(mouseX, mouseY), pts[0]) > distanceBetweenPoints(GM::Point(mouseX, mouseY), pts[1])) p = pts[1];
            (*pointMemory)[index].arg = atan2(p.y - c.center.y, p.x - c.center.x);
            break;
        }
        default:
            break;
    }
    return index;
}

int createSegment(double mouseX, double mouseY, std::vector<dynamicIndex> * indexSelection, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory, std::vector<dynamicPointIndexes2> * lineMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2, std::vector<dynamicPointIndexes3> * circleMemoryDB3, double RECOGNISABLE_DISTANCE)
{
    if (indexSelection->size() == 0)
    {
        std::vector<indexDist> closePoints = findClosestPoint(mouseX, mouseY, pointMemory, RECOGNISABLE_DISTANCE);
        if (closePoints.size() > 0)
        {
            indexSelection->emplace_back(closePoints[0].index, POINT);
        }
        else
        {
            int next = createPoint(mouseX, mouseY, indexSelection, pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3, RECOGNISABLE_DISTANCE);
            fromPermToTemp(&(*pointMemory)[next].pType);
            indexSelection->emplace_back(next, POINT);
        }
        return -1;
    }
    else if (indexSelection->size() == 1)
    {
        std::vector<indexDist> closePoints = findClosestPoint(mouseX, mouseY, pointMemory, RECOGNISABLE_DISTANCE);
        int next = getNextFreeSegment(segmentMemory);
        if (closePoints.size() > 0)
        {
            if (indexSelection->at(0).index == closePoints[0].index)
            {
                return -1;
            }
            (*segmentMemory)[next] = dynamicPointIndexes2(indexSelection->at(0).index, closePoints[0].index);
        }
        else
        {
            int newPoint = createPoint(mouseX, mouseY, indexSelection, pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3, RECOGNISABLE_DISTANCE);
            (*segmentMemory)[next] = dynamicPointIndexes2(indexSelection->at(0).index, newPoint);
        }
        fromTempToPerm(&(*pointMemory)[indexSelection->at(0).index].pType);
        indexSelection->clear();
        return next;
    }
    return -2;
}

int createLine(double mouseX, double mouseY, std::vector<dynamicIndex> * indexSelection, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory, std::vector<dynamicPointIndexes2> * lineMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2, std::vector<dynamicPointIndexes3> * circleMemoryDB3, double RECOGNISABLE_DISTANCE)
{
    if (indexSelection->size() == 0)
    {
        std::vector<indexDist> closePoints = findClosestPoint(mouseX, mouseY, pointMemory, RECOGNISABLE_DISTANCE);
        if (closePoints.size() > 0)
        {
            indexSelection->emplace_back(closePoints[0].index, POINT);
        }
        else
        {
            int next = createPoint(mouseX, mouseY, indexSelection, pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3, RECOGNISABLE_DISTANCE);
            fromPermToTemp(&(*pointMemory)[next].pType);
            indexSelection->emplace_back(next, POINT);
        }
        return -1;
    }
    else if (indexSelection->size() == 1)
    {
        std::vector<indexDist> closePoints = findClosestPoint(mouseX, mouseY, pointMemory, RECOGNISABLE_DISTANCE);
        int next = getNextFreeLine(lineMemory);
        if (closePoints.size() > 0)
        {
            if (indexSelection->at(0).index == closePoints[0].index) return -1;
            (*lineMemory)[next] = dynamicPointIndexes2(indexSelection->at(0).index, closePoints[0].index);
        }
        else
        {
            int newPoint = createPoint(mouseX, mouseY, indexSelection, pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3, RECOGNISABLE_DISTANCE);
            (*lineMemory)[next] = dynamicPointIndexes2(indexSelection->at(0).index, newPoint);
        }
        fromTempToPerm(&(*pointMemory)[indexSelection->at(0).index].pType);
        indexSelection->clear();
        return next;
    }
    return -2;
}

int createCircleDB2(double mouseX, double mouseY, std::vector<dynamicIndex> * indexSelection, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory, std::vector<dynamicPointIndexes2> * lineMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2, std::vector<dynamicPointIndexes3> * circleMemoryDB3, double RECOGNISABLE_DISTANCE)
{
    if (indexSelection->size() == 0)
    {
        std::vector<indexDist> closePoints = findClosestPoint(mouseX, mouseY, pointMemory, RECOGNISABLE_DISTANCE);
        if (closePoints.size() > 0)
        {
            indexSelection->emplace_back(closePoints[0].index, POINT);
        }
        else
        {
            int next = createPoint(mouseX, mouseY, indexSelection, pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3, RECOGNISABLE_DISTANCE);
            fromPermToTemp(&(*pointMemory)[next].pType);
            indexSelection->emplace_back(next, POINT);
        }
        return -1;
    }
    else if (indexSelection->size() == 1)
    {
        std::vector<indexDist> closePoints = findClosestPoint(mouseX, mouseY, pointMemory, RECOGNISABLE_DISTANCE);
        int next = getNextFreeCircleDB2(circleMemoryDB2);
        if (closePoints.size() > 0)
        {
            if (indexSelection->at(0).index == closePoints[0].index) return -1;
            (*circleMemoryDB2)[next] = dynamicPointIndexes2(indexSelection->at(0).index, closePoints[0].index);
        }
        else
        {
            int newPoint = createPoint(mouseX, mouseY, indexSelection, pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3, RECOGNISABLE_DISTANCE);
            (*circleMemoryDB2)[next] = dynamicPointIndexes2(indexSelection->at(0).index, newPoint);
        }
        fromTempToPerm(&(*pointMemory)[indexSelection->at(0).index].pType);
        indexSelection->clear();
        return next;
    }
    return -2;
}

int createCircleDB3(double mouseX, double mouseY, std::vector<dynamicIndex> * indexSelection, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory, std::vector<dynamicPointIndexes2> * lineMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2, std::vector<dynamicPointIndexes3> * circleMemoryDB3, double RECOGNISABLE_DISTANCE)
{
    if (indexSelection->size() == 0)
    {
        std::vector<indexDist> closePoints = findClosestPoint(mouseX, mouseY, pointMemory, RECOGNISABLE_DISTANCE);
        if (closePoints.size() > 0)
        {
            indexSelection->emplace_back(closePoints[0].index, POINT);
        }
        else
        {
            int next = createPoint(mouseX, mouseY, indexSelection, pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3, RECOGNISABLE_DISTANCE);
            fromPermToTemp(&(*pointMemory)[next].pType);
            indexSelection->emplace_back(next, POINT);
        }
        return -1;
    }
    else if (indexSelection->size() == 1)
    {
        std::vector<indexDist> closePoints = findClosestPoint(mouseX, mouseY, pointMemory, RECOGNISABLE_DISTANCE);
        if (closePoints.size() > 0)
        {
            if (indexSelection->at(0).index == closePoints[0].index) return -1;
            indexSelection->emplace_back(closePoints[0].index, POINT);
        }
        else
        {
            int next = createPoint(mouseX, mouseY, indexSelection, pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3, RECOGNISABLE_DISTANCE);
            fromPermToTemp(&(*pointMemory)[next].pType);
            indexSelection->emplace_back(next, POINT);
        }
        return -1;
    }
    else if (indexSelection->size() == 2)
    {
        std::vector<indexDist> closePoints = findClosestPoint(mouseX, mouseY, pointMemory, RECOGNISABLE_DISTANCE);
        int next = getNextFreeCircleDB3(circleMemoryDB3);
        if (closePoints.size() > 0)
        {
            if (indexSelection->at(0).index == closePoints[0].index) return -1;
            if (indexSelection->at(1).index == closePoints[0].index) return -1;
            (*circleMemoryDB3)[next] = dynamicPointIndexes3(indexSelection->at(0).index, indexSelection->at(1).index, closePoints[0].index);
        }
        else
        {
            int newPoint = createPoint(mouseX, mouseY, indexSelection, pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3, RECOGNISABLE_DISTANCE);
            (*circleMemoryDB3)[next] = dynamicPointIndexes3(indexSelection->at(0).index, indexSelection->at(1).index, newPoint);
        }
        fromTempToPerm(&(*pointMemory)[indexSelection->at(0).index].pType);
        fromTempToPerm(&(*pointMemory)[indexSelection->at(1).index].pType);
        indexSelection->clear();
        return next;
    }
    return -2;
}

int createAltitude(double mouseX, double mouseY, std::vector<dynamicIndex> * indexSelection, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory, std::vector<dynamicPointIndexes2> * lineMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2, std::vector<dynamicPointIndexes3> * circleMemoryDB3, double RECOGNISABLE_DISTANCE)
{

    if (indexSelection->size() == 0)
    {
        const std::set<geometryShape> preferred = {POINT, LINE, SEGMENT};
        dynamicIndex ret = selectObject(mouseX, mouseY, indexSelection, pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3, RECOGNISABLE_DISTANCE, preferred);
        if (ret.shape == NO_SHAPE)
        {
            int nextp = createPoint(mouseX, mouseY, indexSelection, pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3, RECOGNISABLE_DISTANCE);
            indexSelection->emplace_back(nextp, POINT);
            fromPermToTemp(&(*pointMemory)[nextp].pType);
        }
        else
        {
            // Do nothing cause it selected it automatically
        }
    }
    else if (indexSelection->size() == 1)
    {
        int nextPoint = getNextFreePoint(pointMemory);
        int nextSegment = getNextFreeSegment(segmentMemory);
        if ((*indexSelection)[0].shape == POINT)
        {
            const std::set<geometryShape> preferred = {LINE, SEGMENT};
            dynamicIndex ret = selectObject(mouseX, mouseY, indexSelection, pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3, RECOGNISABLE_DISTANCE, preferred);
            if (ret.shape == NO_SHAPE) return -1;
            (*pointMemory)[nextPoint] = dynamicPoint(0, 0, LOCKED_ALTITUDE_FOOT, ret.shape, (*indexSelection)[0].shape, ret.index, (*indexSelection)[0].index);
            (*segmentMemory)[nextSegment] = dynamicPointIndexes2((*indexSelection)[0].index, nextPoint);

            fromTempToPerm(&(*pointMemory)[indexSelection->at(0).index].pType);
        }
        else
        {
            const std::set<geometryShape> preferred = {POINT};
            dynamicIndex ret = selectObject(mouseX, mouseY, indexSelection, pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3, RECOGNISABLE_DISTANCE, preferred);
            if (ret.shape == NO_SHAPE)
            {
                (*pointMemory)[nextPoint] = dynamicPoint(0, 0);
                int nextp = createPoint(mouseX, mouseY, indexSelection, pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3, RECOGNISABLE_DISTANCE);
                (*pointMemory)[nextPoint] = dynamicPoint(0, 0, LOCKED_ALTITUDE_FOOT, POINT, (*indexSelection)[0].shape, nextp, (*indexSelection)[0].index);
                (*segmentMemory)[nextSegment] = dynamicPointIndexes2(nextp, nextPoint);
            }
            else
            {
                (*pointMemory)[nextPoint] = dynamicPoint(0, 0, LOCKED_ALTITUDE_FOOT, (*indexSelection)[0].shape, (*indexSelection)[1].shape, (*indexSelection)[0].index, (*indexSelection)[1].index);
                (*segmentMemory)[nextSegment] = dynamicPointIndexes2(nextPoint, (*indexSelection)[1].index);
            }
        }
        indexSelection->clear();
    }
    return -2;
}

int createMidpoint(double mouseX, double mouseY, std::vector<dynamicIndex> * indexSelection, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory, std::vector<dynamicPointIndexes2> * lineMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2, std::vector<dynamicPointIndexes3> * circleMemoryDB3, double RECOGNISABLE_DISTANCE)
{
    if (indexSelection->size() == 0)
    {
        const std::set<geometryShape> preferred = {POINT};
        dynamicIndex ret = selectObject(mouseX, mouseY, indexSelection, pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3, RECOGNISABLE_DISTANCE, preferred);
        if (ret.shape == NO_SHAPE)
        {
            int nextp = createPoint(mouseX, mouseY, indexSelection, pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3, RECOGNISABLE_DISTANCE);
            indexSelection->emplace_back(nextp, POINT);
            fromPermToTemp(&(*pointMemory)[nextp].pType);
        }
        else
        {
            //it selected it automatically
        }
    }
    else if (indexSelection->size() == 1)
    {
        int nextPoint = getNextFreePoint(pointMemory);
        const std::set<geometryShape> preferred = {POINT};
        dynamicIndex ret = selectObject(mouseX, mouseY, indexSelection, pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3, RECOGNISABLE_DISTANCE, preferred);
        if (ret.shape == POINT)
        {
            (*pointMemory)[nextPoint] = dynamicPoint(0, 0, LOCKED_MIDPOINT, (*indexSelection)[0].shape, (*indexSelection)[1].shape, (*indexSelection)[0].index, (*indexSelection)[1].index);
        }
        else
        {
            (*pointMemory)[nextPoint] = dynamicPoint(0, 0);
            int nextp = createPoint(mouseX, mouseY, indexSelection, pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3, RECOGNISABLE_DISTANCE);
            (*pointMemory)[nextPoint] = dynamicPoint(0, 0, LOCKED_MIDPOINT, POINT, (*indexSelection)[0].shape, nextp, (*indexSelection)[0].index);
        }
        fromTempToPerm(&(*pointMemory)[indexSelection->at(0).index].pType);
        indexSelection->clear();
    }
    return -2;
}

int createPerpendicularBisector(double mouseX, double mouseY, std::vector<dynamicIndex> * indexSelection, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory, std::vector<dynamicPointIndexes2> * lineMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2, std::vector<dynamicPointIndexes3> * circleMemoryDB3, double RECOGNISABLE_DISTANCE)
{
    if (indexSelection->size() == 0)
    {
        const std::set<geometryShape> preferred = {POINT};
        dynamicIndex ret = selectObject(mouseX, mouseY, indexSelection, pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3, RECOGNISABLE_DISTANCE, preferred);
        if (ret.shape == NO_SHAPE)
        {
            int nextp = createPoint(mouseX, mouseY, indexSelection, pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3, RECOGNISABLE_DISTANCE);
            indexSelection->emplace_back(nextp, POINT);
            fromPermToTemp(&(*pointMemory)[nextp].pType);
        }
        else
        {
            //it selected it automatically
        }
    }
    else if (indexSelection->size() == 1)
    {
        int nextPoint1 = getNextFreePoint(pointMemory);
        (*pointMemory)[nextPoint1] = dynamicPoint(0, 0);
        int nextPoint2 = getNextFreePoint(pointMemory);
        (*pointMemory)[nextPoint2] = dynamicPoint(0, 0);
        int nextLine = getNextFreeLine(lineMemory);
        const std::set<geometryShape> preferred = {POINT};
        dynamicIndex ret = selectObject(mouseX, mouseY, indexSelection, pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3, RECOGNISABLE_DISTANCE, preferred);
        if (ret.shape == POINT)
        {
            (*pointMemory)[nextPoint1] = dynamicPoint(0, 0, LOCKED_MIDPOINT, (*indexSelection)[0].shape, (*indexSelection)[1].shape, (*indexSelection)[0].index, (*indexSelection)[1].index);
            (*pointMemory)[nextPoint2] = dynamicPoint(0, 0, LOCKED_PERPENDICULAR_BISECTOR, (*indexSelection)[0].shape, (*indexSelection)[1].shape, (*indexSelection)[0].index, (*indexSelection)[1].index);
        }
        else
        {

            int nextp = createPoint(mouseX, mouseY, indexSelection, pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3, RECOGNISABLE_DISTANCE);
            (*pointMemory)[nextPoint1] = dynamicPoint(0, 0, LOCKED_MIDPOINT, POINT, (*indexSelection)[0].shape, nextp, (*indexSelection)[0].index);
            (*pointMemory)[nextPoint2] = dynamicPoint(0, 0, LOCKED_PERPENDICULAR_BISECTOR, POINT, (*indexSelection)[0].shape, nextp, (*indexSelection)[0].index);
        }
        (*pointMemory)[nextPoint1].interactable = false;
        (*pointMemory)[nextPoint1].visible = false;
        (*pointMemory)[nextPoint2].interactable = false;
        (*pointMemory)[nextPoint2].visible = false;
        (*lineMemory)[nextLine] = dynamicPointIndexes2(nextPoint1, nextPoint2);
        fromTempToPerm(&(*pointMemory)[indexSelection->at(0).index].pType);
        indexSelection->clear();
    }
    return -2;
}

int createAngleBisector(double mouseX, double mouseY, std::vector<dynamicIndex> * indexSelection, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory, std::vector<dynamicPointIndexes2> * lineMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2, std::vector<dynamicPointIndexes3> * circleMemoryDB3, double RECOGNISABLE_DISTANCE)
{
    if (indexSelection->size() == 0)
    {
        std::vector<indexDist> closePoints = findClosestPoint(mouseX, mouseY, pointMemory, RECOGNISABLE_DISTANCE);
        if (closePoints.size() > 0)
        {
            indexSelection->emplace_back(closePoints[0].index, POINT);
        }
        else
        {
            int next = createPoint(mouseX, mouseY, indexSelection, pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3, RECOGNISABLE_DISTANCE);
            fromPermToTemp(&(*pointMemory)[next].pType);
            indexSelection->emplace_back(next, POINT);
        }
        return -1;
    }
    else if (indexSelection->size() == 1)
    {
        std::vector<indexDist> closePoints = findClosestPoint(mouseX, mouseY, pointMemory, RECOGNISABLE_DISTANCE);
        if (closePoints.size() > 0)
        {
            if (indexSelection->at(0).index == closePoints[0].index) return -1;
            indexSelection->emplace_back(closePoints[0].index, POINT);
        }
        else
        {
            int next = createPoint(mouseX, mouseY, indexSelection, pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3, RECOGNISABLE_DISTANCE);
            fromPermToTemp(&(*pointMemory)[next].pType);
            indexSelection->emplace_back(next, POINT);
        }
        return -1;
    }
    else if (indexSelection->size() == 2)
    {
        std::vector<indexDist> closePoints = findClosestPoint(mouseX, mouseY, pointMemory, RECOGNISABLE_DISTANCE);

        int nextPoint1 = getNextFreePoint(pointMemory);
        (*pointMemory)[nextPoint1] = dynamicPoint(0, 0);
        int nextPoint2 = getNextFreePoint(pointMemory);
        (*pointMemory)[nextPoint2] = dynamicPoint(0, 0);

        int nextLine1 = getNextFreeLine(lineMemory);
        (*lineMemory)[nextLine1] = dynamicPointIndexes2((*indexSelection)[0].index, (*indexSelection)[1].index);
        int nextLine2 = getNextFreeLine(lineMemory);
        (*lineMemory)[nextLine2] = dynamicPointIndexes2(0, 0);

        int nextLine = getNextFreeLine(lineMemory);

        if (closePoints.size() > 0)
        {
            if (indexSelection->at(0).index == closePoints[0].index) return -1;
            if (indexSelection->at(1).index == closePoints[0].index) return -1;

            (*pointMemory)[nextPoint1] = dynamicPoint(0, 0, LOCKED_ANGLE_BISECTOR, POINT, POINT, POINT, (*indexSelection)[0].index, (*indexSelection)[1].index, closePoints[0].index);
            (*lineMemory)[nextLine2] = dynamicPointIndexes2((*indexSelection)[1].index, closePoints[0].index);
            (*pointMemory)[nextPoint2] = dynamicPoint(0, 0, LOCKED_CROSSPOINT, LINE, LINE, nextLine1, nextLine2);
        }
        else
        {
            int newPoint = createPoint(mouseX, mouseY, indexSelection, pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3, RECOGNISABLE_DISTANCE);

            (*pointMemory)[nextPoint1] = dynamicPoint(0, 0, LOCKED_ANGLE_BISECTOR, POINT, POINT, POINT, (*indexSelection)[0].index, (*indexSelection)[1].index, newPoint);
            (*lineMemory)[nextLine2] = dynamicPointIndexes2((*indexSelection)[1].index, newPoint);
            (*pointMemory)[nextPoint2] = dynamicPoint(0, 0, LOCKED_CROSSPOINT, LINE, LINE, nextLine1, nextLine2);
        }
        (*lineMemory)[nextLine] = dynamicPointIndexes2(nextPoint1, nextPoint2);

        (*pointMemory)[nextPoint1].interactable = false;
        (*pointMemory)[nextPoint1].visible = false;
        (*pointMemory)[nextPoint2].interactable = false;
        (*pointMemory)[nextPoint2].visible = false;
        (*lineMemory)[nextLine1].interactable = false;
        (*lineMemory)[nextLine1].visible = false;
        (*lineMemory)[nextLine2].interactable = false;
        (*lineMemory)[nextLine2].visible = false;

        fromTempToPerm(&(*pointMemory)[indexSelection->at(0).index].pType);
        fromTempToPerm(&(*pointMemory)[indexSelection->at(1).index].pType);
        indexSelection->clear();
        return nextLine;
    }
    return -2;
}

int createOutsideAngleBisector(double mouseX, double mouseY, std::vector<dynamicIndex> * indexSelection, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory, std::vector<dynamicPointIndexes2> * lineMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2, std::vector<dynamicPointIndexes3> * circleMemoryDB3, double RECOGNISABLE_DISTANCE)
{
    if (indexSelection->size() == 0)
    {
        std::vector<indexDist> closePoints = findClosestPoint(mouseX, mouseY, pointMemory, RECOGNISABLE_DISTANCE);
        if (closePoints.size() > 0)
        {
            indexSelection->emplace_back(closePoints[0].index, POINT);
        }
        else
        {
            int next = createPoint(mouseX, mouseY, indexSelection, pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3, RECOGNISABLE_DISTANCE);
            fromPermToTemp(&(*pointMemory)[next].pType);
            indexSelection->emplace_back(next, POINT);
        }
        return -1;
    }
    else if (indexSelection->size() == 1)
    {
        std::vector<indexDist> closePoints = findClosestPoint(mouseX, mouseY, pointMemory, RECOGNISABLE_DISTANCE);
        if (closePoints.size() > 0)
        {
            if (indexSelection->at(0).index == closePoints[0].index) return -1;
            indexSelection->emplace_back(closePoints[0].index, POINT);
        }
        else
        {
            int next = createPoint(mouseX, mouseY, indexSelection, pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3, RECOGNISABLE_DISTANCE);
            fromPermToTemp(&(*pointMemory)[next].pType);
            indexSelection->emplace_back(next, POINT);
        }
        return -1;
    }
    else if (indexSelection->size() == 2)
    {
        std::vector<indexDist> closePoints = findClosestPoint(mouseX, mouseY, pointMemory, RECOGNISABLE_DISTANCE);

        int nextPoint1 = getNextFreePoint(pointMemory);
        (*pointMemory)[nextPoint1] = dynamicPoint(0, 0);
        int nextPoint2 = getNextFreePoint(pointMemory);
        (*pointMemory)[nextPoint2] = dynamicPoint(0, 0);

        int nextLine1 = getNextFreeLine(lineMemory);
        (*lineMemory)[nextLine1] = dynamicPointIndexes2((*indexSelection)[0].index, (*indexSelection)[1].index);
        int nextLine2 = getNextFreeLine(lineMemory);
        (*lineMemory)[nextLine2] = dynamicPointIndexes2(0, 0);

        int nextLine = getNextFreeLine(lineMemory);

        if (closePoints.size() > 0)
        {
            if (indexSelection->at(0).index == closePoints[0].index) return -1;
            if (indexSelection->at(1).index == closePoints[0].index) return -1;

            (*pointMemory)[nextPoint1] = dynamicPoint(0, 0, LOCKED_OUTSIDE_ANGLE_BISECTOR, POINT, POINT, POINT, (*indexSelection)[0].index, (*indexSelection)[1].index, closePoints[0].index);
            (*lineMemory)[nextLine2] = dynamicPointIndexes2((*indexSelection)[1].index, closePoints[0].index);
        }
        else
        {
            int newPoint = createPoint(mouseX, mouseY, indexSelection, pointMemory, segmentMemory, lineMemory, circleMemoryDB2, circleMemoryDB3, RECOGNISABLE_DISTANCE);

            (*pointMemory)[nextPoint1] = dynamicPoint(0, 0, LOCKED_OUTSIDE_ANGLE_BISECTOR, POINT, POINT, POINT, (*indexSelection)[0].index, (*indexSelection)[1].index, newPoint);
            (*lineMemory)[nextLine2] = dynamicPointIndexes2((*indexSelection)[1].index, newPoint);
        }
        (*pointMemory)[nextPoint2] = dynamicPoint(0, 0, LOCKED_CROSSPOINT, LINE, LINE, nextLine1, nextLine2);

        (*lineMemory)[nextLine] = dynamicPointIndexes2(nextPoint1, nextPoint2);

        (*pointMemory)[nextPoint1].interactable = false;
        (*pointMemory)[nextPoint1].visible = false;
        (*pointMemory)[nextPoint2].interactable = false;
        (*pointMemory)[nextPoint2].visible = false;
        (*lineMemory)[nextLine1].interactable = false;
        (*lineMemory)[nextLine1].visible = false;
        (*lineMemory)[nextLine2].interactable = false;
        (*lineMemory)[nextLine2].visible = false;

        fromTempToPerm(&(*pointMemory)[indexSelection->at(0).index].pType);
        fromTempToPerm(&(*pointMemory)[indexSelection->at(1).index].pType);
        indexSelection->clear();
        return nextLine;
    }
}
