#include "../header.h"

class Point{
    Point(float x, float y) : x(x), y(y) {}
    float x, y;
public:
    friend ostream &operator<<(ostream  &os, const Point &p) {
        os << "x: " << p.x << ", y: " << p.y;
        return os;
    }

    // There was no connection between the Point and the PointFactory
    // Make an inner class - helper for how it should be used
    // Ups for inner class:
    // You get access to private members of the Point class
    // You can make it private (_2 file), but then you need to make a singleton instance of the factory
    class PointFactory{
        PointFactory(){}
    public:
        static Point NewCartesian(float x, float y)
        { 
            return {x, y}; 
        }
        
        static Point NewPolar(float r, float theta) 
        { 
            return {r*cos(theta), r*sin(theta)}; 
        }
    };
};

int main() {
    auto p = Point::PointFactory::NewPolar(5, M_PI_4);
    cout << p << endl;
    
    return 0;
}
