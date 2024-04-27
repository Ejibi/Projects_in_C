#include "2DMotion.h"
#include <iostream>
#include <cmath>
#include <iomanip>

std::istream& operator>>(std::istream& is, Point& point) {
    is >> point.x >> point.y;
    return is;
}

std::istream& operator>>(std::istream& is, Force& force) {
    is >> force.angle >> force.magnitude;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Point& point) {
    os << "(" << std::fixed << std::setprecision(2) << point.x << ", " << point.y << ")";
    return os;
}


std::ostream& operator<<(std::ostream& os, const Force& force) {
    os << std::fixed << std::setprecision(2) << force.angle << " degrees with magnitude of " << force.magnitude;
    return os;
}


Point operator+(const Point& point, const Force& force) {
    Point newPoint;
    float radians = force.angle * (PI / 180.0);
    float horizontalComponent = force.magnitude * std::cos(radians);
    float verticalComponent = force.magnitude * std::sin(radians);
    newPoint.x = point.x + horizontalComponent;
    newPoint.y = point.y + verticalComponent;
    return newPoint;
}


Force operator*(const Force& force, int scalar) {
    Force result;
    result.magnitude = force.magnitude * scalar;
    result.angle = force.angle; 
    return result;
}

int Point::quadrant() const {
    if (x > 0 && y > 0) return 1;
    else if (x < 0 && y > 0) return 2;
    else if (x < 0 && y < 0) return 3; 
    else if (x > 0 && y < 0) return 4; 
    else return 1;
}