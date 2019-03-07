#ifndef DYNAMICALSHAPEDATA_H
#define DYNAMICALSHAPEDATA_H

#include"Geometry.h"
#include"Enums.h"

struct dynamicPoint
{
    bool interactable = true;
    bool visible = true;
    GM::Point coords;
    pointType pType;
    geometryShape defShape1, defShape2, defShape3 = NO_SHAPE;
    int defIndex1, defIndex2, defIndex3 = -1;
    double arg = 0;

    dynamicPoint();
    dynamicPoint(double x, double y);
    dynamicPoint(double x, double y, pointType pType);
    dynamicPoint(double x, double y, pointType pType, geometryShape defShape1, int defIndex1);
    dynamicPoint(double x, double y, pointType pType, geometryShape defShape1, geometryShape defShape2, int defIndex1, int defIndex2);
    dynamicPoint(double x, double y, pointType pType, geometryShape defShape1, geometryShape defShape2, geometryShape defShape3, int defIndex1, int defIndex2, int defIndex3);
};

struct pointPos
{
    int index;
    double arg=0;
    double x;
    double y;

    pointPos();
    pointPos(int index, double x, double y);
    pointPos(int index, double x, double y, double arg);
};

struct dynamicIndex
{
    int index;
    geometryShape shape;

    dynamicIndex();
    dynamicIndex(int index, geometryShape geomShape);
};

struct indexDist
{
    int index;
    double distance;

    indexDist();
    indexDist(int index, double distance);
};

struct dynamicPointIndexes2
{
    bool interactable=true;
    bool visible = true;
    int pointIndexA;
    int pointIndexB;
    dynamicPointIndexes2();
    dynamicPointIndexes2(int a, int b);
};
struct dynamicPointIndexes3
{
    bool interactable=true;
    bool visible = true;
    int pointIndexA;
    int pointIndexB;
    int pointIndexC;
    dynamicPointIndexes3();
    dynamicPointIndexes3(int a, int b, int c);
};

#endif // DYNAMICALSHAPEDATA_H

