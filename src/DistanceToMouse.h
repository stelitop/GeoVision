#ifndef DISTANCETOMOUSE_H
#define DISTANCETOMOUSE_H

#include<iostream>
#include<vector>
#include<algorithm>

#include"Geometry.h"
#include"DynamicalShapeData.h"
#include"DynamicToStatic.h"

bool operator< (const indexDist a, const indexDist b);
std::vector<indexDist> findClosestPoint(double mouseX, double mouseY, std::vector<dynamicPoint> * pointMemory, double RECOGNISABLE_DISTANCE);
std::vector<indexDist> findClosestSegment(double mouseX, double mouseY, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory, double RECOGNISABLE_DISTANCE);
std::vector<indexDist> findClosestLine(double mouseX, double mouseY, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * lineMemory, double RECOGNISABLE_DISTANCE);
std::vector<indexDist> findClosestCircleDB2(double mouseX, double mouseY, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2, double RECOGNISABLE_DISTANCE);
std::vector<indexDist> findClosestCircleDB3(double mouseX, double mouseY, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes3> * circleMemoryDB3, double RECOGNISABLE_DISTANCE);

#endif // DISTANCETOMOUSE_H
