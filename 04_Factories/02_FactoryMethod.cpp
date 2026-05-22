#include "../header.h"

class Point{
    // encapsulation - we want to hide the implementation details of the class -- oop move
    Point(float x, float y) : x(x), y(y) {}
public:
    float x, y;

    // factory method - static method that creates an object of the class
    static Point NewCartesian(float x, float y)
    { 
        // return the privete constructor, it is the only way to create a point, and it is more descriptive
        return {x, y}; 
    }
    
    static Point NewPolar(float r, float theta) 
    { 
        return {r*cos(theta), r*sin(theta)}; 
    }

    friend ostream &operator<<(ostream  &os, const Point &p) {
        os << "x: " << p.x << ", y: " << p.y;
        return os;
    }
};

int main() {
    auto p = Point::NewPolar(5, M_PI_4);
    cout << p << endl;
    
    return 0;
}
