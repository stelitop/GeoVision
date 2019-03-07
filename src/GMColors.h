#ifndef GMCOLORS_H
#define GMCOLORS_H

#include<iostream>
#include<SFML/Graphics.hpp>
#include"Geometry.h"

const sf::Color DEFAULT_COLOR(255, 170, 70, 155);
const sf::Color DEFAULT_COLOR_SELECTION(255, 255, 255, 255);
const sf::Color DEFAULT_COLOR_PREVIEW(0, 155, 155, 255);
const sf::Color DEFAULT_COLOR_HOVER(255, 170, 170, 255);

struct PointColors
{
public:
    sf::Color color;
    PointColors();
    PointColors(sf::Color color);
};

struct SegmentColors
{
public:
    sf::Color colorA, colorB;
    SegmentColors();
    SegmentColors(sf::Color colorA, sf::Color colorB);
};

struct LineColors
{
public:
    sf::Color color;
    LineColors();
    LineColors(sf::Color color);
};

struct CircleColors
{
public:
    sf::Color fillColor;
    sf::Color outlineColor;
    CircleColors();
    CircleColors(sf::Color fillColor, sf::Color outlineColor);
};

struct TriangleColors
{
public:
    sf::Color colorA, colorB, colorC;
    TriangleColors();
    TriangleColors(sf::Color colorA, sf::Color colorB, sf::Color colorC);
};

#endif // GMCOLORS_H
