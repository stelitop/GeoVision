#ifndef OBJECTPREVIEW_H
#define OBJECTPREVIEW_H

#include<vector>
#include<SFML/Graphics.hpp>
#include<set>

#include"Enums.h"
#include"DynamicalShapeData.h"
#include"Rendering.h"
#include"DynamicToStatic.h"
#include"MemoryManagement.h"

using namespace sf;

void objectPreview(RenderWindow * window, std::vector<dynamicIndex> * indexSelection, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory, std::vector<dynamicPointIndexes2> * lineMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2, std::vector<dynamicPointIndexes3> * circleMemoryDB3, geometricToolSelected toolSelection, GM::Vector offset, double RECOGNISABLE_DISTANCE, double thickness);

#endif // OBJECTPREVIEW_H
