#ifndef DYNAMICTOSTATIC_H
#define DYNAMICTOSTATIC_H

#include<iostream>
#include"Geometry.h"
#include"DynamicalShapeData.h"

GM::Point DTSPoint(int index, std::vector<dynamicPoint> * pointMemory);
GM::Segment DTSSegment(int index, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory);
GM::Line DTSLine(int index, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * lineMemory);
GM::Circle DTSCircleDB2(int index, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2);
GM::Circle DTSCircleDB3(int index, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes3> * circleMemoryDB3);

#endif // DYNAMICTOSTATIC_H
