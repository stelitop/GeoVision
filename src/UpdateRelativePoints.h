#ifndef UPDATERELATIVEPOINTS_H
#define UPDATERELATIVEPOINTS_H

#include<iostream>
#include<vector>

#include"DynamicalShapeData.h"
#include"ChangePointType.h"
#include"DynamicToStatic.h"
#include"Geometry.h"

void updateRelativePoints(std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory, std::vector<dynamicPointIndexes2> * lineMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2, std::vector<dynamicPointIndexes3> * circleMemoryDB3);

#endif // UPDATERELATIVEPOINTS_H
