#ifndef MEMORYMANAGEMENT_H
#define MEMORYMANAGEMENT_H

#include<iostream>
#include<vector>
#include<set>

#include"Geometry.h"
#include"DynamicalShapeData.h"
#include"Enums.h"
#include"DistanceToMouse.h"
#include"DynamicToStatic.h"
#include"ChangePointType.h"

void cleanTemporaryData(std::vector<dynamicIndex> * indexSelection, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory, std::vector<dynamicPointIndexes2> * lineMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2, std::vector<dynamicPointIndexes3> * circleMemoryDB3);

void restoreOldPositions(std::vector<pointPos> * oldPointPositions, std::vector<dynamicPoint> * pointMemory);

int getNextFreePoint(std::vector<dynamicPoint> * pointMemory);
int getNextFreeSegment(std::vector<dynamicPointIndexes2> * segmentMemory);
int getNextFreeLine(std::vector<dynamicPointIndexes2> * lineMemory);
int getNextFreeCircleDB2(std::vector<dynamicPointIndexes2> * circleMemoryDB2);
int getNextFreeCircleDB3(std::vector<dynamicPointIndexes3> * circleMemoryDB3);

dynamicIndex selectObject(double mouseX, double mouseY, std::vector<dynamicIndex> * indexSelection, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory, std::vector<dynamicPointIndexes2> * lineMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2, std::vector<dynamicPointIndexes3> * circleMemoryDB3, double RECOGNISABLE_DISTANCE, const std::set<geometryShape> preferredShape);

int createPoint(double mouseX, double mouseY, std::vector<dynamicIndex> * indexSelection, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory, std::vector<dynamicPointIndexes2> * lineMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2, std::vector<dynamicPointIndexes3> * circleMemoryDB3, double RECOGNISABLE_DISTANCE);

int createRelativePoint(double mouseX, double mouseY, dynamicIndex object, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory, std::vector<dynamicPointIndexes2> * lineMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2, std::vector<dynamicPointIndexes3> * circleMemoryDB3);

int createSegment(double mouseX, double mouseY, std::vector<dynamicIndex> * indexSelection, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory, std::vector<dynamicPointIndexes2> * lineMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2, std::vector<dynamicPointIndexes3> * circleMemoryDB3, double RECOGNISABLE_DISTANCE);

int createLine(double mouseX, double mouseY, std::vector<dynamicIndex> * indexSelection, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory, std::vector<dynamicPointIndexes2> * lineMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2, std::vector<dynamicPointIndexes3> * circleMemoryDB3, double RECOGNISABLE_DISTANCE);

int createCircleDB2(double mouseX, double mouseY, std::vector<dynamicIndex> * indexSelection, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory, std::vector<dynamicPointIndexes2> * lineMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2, std::vector<dynamicPointIndexes3> * circleMemoryDB3, double RECOGNISABLE_DISTANCE);

int createCircleDB3(double mouseX, double mouseY, std::vector<dynamicIndex> * indexSelection, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory, std::vector<dynamicPointIndexes2> * lineMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2, std::vector<dynamicPointIndexes3> * circleMemoryDB3, double RECOGNISABLE_DISTANCE);

int createAltitude(double mouseX, double mouseY, std::vector<dynamicIndex> * indexSelection, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory, std::vector<dynamicPointIndexes2> * lineMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2, std::vector<dynamicPointIndexes3> * circleMemoryDB3, double RECOGNISABLE_DISTANCE);

int createMidpoint(double mouseX, double mouseY, std::vector<dynamicIndex> * indexSelection, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory, std::vector<dynamicPointIndexes2> * lineMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2, std::vector<dynamicPointIndexes3> * circleMemoryDB3, double RECOGNISABLE_DISTANCE);

int createPerpendicularBisector(double mouseX, double mouseY, std::vector<dynamicIndex> * indexSelection, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory, std::vector<dynamicPointIndexes2> * lineMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2, std::vector<dynamicPointIndexes3> * circleMemoryDB3, double RECOGNISABLE_DISTANCE);

int createAngleBisector(double mouseX, double mouseY, std::vector<dynamicIndex> * indexSelection, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory, std::vector<dynamicPointIndexes2> * lineMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2, std::vector<dynamicPointIndexes3> * circleMemoryDB3, double RECOGNISABLE_DISTANCE);

int createOutsideAngleBisector(double mouseX, double mouseY, std::vector<dynamicIndex> * indexSelection, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory, std::vector<dynamicPointIndexes2> * lineMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2, std::vector<dynamicPointIndexes3> * circleMemoryDB3, double RECOGNISABLE_DISTANCE);

#endif // MEMORYMANAGEMENT_H
