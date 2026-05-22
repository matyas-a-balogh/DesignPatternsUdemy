#include "../header.h"

class Point{
public:
    // friend class PointFactory; // violated open-close principle, but its needed
    Point(float x, float y) : x(x), y(y) {} // or you can make everything public and its reachable wout o-c princ
// public:
    float x, y;

    friend ostream &operator<<(ostream  &os, const Point &p) {
        os << "x: " << p.x << ", y: " << p.y;
        return os;
    }
};

// Dedicated factory (not abstract)
// in GoF book, there is only Factory Method and Abstr. Factory, no Factory
struct PointFactory{
    // doesnt have to be static
    static Point NewCartesian(float x, float y)
    { 
        return {x, y}; 
    }
    
    static Point NewPolar(float r, float theta) 
    { 
        return {r*cos(theta), r*sin(theta)}; 
    }

};

int main() {
    auto p = PointFactory::NewPolar(5, M_PI_4);
    cout << p << endl;
    
    return 0;
}
