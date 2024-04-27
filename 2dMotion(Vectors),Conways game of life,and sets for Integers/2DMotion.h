#ifndef MOTION2D
#define MOTION2D
#include <iostream>

// Predefined constant for pi, to be used if/when converting degrees
// to radians.
#define PI 3.14159265

// Forward declation of Force. Needed in case any of Point references
// the existence of type Force.
class Force;

class Point {
    // Private fields and helpers here.
    float x;
    float y;
  public:
    // Required public interface here.
    Point() : x(0), y(0) {}
    int quadrant() const;
    friend std::istream& operator>>(std::istream& is, Point& point);
    friend std::ostream& operator<<(std::ostream& os, const Point& point);
    friend Point operator+(const Point& point, const Force& force);
};

class Force {
    // Private fields and helpers here.
  public:
    float angle;
    float magnitude;
    // Required public interface here.
    // Friend declarations for overloaded operators
    friend std::istream& operator>>(std::istream& is, Force& force);
    friend std::ostream& operator<<(std::ostream& os, const Force& force);
    friend Force operator*(const Force& force, int scalar);
};

#endif
