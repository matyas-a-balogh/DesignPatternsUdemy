#include <math.h>

/*
struct Point{
    Point(float x, float y) : x(x), y(y) {}
    // it is not allowed to have the same argument types
    Point(float rho, float theta) : x(rho * cos(theta)), y(rho * sin(theta)) {}
    float x, y;
};
*/

enum class PointType{
    cartesian,
    polar
};

struct Point{
    // now a and b is not descriptive, and documentation is not the best
    // its insufficient to have two constructors with the same argument types, we need to distinguish them
    Point(float a, float b, PointType type = PointType::cartesian) {
        if (type == PointType::cartesian){
            x = a;
            y = b;
        } else {
            x = a*cos(b);
            y = a*sin(b);
    }
    float x, y;
};
