#include"GMColors.h"

PointColors::PointColors()
{
    this->color = DEFAULT_COLOR;
}
PointColors::PointColors(sf::Color color)
{
    this->color = color;
}

SegmentColors::SegmentColors()
{
    this->colorA = DEFAULT_COLOR;
    this->colorB = DEFAULT_COLOR;
}
SegmentColors::SegmentColors(sf::Color colorA, sf::Color colorB)
{
    this->colorA = colorA;
    this->colorB = colorB;
}

LineColors::LineColors()
{
    this->color = DEFAULT_COLOR;
}
LineColors::LineColors(sf::Color color)
{
    this->color = color;
}

CircleColors::CircleColors()
{
    this->fillColor = sf::Color(0, 0, 0, 0);
    this->outlineColor = DEFAULT_COLOR;
}
CircleColors::CircleColors(sf::Color fillColor, sf::Color outlineColor)
{
    this->fillColor = fillColor;
    this->outlineColor = outlineColor;
}

TriangleColors::TriangleColors()
{
    this->colorA = DEFAULT_COLOR;
    this->colorB = DEFAULT_COLOR;
    this->colorC = DEFAULT_COLOR;
}
TriangleColors::TriangleColors(sf::Color colorA, sf::Color colorB, sf::Color colorC)
{
    this->colorA = colorA;
    this->colorB = colorB;
    this->colorC = colorC;
}
