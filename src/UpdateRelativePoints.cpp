#include "UpdateRelativePoints.h"

void updateRelativePoints(std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory, std::vector<dynamicPointIndexes2> * lineMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2, std::vector<dynamicPointIndexes3> * circleMemoryDB3)
{
    int totalPoints = pointMemory->size(), donePoints = 0;
    bool points[totalPoints];
    for (int i=0; i<totalPoints; i++)
    {
        if ((*pointMemory)[i].pType == FREE || (*pointMemory)[i].pType == NO_POINT)
        {
            donePoints++;
            points[i] = true;
        }
        else points[i] = false;
    }
    while (donePoints < totalPoints)
    {
        for (int i=0; i<totalPoints; i++)
        {
            if (points[i] == true) continue;

            dynamicPoint curPoint = (*pointMemory)[i];
            fromTempToPerm(&curPoint.pType);

            switch(curPoint.pType)
            {
                case RELATIVE:
                {
                    if (curPoint.defShape1 == CIRCLE_DB2)
                    {
                        GM::Circle c = DTSCircleDB2(curPoint.defIndex1, pointMemory, circleMemoryDB2);
                        double an = curPoint.arg;
                        (*pointMemory)[i].coords = c.center + c.radius*GM::Vector(cos(an), sin(an));
                    }
                    else if (curPoint.defShape1 == CIRCLE_DB3)
                    {
                        GM::Circle c = DTSCircleDB3(curPoint.defIndex1, pointMemory, circleMemoryDB3);
                        double an = curPoint.arg;
                        (*pointMemory)[i].coords = c.center + c.radius*GM::Vector(cos(an), sin(an));
                    }
                    else if (curPoint.defShape1 == LINE || curPoint.defShape1 == SEGMENT)
                    {
                        double dx, dy;
                        GM::Point p1, p2;
                        if (curPoint.defShape1 == LINE)
                        {
                            p1 = (*pointMemory)[(*lineMemory)[curPoint.defIndex1].pointIndexA].coords;
                            p2 = (*pointMemory)[(*lineMemory)[curPoint.defIndex1].pointIndexB].coords;
                        }
                        else
                        {
                            p1 = (*pointMemory)[(*segmentMemory)[curPoint.defIndex1].pointIndexA].coords;
                            p2 = (*pointMemory)[(*segmentMemory)[curPoint.defIndex1].pointIndexB].coords;
                        }
                        dx = p2.x - p1.x;
                        dy = p2.y - p1.y;
                        (*pointMemory)[i].coords = p1 + curPoint.arg*GM::Vector(dx, dy);
                    }
                    break;
                }
                case LOCKED_CROSSPOINT:
                {
                    if ((curPoint.defShape1 == SEGMENT || curPoint.defShape1 == LINE) && (curPoint.defShape2 == SEGMENT || curPoint.defShape2 == LINE))
                    {

                        GM::Line l1, l2;
                        if (curPoint.defShape1 == SEGMENT)
                        {
                            if (points[(*segmentMemory)[curPoint.defIndex1].pointIndexA] == false || points[(*segmentMemory)[curPoint.defIndex1].pointIndexB] == false) continue;
                            l1 = GM::Line(DTSSegment(curPoint.defIndex1, pointMemory, segmentMemory));
                        }
                        else
                        {
                            if (points[(*lineMemory)[curPoint.defIndex1].pointIndexA] == false || points[(*lineMemory)[curPoint.defIndex1].pointIndexB] == false) continue;
                            l1 = DTSLine(curPoint.defIndex1, pointMemory, lineMemory);
                        }
                        if (curPoint.defShape2 == SEGMENT)
                        {
                            if (points[(*segmentMemory)[curPoint.defIndex2].pointIndexA] == false || points[(*segmentMemory)[curPoint.defIndex2].pointIndexB] == false) continue;
                            l2 = GM::Line(DTSSegment(curPoint.defIndex2, pointMemory, segmentMemory));
                        }
                        else
                        {
                            if (points[(*lineMemory)[curPoint.defIndex2].pointIndexA] == false || points[(*lineMemory)[curPoint.defIndex2].pointIndexB] == false) continue;
                            l2 = DTSLine(curPoint.defIndex2, pointMemory, lineMemory);
                        }

                        if (l1.getM() != l2.getM())
                        {
                            (*pointMemory)[i].coords = crossPoints(l1, l2)[0];
                        }
                    }
                    else if (curPoint.defShape1 == CIRCLE_DB2 || curPoint.defShape1 == CIRCLE_DB3 || curPoint.defShape2 == CIRCLE_DB2 || curPoint.defShape2 == CIRCLE_DB3)
                    {
                        if (curPoint.defShape1 == LINE || curPoint.defShape2 == LINE || curPoint.defShape1 == SEGMENT || curPoint.defShape2 == SEGMENT)
                        {
                            GM::Circle c;
                            GM::Line l;
                            GM::Point defPoint1, defPoint2;
                            if (curPoint.defShape1 == LINE)
                            {
                                if (points[(*lineMemory)[curPoint.defIndex1].pointIndexA] == false || points[(*lineMemory)[curPoint.defIndex1].pointIndexB] == false) continue;
                                l = DTSLine(curPoint.defIndex1, pointMemory, lineMemory);
                                defPoint1 = DTSPoint( (*lineMemory)[curPoint.defIndex1].pointIndexA, pointMemory );
                                defPoint2 = DTSPoint( (*lineMemory)[curPoint.defIndex1].pointIndexB, pointMemory );
                            }
                            else if (curPoint.defShape1 == SEGMENT)
                            {
                                if (points[(*segmentMemory)[curPoint.defIndex1].pointIndexA] == false || points[(*segmentMemory)[curPoint.defIndex1].pointIndexB] == false) continue;
                                l = GM::Line(DTSSegment(curPoint.defIndex1, pointMemory, segmentMemory));
                                defPoint1 = DTSPoint( (*segmentMemory)[curPoint.defIndex1].pointIndexA, pointMemory );
                                defPoint2 = DTSPoint( (*segmentMemory)[curPoint.defIndex1].pointIndexB, pointMemory );
                            }
                            else if (curPoint.defShape2 == LINE)
                            {
                                if (points[(*lineMemory)[curPoint.defIndex2].pointIndexA] == false || points[(*lineMemory)[curPoint.defIndex2].pointIndexB] == false) continue;
                                l = DTSLine(curPoint.defIndex2, pointMemory, lineMemory);
                                defPoint1 = DTSPoint( (*lineMemory)[curPoint.defIndex2].pointIndexA, pointMemory );
                                defPoint2 = DTSPoint( (*lineMemory)[curPoint.defIndex2].pointIndexB, pointMemory );
                            }
                            else if (curPoint.defShape2 == SEGMENT)
                            {
                                if (points[(*segmentMemory)[curPoint.defIndex2].pointIndexA] == false || points[(*segmentMemory)[curPoint.defIndex2].pointIndexB] == false) continue;
                                l = GM::Line(DTSSegment(curPoint.defIndex2, pointMemory, segmentMemory));
                                defPoint1 = DTSPoint( (*segmentMemory)[curPoint.defIndex2].pointIndexA, pointMemory );
                                defPoint2 = DTSPoint( (*segmentMemory)[curPoint.defIndex2].pointIndexB, pointMemory );
                            }

                            if (curPoint.defShape1 == CIRCLE_DB2)
                            {
                                if (points[(*circleMemoryDB2)[curPoint.defIndex1].pointIndexA] == false || points[(*circleMemoryDB2)[curPoint.defIndex1].pointIndexB] == false) continue;
                                c = DTSCircleDB2(curPoint.defIndex1, pointMemory, circleMemoryDB2);
                            }
                            else if (curPoint.defShape1 == CIRCLE_DB3)
                            {
                                if (points[(*circleMemoryDB3)[curPoint.defIndex1].pointIndexA] == false || points[(*circleMemoryDB3)[curPoint.defIndex1].pointIndexB] == false || points[(*circleMemoryDB3)[curPoint.defIndex1].pointIndexC] == false) continue;
                                c = DTSCircleDB3(curPoint.defIndex1, pointMemory, circleMemoryDB3);
                            }
                            else if (curPoint.defShape2 == CIRCLE_DB2)
                            {
                                if (points[(*circleMemoryDB2)[curPoint.defIndex2].pointIndexA] == false || points[(*circleMemoryDB2)[curPoint.defIndex2].pointIndexB] == false) continue;
                                c = DTSCircleDB2(curPoint.defIndex2, pointMemory, circleMemoryDB2);
                            }
                            else if (curPoint.defShape2 == CIRCLE_DB3)
                            {
                                if (points[(*circleMemoryDB3)[curPoint.defIndex2].pointIndexA] == false || points[(*circleMemoryDB3)[curPoint.defIndex2].pointIndexB] == false || points[(*circleMemoryDB3)[curPoint.defIndex2].pointIndexC] == false) continue;
                                c = DTSCircleDB3(curPoint.defIndex2, pointMemory, circleMemoryDB3);
                            }

                            std::vector<GM::Point> CP = crossPoints(c, l);

                            (*pointMemory)[i].visible = true;

                            if (CP.size() == 0)
                            {
                                (*pointMemory)[i].visible = false;
                                break;
                            }
                            else if (CP.size() == 1)
                            {
                                (*pointMemory)[i].coords = CP[0];
                                break;

                            }

                            if (l.straight())
                            {
                                // at 0 the y is smaller; ordered by y coord
                                if (CP[0].y > CP[1].y) std::swap(CP[0], CP[1]);

                                if (curPoint.arg == 0)
                                {
                                    if (defPoint1.y < defPoint2.y) (*pointMemory)[i].coords = CP[0];
                                    else (*pointMemory)[i].coords = CP[1];
                                }
                                else
                                {
                                    if (defPoint2.y < defPoint1.y) (*pointMemory)[i].coords = CP[0];
                                    else (*pointMemory)[i].coords = CP[1];
                                }
                            }
                            else
                            {
                                // ordered by x coord
                                if (CP[0].x > CP[1].x) std::swap(CP[0], CP[1]);

                                if (curPoint.arg == 0)
                                {
                                    if (defPoint1.x < defPoint2.x) (*pointMemory)[i].coords = CP[0];
                                    else (*pointMemory)[i].coords = CP[1];
                                }
                                else
                                {
                                    if (defPoint2.x < defPoint1.x) (*pointMemory)[i].coords = CP[0];
                                    else (*pointMemory)[i].coords = CP[1];
                                }
                            }
                        }
                        else if ((curPoint.defShape1 == CIRCLE_DB2 || curPoint.defShape1 == CIRCLE_DB3) && (curPoint.defShape2 == CIRCLE_DB2 || curPoint.defShape2 == CIRCLE_DB3))
                        {
                            GM::Circle c1, c2;
                            if (curPoint.defShape1 == CIRCLE_DB2)
                            {
                                if (points[(*circleMemoryDB2)[curPoint.defIndex1].pointIndexA] == false || points[(*circleMemoryDB2)[curPoint.defIndex1].pointIndexB] == false) continue;
                                c1 = DTSCircleDB2(curPoint.defIndex1, pointMemory, circleMemoryDB2);
                            }
                            else if (curPoint.defShape1 == CIRCLE_DB3)
                            {
                                if (points[(*circleMemoryDB3)[curPoint.defIndex1].pointIndexA] == false || points[(*circleMemoryDB3)[curPoint.defIndex1].pointIndexB] == false || points[(*circleMemoryDB3)[curPoint.defIndex1].pointIndexC] == false) continue;
                                c1 = DTSCircleDB3(curPoint.defIndex1, pointMemory, circleMemoryDB3);
                            }
                            if (curPoint.defShape2 == CIRCLE_DB2)
                            {
                                if (points[(*circleMemoryDB2)[curPoint.defIndex2].pointIndexA] == false || points[(*circleMemoryDB2)[curPoint.defIndex2].pointIndexB] == false) continue;
                                c2 = DTSCircleDB2(curPoint.defIndex2, pointMemory, circleMemoryDB2);
                            }
                            else if (curPoint.defShape2 == CIRCLE_DB3)
                            {
                                if (points[(*circleMemoryDB3)[curPoint.defIndex2].pointIndexA] == false || points[(*circleMemoryDB3)[curPoint.defIndex2].pointIndexB] == false || points[(*circleMemoryDB3)[curPoint.defIndex2].pointIndexC] == false) continue;
                                c2 = DTSCircleDB3(curPoint.defIndex2, pointMemory, circleMemoryDB3);
                            }

                            std::vector<GM::Point> CP = crossPoints(c1, c2);

                            (*pointMemory)[i].visible = true;
                            if (CP.size() == 0)
                            {
                                (*pointMemory)[i].visible = false;
                                break;
                            }
                            if (CP.size() == 1)
                            {
                                (*pointMemory)[i].coords = CP[0];
                                break;
                            }
                            GM::Vector v = c2.center.toVector() - c1.center.toVector(), v1 = CP[0].toVector() - c1.center.toVector(), v2 = CP[1].toVector() - c1.center.toVector();
                            double an = atan2(v.y, v.x), an1 = atan2(v1.y, v1.x), an2 = atan2(v2.y, v2.x);

                            if (an < 0) an+=2*PI;
                            if (an1 < 0) an1+=2*PI;
                            if (an2 < 0) an2+=2*PI;

                            if ((an1 > an2 && an2 > an) || (an2 > an && an > an1) || (an > an1 && an1 > an2)) std::swap(CP[0], CP[1]);

                            if (curPoint.arg == 0) (*pointMemory)[i].coords = CP[0];
                            else (*pointMemory)[i].coords = CP[1];
                        }

                    }
                    break;
                }
                case LOCKED_ALTITUDE_FOOT:
                {
                    GM::Point p;
                    GM::Line l;
                    if (curPoint.defShape1 == POINT && curPoint.defShape2 == SEGMENT)
                    {
                        if (points[curPoint.defIndex1] == false || points[(*segmentMemory)[curPoint.defIndex2].pointIndexA] == false || points[(*segmentMemory)[curPoint.defIndex2].pointIndexB] == false) continue;
                        p = DTSPoint(curPoint.defIndex1, pointMemory);
                        l = GM::Line(DTSSegment(curPoint.defIndex2, pointMemory, segmentMemory));
                    }
                    else if (curPoint.defShape1 == SEGMENT && curPoint.defShape2 == POINT)
                    {
                        if (points[curPoint.defIndex2] == false || points[(*segmentMemory)[curPoint.defIndex1].pointIndexA] == false || points[(*segmentMemory)[curPoint.defIndex1].pointIndexB] == false) continue;
                        p = DTSPoint(curPoint.defIndex2, pointMemory);
                        l = GM::Line(DTSSegment(curPoint.defIndex1, pointMemory, segmentMemory));
                    }
                    else if (curPoint.defShape1 == POINT && curPoint.defShape2 == LINE)
                    {
                        if (points[curPoint.defIndex1] == false || points[(*lineMemory)[curPoint.defIndex2].pointIndexA] == false || points[(*lineMemory)[curPoint.defIndex2].pointIndexB] == false) continue;
                        p = DTSPoint(curPoint.defIndex1, pointMemory);
                        l = DTSLine(curPoint.defIndex2, pointMemory, lineMemory);
                    }
                    else if (curPoint.defShape1 == LINE && curPoint.defShape2 == POINT)
                    {
                        if (points[curPoint.defIndex2] == false || points[(*lineMemory)[curPoint.defIndex1].pointIndexA] == false || points[(*lineMemory)[curPoint.defIndex1].pointIndexB] == false) continue;
                        p = DTSPoint(curPoint.defIndex2, pointMemory);
                        l = DTSLine(curPoint.defIndex1, pointMemory, lineMemory);
                    }
                    else
                    {
                        continue;
                    }
                    GM::Segment s = altitude(l, p);
                    (*pointMemory)[i].coords = s.b;
                    break;
                }
                case LOCKED_MIDPOINT:
                {
                    if (curPoint.defShape1 == POINT && curPoint.defShape2 == POINT)
                    {
                        if (points[curPoint.defIndex1] == false || points[curPoint.defIndex2] == false) continue;
                        (*pointMemory)[i].coords = midpoint(DTSPoint(curPoint.defIndex1, pointMemory), DTSPoint(curPoint.defIndex2, pointMemory));
                    }
                    break;
                }
                case LOCKED_PERPENDICULAR_BISECTOR:
                {
                    if (curPoint.defShape1 == POINT && curPoint.defShape2 == POINT)
                    {
                        if (points[curPoint.defIndex1] == false || points[curPoint.defIndex2] == false) continue;
                        GM::Point p1 = DTSPoint(curPoint.defIndex1, pointMemory), p2 = DTSPoint(curPoint.defIndex2, pointMemory);
                        GM::Point mid = midpoint(p1, p2);
                        (*pointMemory)[i].coords = GM::Point(mid.x + p1.y - mid.y, mid.y + mid.x - p1.x);
                    }
                    break;
                }
                case LOCKED_ANGLE_BISECTOR:
                {
                    if (curPoint.defShape1 == POINT && curPoint.defShape2 == POINT && curPoint.defShape3 == POINT)
                    {
                        if (points[curPoint.defIndex1] == false || points[curPoint.defIndex2] == false || points[curPoint.defIndex3] == false) continue;
                        GM::Point center = DTSPoint(curPoint.defIndex2, pointMemory);
                        GM::Line l = angleBisector(DTSPoint(curPoint.defIndex1, pointMemory), center, DTSPoint(curPoint.defIndex3, pointMemory));
                        if (l.straight())
                        {
                            (*pointMemory)[i].coords = center + GM::Vector(0, 100);
                        }
                        else
                        {
                            double an = atan(l.getM());
                            (*pointMemory)[i].coords = center + GM::Vector(100*cos(an), 100*sin(an));
                            if (findAngle((*pointMemory)[i].coords, center, DTSPoint(curPoint.defIndex1, pointMemory)) > PI/2)
                            {
                                (*pointMemory)[i].coords = center - GM::Vector(100*cos(an), 100*sin(an));
                            }

                        }
                    }
                    break;
                }
                case LOCKED_OUTSIDE_ANGLE_BISECTOR:
                {
                    if (curPoint.defShape1 == POINT && curPoint.defShape2 == POINT && curPoint.defShape3 == POINT)
                    {
                        if (points[curPoint.defIndex1] == false || points[curPoint.defIndex2] == false || points[curPoint.defIndex3] == false) continue;
                        GM::Point center = DTSPoint(curPoint.defIndex2, pointMemory);
                        GM::Line l = angleBisector(DTSPoint(curPoint.defIndex1, pointMemory), center, DTSPoint(curPoint.defIndex3, pointMemory));
                        if (l.straight())
                        {
                            (*pointMemory)[i].coords = center + GM::Vector(100, 0);
                        }
                        else
                        {
                            double an = atan(l.getM());
                            (*pointMemory)[i].coords = center + GM::Vector(100*sin(an), -100*cos(an));
                            if (findAngle((*pointMemory)[i].coords, center, DTSPoint(curPoint.defIndex1, pointMemory)) > PI/2)
                            {
                                (*pointMemory)[i].coords = center - GM::Vector(100*sin(an), -100*cos(an));
                            }
                        }
                    }
                    break;
                }
                default:
                    break;
            }

            points[i] = true;
            donePoints++;

        }
    }
}
