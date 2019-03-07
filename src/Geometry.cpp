#include "Geometry.h"
#include<vector>

// Point functions
GM::Point::Point()
{
    this->x = 0;
    this->y = 0;
}
GM::Point::Point(double x, double y)
{
    this->x = x;
    this->y = y;
}

bool operator== (GM::Point a, GM::Point b)
{
    if (a.x == b.x && a.y == b.y) return true;
    else return false;
}
bool operator!= (GM::Point a, GM::Point b)
{
    if (a.x == b.x && a.y == b.y) return false;
    else return true;
}
void GM::Point::operator= (Vector v)
{
    this->x = v.x;
    this->y = v.y;
}

void GM::Point::operator+= (GM::Vector v)
{
    this->x += v.x;
    this->y += v.y;
}
void GM::Point::operator-= (GM::Vector v)
{
    this->x -= v.x;
    this->y -= v.y;
}

GM::Vector GM::Point::toVector()
{
    return GM::Vector(this->x, this->y);
}

// Segment functions
GM::Segment::Segment()
{
    this->a = GM::Point();
    this->b = GM::Point();
}
GM::Segment::Segment(Point a, Point b)
{
    this->a = a;
    this->b = b;
}
GM::Segment::Segment(double x1, double y1, double x2, double y2)
{
    this->a = GM::Point(x1, y1);
    this->b = GM::Point(x2, y2);
}
double GM::Segment::lenght()
{
    double dx = this->a.x - this->b.x;
    double dy = this->a.y - this->b.y;
    return sqrt(dx*dx + dy*dy);
}
bool GM::Segment::isPointLying(Point p)
{
    GM::Line l = *this;
    if (l.straight())
    {
        if (l.getB() != p.x) return false;
    }
    else if(p.x*l.getM() + l.getB() != p.y) return false;

    double bigX = std::max(this->a.x , this->b.x);
    double smallX = std::min(this->a.x , this->b.x);
    if (bigX >= p.x && p.x >= smallX) return true;
    return false;
}

// Line functions
GM::Line::Line()
{
    this->z_m = 0;
    this->z_b = 0;
    this->z_straight = false;
}
GM::Line::Line(Point a, Point b)
{
    if (a != b)
    {
        if (a.x == b.x)
        {
            this->z_b = a.x;
            this->z_straight = true;
        }
        else
        {
            this->z_m = (a.y - b.y)/(a.x - b.x);
            this->z_b = a.y - a.x*this->z_m;
            this->z_straight = false;
        }
    }
    else
    {
        this->z_straight = false;
        this->z_b = a.x;
        this->z_m = 0;
    }
}
GM::Line::Line(Segment s)
{
    *this = GM::Line(s.a, s.b);
}
GM::Line::Line(double m, double b)
{
    this->z_m = m;
    this->z_b = b;
    this->z_straight = false;
}
bool GM::Line::straight()
{
    return this->z_straight;
}
double GM::Line::getB()
{
    return this->z_b;
}
double GM::Line::getM()
{
    return this->z_m;
}
bool GM::Line::isPointLying(Point p)
{
    if (this->straight())
    {
        if (std::abs(this->getB() - p.x) < 0.0001) return true;
        return false;
    }
    if(std::abs(p.x*this->getM() + this->getB() - p.y) < 0.0001) return true;
    return false;
}
void GM::Line::operator=(Segment s)
{
    *this = GM::Line(s);
}
bool operator== (GM::Line a, GM::Line b)
{
    if (a.straight() == b.straight() && a.straight() == true && a.getB() == b.getB()) return true;
    else if (a.straight() == b.straight() && a.straight() == false && a.getB() == b.getB() && a.getM() == b.getM()) return true;
    return false;
}

// Circle functions
GM::Circle::Circle()
{
    this->center = GM::Point(0, 0);
    this->radius = 0;
}
GM::Circle::Circle(Point p, double radius)
{
    this->center = p;
    this->radius = radius;
}
GM::Circle::Circle(Point a, Point b, Point c)
{
    GM::Line l1(a, b), l2(b, c);
    if (a == b || b == c || a == c) *this = Circle();
    else if (l1 == l2) *this = Circle();
    else
    {
        l1 = perpendicularBisector(GM::Segment(a, b));
        l2 = perpendicularBisector(GM::Segment(a, c));
        this->center = crossPoints(l1, l2)[0];
        this->radius = GM::Segment(this->center, a).lenght();
    }
}

// Vector functions
GM::Vector::Vector()
{
    this->x = 0;
    this->y = 0;
}
GM::Vector::Vector(double x, double y)
{
    this->x = x;
    this->y = y;
}

void GM::Vector::rotateByAngle(double an)
{
    double curan = atan2(this->y, this->x);
    double r = sqrt(this->x*this->x + this->y*this->y);
    curan += an;
    this->x = r*cos(curan);
    this->y = r*sin(curan);
}

GM::Point operator+ (GM::Point p, GM::Vector v)
{
    return GM::Point(p.x + v.x, p.y + v.y);
}
GM::Point operator- (GM::Point p, GM::Vector v)
{
    return GM::Point(p.x - v.x, p.y - v.y);
}
GM::Vector operator+ (GM::Vector a, GM::Vector b)
{
    return GM::Vector(a.x + b.x, a.y + b.y);
}
GM::Vector operator- (GM::Vector a, GM::Vector b)
{
    return GM::Vector(a.x - b.x, a.y - b.y);
}
GM::Vector operator* (GM::Vector v, double x)
{
    return GM::Vector(v.x*x, v.y*x);
}
GM::Vector operator* (double x, GM::Vector v)
{
    return GM::Vector(v.x*x, v.y*x);
}
GM::Vector operator/ (GM::Vector v, double x)
{
    return GM::Vector(v.x/x, v.y/x);
}

// Triangle functions
GM::Triangle::Triangle()
{
    this->a = GM::Point();
    this->b = GM::Point();
    this->c = GM::Point();
}
GM::Triangle::Triangle(Point a, Point b, Point c)
{
    this->a = a;
    this->b = b;
    this->c = c;
}
GM::Triangle::Triangle(double x1, double y1, double x2, double y2, double x3, double y3)
{
    this->a = GM::Point(x1, y1);
    this->b = GM::Point(x2, y2);
    this->c = GM::Point(x3, y3);
}

bool GM::Triangle::valid()
{
    if (this->a == this->b || this->b == this->c || this->a == this->c) return false;
    GM::Line l1(a, b), l2(b, c);
    if (l1 == l2) return false;
    return true;
}
double GM::Triangle::area()
{
    if (!this->valid()) return 0;
    double a = distanceBetweenPoints(this->b, this->c);
    double b = distanceBetweenPoints(this->a, this->c);
    double c = distanceBetweenPoints(this->a, this->b);
    double p = (a + b + c)/2;
    return sqrt(p*(p-a)*(p-b)*(p-c));
}
double GM::Triangle::perimeter()
{
    if (!this->valid()) return 0;
    double a = distanceBetweenPoints(this->b, this->c);
    double b = distanceBetweenPoints(this->a, this->c);
    double c = distanceBetweenPoints(this->a, this->b);
    return a + b + c;
}
GM::Point GM::Triangle::circumcenter()
{
    if (!this->valid()) return GM::Point();
    GM::Segment s1(this->a, this->b), s2(this->b, this->c);
    GM::Line l1 = perpendicularBisector(s1), l2 = perpendicularBisector(s2);
    return crossPoints(l1 , l2)[0];
}
GM::Circle GM::Triangle::circumcircle()
{
    if (!this->valid()) return GM::Circle();
    GM::Point c = this->circumcenter();
    double r = distanceBetweenPoints(c, this->a);
    return GM::Circle(c, r);
}
GM::Point GM::Triangle::orthocenter()
{
    if (!this->valid()) return GM::Point();
    GM::Segment s1 = altitude(GM::Segment(this->a, this->b), this->c);
    GM::Segment s2 = altitude(GM::Segment(this->a, this->c), this->b);
    return crossPoints(s1, s2)[0];
}
GM::Point GM::Triangle::centroid()
{
    if (!this->valid()) return GM::Point();
    GM::Segment s1(this->a , midpoint(this->b, this->c));
    GM::Segment s2(this->b , midpoint(this->a, this->c));
    return crossPoints(s1, s2)[0];
}
GM::Point GM::Triangle::incenter()
{
    if (!this->valid()) return GM::Point();
    double a = distanceBetweenPoints(this->b, this->c), b = distanceBetweenPoints(this->a, this->c), c = distanceBetweenPoints(this->a, this->b);
    double p = a + b + c;
    return GM::Point( (a*this->a.x + b*this->b.x + c*this->c.x)/p , (a*this->a.y + b*this->b.y + c*this->c.y)/p);
}
GM::Circle GM::Triangle::incircle()
{
    if (!this->valid()) return GM::Circle();
    GM::Point c = this->incenter();
    double r = altitude(GM::Segment(this->a, this->b), c).lenght();
    return GM::Circle(c, r);
}
GM::Circle GM::Triangle::ninePointsCircle()
{
    if (!this->valid()) return GM::Circle();
    GM::Point center = midpoint(this->orthocenter(), this->circumcenter());
    double r = distanceBetweenPoints(center, midpoint(this->a, this->b));
    return GM::Circle(center, r);
}

// Other functions

std::vector<GM::Point> crossPoints(GM::Line a, GM::Line b)
{
    std::vector<GM::Point> ret;
    GM::Point p;

    if (a.straight() == b.straight())
    {
        if (a.straight() == true) return ret;
        double m1 = a.getM(), m2 = b.getM();
        if (m1 == m2) return ret;
        double b1 = a.getB(), b2 = b.getB();
        p.x = (b1 - b2)/(m2 - m1);
        p.y = m1*p.x + b1;
    }
    else
    {
        if (a.straight() == true) std::swap(a, b);
        p.x = b.getB();
        p.y = a.getM()*p.x + a.getB();
    }
    ret.push_back(p);
    return ret;
}
std::vector<GM::Point> crossPoints(GM::Line a, GM::Segment b)
{
    return crossPoints(a, GM::Line(b));
}
std::vector<GM::Point> rossPoints(GM::Segment a, GM::Line b)
{
    return crossPoints(GM::Line(a), b);
}
std::vector<GM::Point> crossPoints(GM::Segment a, GM::Segment b)
{
    return crossPoints(GM::Line(a), GM::Line(b));
}

std::vector<GM::Point> crossPoints(GM::Circle c, GM::Line l)
{
    std::vector<GM::Point> ret;
    GM::Segment height = altitude(l, c.center);
    double distance = height.lenght();

    if (distance > c.radius) return ret;
    if (distance == c.radius)
    {
        ret.push_back(height.b);
        return ret;
    }

    GM::Point p1 = c.center, p2 = c.center;

    if (l.straight() && l.getB() == c.center.x)
    {
        p1 += GM::Vector(0, c.radius);
        p2 -= GM::Vector(0, c.radius);
    }
    else if (std::abs(c.center.y - l.getM()*c.center.x - l.getB()) < 0.0001)
    {
        double m = l.getM();
        GM::Vector v(c.radius/sqrt(m*m+1), c.radius*m/sqrt(m*m + 1));
        p1 += v;
        p2 -= v;
    }
    else
    {
        double an1 = acos(distance/c.radius);
        double an2 = atan2(height.b.y - height.a.y, height.b.x - height.a.x);

        p1.x += cos(an2+an1)*c.radius;
        p1.y += sin(an2+an1)*c.radius;
        p2.x += cos(an2-an1)*c.radius;
        p2.y += sin(an2-an1)*c.radius;
    }
    ret.push_back(p1);
    ret.push_back(p2);
    return ret;
}
std::vector<GM::Point> crossPoints(GM::Line l, GM::Circle c)
{
    return crossPoints(c, l);
}

std::vector<GM::Point> crossPoints(GM::Circle c, GM::Segment s)
{
    GM::Line l = s;
    std::vector<GM::Point> ret;
    GM::Segment height = altitude(l, c.center);
    double distance = height.lenght();

    if (distance > c.radius) return ret;
    if (distance == c.radius)
    {
        if (s.isPointLying(height.b)) ret.push_back(height.b);
        return ret;
    }

    GM::Point p1 = c.center, p2 = c.center;

    if (l.straight() && l.getB() == c.center.x)
    {
        p1 += GM::Vector(0, c.radius);
        p2 -= GM::Vector(0, c.radius);
    }
    else if (abs(c.center.y - l.getM()*c.center.x - l.getB()) < 0.0001)
    {
        double m = l.getM();
        GM::Vector v(c.radius/sqrt(m*m+1), c.radius*m/sqrt(m*m + 1));
        p1 += v;
        p2 -= v;
    }
    else
    {
        double an1 = acos(distance/c.radius);
        double an2 = atan2(height.b.y - height.a.y, height.b.x - height.a.x);

        p1.x += cos(an2+an1)*c.radius;
        p1.y += sin(an2+an1)*c.radius;
        p2.x += cos(an2-an1)*c.radius;
        p2.y += sin(an2-an1)*c.radius;
    }
    if (s.isPointLying(p1)) ret.push_back(p1);
    if (s.isPointLying(p2)) ret.push_back(p2);
    return ret;
}
std::vector<GM::Point> crossPoints(GM::Segment s, GM::Circle c)
{
    return crossPoints(c, s);
}

std::vector<GM::Point> crossPoints(GM::Circle c1, GM::Circle c2)
{
    std::vector<GM::Point> ret;
    if (c1.radius < c2.radius) std::swap(c1, c2);
    if (c1.center.y == c2.center.y)
    {
        double r = distanceBetweenPoints(c1.center, c2.center);
        if (r == 0) return ret;
        if (c1.radius + c2.radius < r) return ret;
        if (r + c2.radius < c1.radius) return ret;

        double an = acos((c1.radius*c1.radius + r*r - c2.radius*c2.radius)/(2*c1.radius*r));
        GM::Vector v1(c1.radius*cos(an), c1.radius*sin(an));
        GM::Vector v2(c1.radius*cos(an), -c1.radius*sin(an));
        if (c1.center.x > c2.center.x)
        {
            v1.x = -v1.x;
            v2.x = -v2.x;
        }

        if (v1.y == 0)
        {
            ret.push_back(c1.center + v1);
        }
        else
        {
            ret.push_back(c1.center + v1);
            ret.push_back(c1.center + v2);
        }

        return ret;
    }
    double m = -(c1.center.x - c2.center.x)/(c1.center.y - c2.center.y);
    double b = -(c1.radius*c1.radius - c2.radius*c2.radius + c2.center.x*c2.center.x - c1.center.x*c1.center.x + c2.center.y*c2.center.y - c1.center.y*c1.center.y)/(2*(c1.center.y - c2.center.y));
    return crossPoints(c1, GM::Line(m, b));
}

std::vector<GM::Segment> tangents(GM::Circle c, GM::Point p)
{
    std::vector<GM::Segment> ret;
    GM::Circle c1(midpoint(c.center, p), distanceBetweenPoints(c.center, p)/2);
    std::vector<GM::Point> v = crossPoints(c, c1);
    for (unsigned int i=0; i<v.size(); i++)
    {
        ret.emplace_back(p, v[i]);
    }
    return ret;
}

GM::Point midpoint(GM::Point a, GM::Point b)
{
    return GM::Point((a.x + b.x)/2 , (a.y + b.y)/2);
}
GM::Point midpoint(GM::Segment s)
{
    return midpoint(s.a, s.b);
}

GM::Line perpendicularBisector(GM::Segment s)
{
    GM::Point p = midpoint(s);
    GM::Line l = s;

    if (l.straight()) return GM::Line(p, GM::Point(p.x + 1, p.y));
    if (s.a.y == s.b.y) return GM::Line(p, GM::Point(p.x, p.y + 1));
    double newM = -1.0/l.getM();
    return GM::Line(p, p + GM::Vector(1, newM));
}

GM::Segment altitude(GM::Line l, GM::Point p)
{
    if (l.straight()) return GM::Segment(p.x, p.y, l.getB(), p.y);
    if (l.getM() == 0) return GM::Segment(p.x, p.y, p.x, l.getB());
    double newM = -1.0/l.getM(), newB = p.y - p.x*newM;
    GM::Point p2 = crossPoints(l, GM::Line(newM, newB))[0];
    return GM::Segment(p, p2);
}
GM::Segment altitude(GM::Segment s, GM::Point p)
{
    return altitude(GM::Line(s), p);
}
GM::Segment altitude(GM::Point p, GM::Line l)
{
    return altitude(l, p);
}
GM::Segment altitude(GM::Point p, GM::Segment s)
{
    return altitude(GM::Line(s), p);
}

double distanceBetweenPoints(GM::Point a, GM::Point b)
{
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

double findAngle(GM::Point a, GM::Point b, GM::Point c)
{
    if (a == b || b == c || a == c) return 0;
    if (GM::Line(a, b) == GM::Line(b, c))
    {
        if (GM::Segment(a, c).isPointLying(b)) return PI;
        else return 0;
    }
    double A = distanceBetweenPoints(b, c);
    double B = distanceBetweenPoints(a, c);
    double C = distanceBetweenPoints(a, b);
    return acos((A*A + C*C - B*B)/(2*A*C));
}

bool areTrianglesCongruent(GM::Triangle a, GM::Triangle b)
{
    if (!a.valid() || !b.valid()) return false;
    double sidesA[3];
    double sidesB[3];
    sidesA[0] = distanceBetweenPoints(a.a, a.b);
    sidesA[1] = distanceBetweenPoints(a.a, a.c);
    sidesA[2] = distanceBetweenPoints(a.c, a.b);
    sidesB[0] = distanceBetweenPoints(b.a, b.b);
    sidesB[1] = distanceBetweenPoints(b.a, b.c);
    sidesB[2] = distanceBetweenPoints(b.c, b.b);
    std::sort(sidesA, sidesA + 3);
    std::sort(sidesB, sidesB + 3);
    if (sidesA[0] == sidesB[0] && sidesA[1] == sidesB[1] && sidesA[2] == sidesB[2]) return true;
    return false;
}
double areTrianglesSimilar(GM::Triangle a, GM::Triangle b)
{
    if (!a.valid() || !b.valid()) return 0;
    double sidesA[3];
    double sidesB[3];
    sidesA[0] = distanceBetweenPoints(a.a, a.b);
    sidesA[1] = distanceBetweenPoints(a.a, a.c);
    sidesA[2] = distanceBetweenPoints(a.c, a.b);
    sidesB[0] = distanceBetweenPoints(b.a, b.b);
    sidesB[1] = distanceBetweenPoints(b.a, b.c);
    sidesB[2] = distanceBetweenPoints(b.c, b.b);
    std::sort(sidesA, sidesA + 3);
    std::sort(sidesB, sidesB + 3);
    double k = sidesA[0]/sidesB[0];
    if (sidesA[1]/sidesB[1] == k && sidesA[2]/sidesB[2] == k) return k;
    return 0;
}

GM::Line angleBisector(GM::Point a, GM::Point b, GM::Point c)
{
    GM::Vector v1 = a.toVector() - b.toVector(), v2 = c.toVector() - b.toVector();
    if (v1.x == -v2.x && v1.y == v2.y)
    {
        return GM::Line(b, b + GM::Vector(0, 1));
    }
    double A = distanceBetweenPoints(b, c);
    double C = distanceBetweenPoints(a, b);
    double mm = (A*(a.y - b.y) + C*(c.y - b.y))/(A*(a.x - b.x) + C*(c.x - b.x));
    double bb = b.y - mm*b.x;
    return GM::Line(mm, bb);
}
GM::Line angleBisector(GM::Line l1, GM::Line l2, int arg)
{
    double an1, an2;
    if (l1.straight()) an1 = PI/2;
    else an1 = atan(l1.getM());
    if (l2.straight()) an2 = PI/2;
    else an2 = atan(l2.getM());

    double an = (an1 + an2)/2;

    if (arg == 0)
    {
        if (an1 > an2) an+=PI/2;
    }
    else
    {
        if (an2 > an1) an+=PI/2;
    }

    if (an1 == an2)
    {
        double b = (l1.getB() + l2.getB())/2;
        if (an1 == PI/2)
        {
            return GM::Line(GM::Point(b, -100), GM::Point(b, 100));
        }
        return GM::Line(l1.getM(), b);
    }
    else
    {
        GM::Point p = crossPoints(l1, l2)[0];
        if (an == PI/2)
        {
            return GM::Line(p, p + GM::Vector(0, 100));
        }
        double m = tan(an);
        double b = p.y - m*p.x;
        return GM::Line(m, b);
    }
}
GM::Line angleBisector(GM::Segment s, GM::Line l, int arg)
{
    return angleBisector(GM::Line(s), l, arg);
}
GM::Line angleBisector(GM::Line l, GM::Segment s, int arg)
{
    return angleBisector(l, GM::Line(s), arg);
}
GM::Line angleBisector(GM::Segment s1, GM::Segment s2, int arg)
{
    return angleBisector(GM::Line(s1), GM::Line(s2), arg);
}
