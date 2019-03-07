#ifndef GEOMETRY_H
#define GEOMETRY_H

#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>
#include<iomanip>

const double PI = atan(1)*4;

namespace GM
{
    class Vector
    {
    public:
        double x;
        double y;

        Vector();
        Vector(double x, double y);

        void rotateByAngle(double an);
    private:
    };

    class Point
    {
    public:
        double x;
        double y;

        Point();
        Point(double x, double y);

        void operator+= (Vector v);
        void operator-= (Vector v);
        void operator= (Vector v);

        Vector toVector();
    private:
    };

    class Segment
    {
    public:
        Point a;
        Point b;

        Segment();
        Segment(Point a, Point b);
        Segment(double x1, double y1, double x2, double y2);

        double lenght();
        bool isPointLying(Point p);
    private:
    };

    class Line
    {
    public:
        Line();
        Line(Point a, Point b);
        Line(Segment s);
        Line(double m, double b);

        bool straight();
        double getB();
        double getM();
        bool isPointLying(Point p);

        void operator= (Segment s);

    private:
        bool z_straight;
        double z_m;
        double z_b;
    };

    class Circle
    {
    public:
        Point center;
        double radius;

        Circle();
        Circle(Point p, double radius);
        Circle(Point a, Point b, Point c);
    private:
    };

    // Here's the complex shit boi

    class Triangle
    {
    public:
        Point a;
        Point b;
        Point c;

        Triangle();
        Triangle(Point a, Point b, Point c);
        Triangle(double x1, double y1, double x2, double y2, double x3, double y3);

        bool valid();
        double area();
        double perimeter();
        Point circumcenter();
        Circle circumcircle();
        Point orthocenter();
        Point centroid();
        Point incenter();
        Circle incircle();
        Circle ninePointsCircle();
    private:
    };

}

GM::Line perpendicularBisector(GM::Segment s);
GM::Line angleBisector(GM::Point a, GM::Point b, GM::Point c);
GM::Line angleBisector(GM::Line l1, GM::Line l2, int arg = 0);
GM::Line angleBisector(GM::Segment s, GM::Line l, int arg = 0);
GM::Line angleBisector(GM::Line l, GM::Segment s, int arg = 0);
GM::Line angleBisector(GM::Segment s1, GM::Segment s2, int arg = 0);

GM::Segment altitude(GM::Line l, GM::Point p);
GM::Segment altitude(GM::Segment s, GM::Point p);
GM::Segment altitude(GM::Point p, GM::Line l);
GM::Segment altitude(GM::Point p, GM::Segment s);

GM::Point midpoint(GM::Point a, GM::Point b);
GM::Point midpoint(GM::Segment s);

double distanceBetweenPoints(GM::Point a, GM::Point b);

double findAngle(GM::Point a, GM::Point b, GM::Point c);

std::vector<GM::Point> crossPoints(GM::Line a, GM::Line b);
std::vector<GM::Point> crossPoints(GM::Line a, GM::Segment b);
std::vector<GM::Point> crossPoints(GM::Segment a, GM::Line b);
std::vector<GM::Point> crossPoints(GM::Segment a, GM::Segment b);
std::vector<GM::Point> crossPoints(GM::Circle c, GM::Line l);
std::vector<GM::Point> crossPoints(GM::Line l, GM::Circle c);
std::vector<GM::Point> crossPoints(GM::Circle c, GM::Segment s);
std::vector<GM::Point> crossPoints(GM::Segment s, GM::Circle c);
std::vector<GM::Point> crossPoints(GM::Circle c1, GM::Circle c2);

std::vector<GM::Segment> tangents(GM::Circle c, GM::Point p);

bool areTrianglesCongruent(GM::Triangle a, GM::Triangle b);
double areTrianglesSimilar(GM::Triangle a, GM::Triangle b);

bool operator== (GM::Point a, GM::Point b);
bool operator!= (GM::Point a, GM::Point b);
bool operator== (GM::Line a, GM::Line b);
GM::Point operator+ (GM::Point p, GM::Vector v);
GM::Point operator- (GM::Point p, GM::Vector v);
GM::Vector operator+ (GM::Vector a, GM::Vector b);
GM::Vector operator- (GM::Vector a, GM::Vector b);
GM::Vector operator* (GM::Vector v, double x);
GM::Vector operator* (double x, GM::Vector v);
GM::Vector operator/ (GM::Vector v, double x);

#endif // GEOMETRY_H
