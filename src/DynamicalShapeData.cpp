#include "DynamicalShapeData.h"

dynamicPoint::dynamicPoint()
{
    *this = dynamicPoint(0, 0, FREE, NO_SHAPE, NO_SHAPE, NO_SHAPE, -1, -1, -1);
}
dynamicPoint::dynamicPoint(double x, double y)
{
    *this = dynamicPoint(x, y, FREE, NO_SHAPE, NO_SHAPE, NO_SHAPE, -1, -1, -1);
}
dynamicPoint::dynamicPoint(double x, double y, pointType pType)
{
    *this = dynamicPoint(x, y, pType, NO_SHAPE, NO_SHAPE, NO_SHAPE, -1, -1, -1);
}
dynamicPoint::dynamicPoint(double x, double y, pointType pType, geometryShape defShape1, int defIndex1)
{
    *this = dynamicPoint(x, y, pType, defShape1, NO_SHAPE, NO_SHAPE, defIndex1, -1, -1);
}
dynamicPoint::dynamicPoint(double x, double y, pointType pType, geometryShape defShape1, geometryShape defShape2, int defIndex1, int defIndex2)
{
    *this = dynamicPoint(x, y, pType, defShape1, defShape2, NO_SHAPE, defIndex1, defIndex2, -1);
}
dynamicPoint::dynamicPoint(double x, double y, pointType pType, geometryShape defShape1, geometryShape defShape2, geometryShape defShape3, int defIndex1, int defIndex2, int defIndex3)
{
    this->coords = GM::Point(x, y);
    this->pType = pType;
    this->defShape1 = defShape1;
    this->defShape2 = defShape2;
    this->defShape3 = defShape3;
    this->defIndex1 = defIndex1;
    this->defIndex2 = defIndex2;
    this->defIndex3 = defIndex3;
}

pointPos::pointPos()
{
    *this = pointPos(-1, 0, 0);
}
pointPos::pointPos(int index, double x, double y)
{
    this->index = index;
    this->x = x;
    this->y = y;
    this->arg = 0;
}
pointPos::pointPos(int index, double x, double y, double arg)
{
    this->index = index;
    this->x = x;
    this->y = y;
    this->arg = arg;
}

dynamicIndex::dynamicIndex()
{
    *this = dynamicIndex(-1, NO_SHAPE);
}
dynamicIndex::dynamicIndex(int index, geometryShape geomShape)
{
    this->index = index;
    this->shape = geomShape;
}

indexDist::indexDist()
{
    this->index = 0;
    this->distance = 0;
}
indexDist::indexDist(int index, double distance)
{
    this->index = index;
    this->distance = distance;
}

dynamicPointIndexes2::dynamicPointIndexes2()
{
    this->pointIndexA = 0;
    this->pointIndexB = 0;
}
dynamicPointIndexes2::dynamicPointIndexes2(int a, int b)
{
    this->pointIndexA = a;
    this->pointIndexB = b;
}

dynamicPointIndexes3::dynamicPointIndexes3()
{
    this->pointIndexA = 0;
    this->pointIndexB = 0;
    this->pointIndexC = 0;
}
dynamicPointIndexes3::dynamicPointIndexes3(int a, int b, int c)
{
    this->pointIndexA = a;
    this->pointIndexB = b;
    this->pointIndexC = c;
}
