#ifndef RENDERING_H
#define RENDERING_H

#include<iostream>
#include<SFML/Graphics.hpp>
#include<vector>
#include"Geometry.h"
#include"GMColors.h"

using namespace sf;

void renderGMShape(RenderWindow * window, GM::Point point, GM::Vector offset);
void renderGMShape(RenderWindow * window, GM::Segment segment, GM::Vector offset, double thickness);
void renderGMShape(RenderWindow * window, GM::Line line, GM::Vector offset, double thickness);
void renderGMShape(RenderWindow * window, GM::Circle circle, GM::Vector offset, double thickness);
void renderGMShape(RenderWindow * window, GM::Triangle triangle, GM::Vector offset, double thickness);

void renderGMShape(RenderWindow * window, GM::Point point, PointColors colors, GM::Vector offset);
void renderGMShape(RenderWindow * window, GM::Segment segment, SegmentColors colors, GM::Vector offset, double thickness);
void renderGMShape(RenderWindow * window, GM::Line line, LineColors colors, GM::Vector offset, double thickness);
void renderGMShape(RenderWindow * window, GM::Circle circle, CircleColors colors, GM::Vector offset, double thickness);
void renderGMShape(RenderWindow * window, GM::Triangle triangle, TriangleColors colors, GM::Vector offset, double thickness);

void renderGMShape(RenderWindow * window, std::vector<GM::Point> * points, GM::Vector offset);
void renderGMShape(RenderWindow * window, std::vector<GM::Segment> * segments, GM::Vector offset, double thickness);
void renderGMShape(RenderWindow * window, std::vector<GM::Line> * lines, GM::Vector offset, double thickness);
void renderGMShape(RenderWindow * window, std::vector<GM::Circle> * circles, GM::Vector offset, double thickness);
void renderGMShape(RenderWindow * window, std::vector<GM::Triangle> * triangles, GM::Vector offset, double thickness);

#endif // RENDERING_H
