#ifndef RENDERINGDYNAMICOBJECTS_H
#define RENDERINGDYNAMICOBJECTS_H

#include<iostream>
#include<vector>
#include<SFML/Graphics.hpp>
#include<set>

#include"DynamicalShapeData.h"
#include"Rendering.h"
#include"DynamicToStatic.h"
#include"MemoryManagement.h"

using namespace sf;

void renderDynamicObjects(RenderWindow * window, double mouseX, double mouseY, std::vector<dynamicIndex> * selection, std::vector<dynamicPoint> * pointMemory, std::vector<dynamicPointIndexes2> * segmentMemory, std::vector<dynamicPointIndexes2> * lineMemory, std::vector<dynamicPointIndexes2> * circleMemoryDB2, std::vector<dynamicPointIndexes3> * circleMemoryDB3, GM::Vector offset, double RECOGNISABLE_DISTANCE, double thickness);

#endif // RENDERINGDYNAMICOBJECTS_H
