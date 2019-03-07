#include "Rendering.h"
#include<SFML/Graphics.hpp>
#include"Geometry.h"

using namespace sf;

void renderGMShape(RenderWindow * window, GM::Point point, GM::Vector offset)
{
    PointColors col;
    col.color = DEFAULT_COLOR;
    col.color.a = 255;
    col.color.r = col.color.r*9/10;
    col.color.g = col.color.g*9/10;
    col.color.b = col.color.b*9/10;
    renderGMShape(window, point, col, offset);
}
void renderGMShape(RenderWindow * window, GM::Segment segment, GM::Vector offset, double thickness)
{
    SegmentColors col;
    col.colorA = col.colorB = DEFAULT_COLOR;
    renderGMShape(window, segment, col, offset, thickness);
}
void renderGMShape(RenderWindow * window, GM::Line line, GM::Vector offset, double thickness)
{
    LineColors col;
    col.color = DEFAULT_COLOR;
    renderGMShape(window, line, col, offset, thickness);
}
void renderGMShape(RenderWindow * window, GM::Circle circle, GM::Vector offset, double thickness)
{
    CircleColors col;
    col.fillColor = Color(0, 0, 0, 0);
    col.outlineColor = DEFAULT_COLOR;
    renderGMShape(window, circle, col, offset, thickness);
}
void renderGMShape(RenderWindow * window, GM::Triangle triangle, GM::Vector offset, double thickness)
{
    TriangleColors col;
    col.colorA = col.colorB = col.colorC = DEFAULT_COLOR;
    renderGMShape(window, triangle, col, offset, thickness);
}

void renderGMShape(RenderWindow * window, GM::Point point, PointColors colors, GM::Vector offset)
{
    point -= offset;
    int windowY = window->getSize().y;
    point.y = windowY - point.y;
    CircleShape c;
    int r = 5;
    c.setPosition(point.x - 5, point.y - 5);
    c.setRadius(r);
    c.setFillColor(colors.color);
    c.setOutlineThickness(0);
    window->draw(c);
}
void renderGMShape(RenderWindow * window, GM::Segment segment, SegmentColors colors, GM::Vector offset, double thickness)
{
    thickness/=2;
    segment.a -= offset;
    segment.b -= offset;
    int windowY = window->getSize().y;
    segment.a.y = windowY - segment.a.y;
    segment.b.y = windowY - segment.b.y;

    VertexArray v(Lines, 2);
    v[0].position = Vector2f(segment.a.x, segment.a.y);
    v[1].position = Vector2f(segment.b.x, segment.b.y);
    v[0].color = colors.colorA;
    v[1].color = colors.colorB;
    window->draw(v);
}
void renderGMShape(RenderWindow * window, GM::Line line, LineColors colors, GM::Vector offset, double thickness)
{
    double m = line.getM(), b = line.getB();
    int windowX = window->getSize().x;
    int windowY = window->getSize().y;
    VertexArray v(Lines, 2);
    if (line.straight())
    {
        b -= offset.x;
        v[0].position = Vector2f(b, 0);
        v[1].position = Vector2f(b, windowY);
    }
    else
    {
        b -= offset.y - m*offset.x;
        v[0].position = Vector2f(0, windowY - b);
        v[1].position = Vector2f(windowX, windowY - (m*windowX + b));
    }
    v[0].color = colors.color;
    v[1].color = colors.color;
    window->draw(v);
}
void renderGMShape(RenderWindow * window, GM::Circle circle, CircleColors colors, GM::Vector offset, double thickness)
{
    circle.center -= offset;
    int windowY = window->getSize().y;
    circle.center.y = windowY - circle.center.y;
    CircleShape c;
    c.setRadius(circle.radius - thickness);
    c.setPosition(circle.center.x - circle.radius + thickness, circle.center.y - circle.radius + thickness);
    c.setFillColor(colors.fillColor);
    c.setOutlineColor(colors.outlineColor);
    c.setOutlineThickness(thickness + 1);
    c.setPointCount(std::max(int(circle.radius*2*PI/10), 10));
    window->draw(c);
}
void renderGMShape(RenderWindow * window, GM::Triangle triangle, TriangleColors colors, GM::Vector offset, double thickness)
{
    triangle.a -= offset;
    triangle.b -= offset;
    triangle.c -= offset;
    triangle.a.y = window->getSize().y - triangle.a.y;
    triangle.b.y = window->getSize().y - triangle.b.y;
    triangle.c.y = window->getSize().y - triangle.c.y;
    VertexArray v(LineStrip, 4);
    v[0] = Vector2f(triangle.a.x, triangle.a.y);
    v[1] = Vector2f(triangle.b.x, triangle.b.y);
    v[2] = Vector2f(triangle.c.x, triangle.c.y);
    v[3] = Vector2f(triangle.a.x, triangle.a.y);
    v[0].color = colors.colorA;
    v[1].color = colors.colorB;
    v[2].color = colors.colorC;
    v[3].color = colors.colorA;
    window->draw(v);
}

void renderGMShape(RenderWindow * window, std::vector<GM::Point> * points, GM::Vector offset)
{
    for (unsigned int i=0; i<points->size(); i++) renderGMShape(window, points->at(i), offset);
}
void renderGMShape(RenderWindow * window, std::vector<GM::Segment> * segments, GM::Vector offset, double thickness)
{
    for (unsigned int i=0; i<segments->size(); i++) renderGMShape(window, segments->at(i), offset, thickness);
}
void renderGMShape(RenderWindow * window, std::vector<GM::Line> * lines, GM::Vector offset, double thickness)
{
    for (unsigned int i=0; i<lines->size(); i++) renderGMShape(window, lines->at(i), offset, thickness);
}
void renderGMShape(RenderWindow * window, std::vector<GM::Circle> * circles, GM::Vector offset, double thickness)
{
    for (unsigned int i=0; i<circles->size(); i++) renderGMShape(window, circles->at(i), offset, thickness);
}
void renderGMShape(RenderWindow * window, std::vector<GM::Triangle> * triangles, GM::Vector offset, double thickness)
{
    for (unsigned int i=0; i<triangles->size(); i++) renderGMShape(window, triangles->at(i), offset, thickness);
}
