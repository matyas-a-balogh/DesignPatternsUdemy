#include <iostream>
#include <math.h>

using namespace std;

class Point{
    Point(float x, float y) : x(x), y(y) {}
    float x, y;
public:
    friend ostream &operator<<(ostream  &os, const Point &p) {
        os << "x: " << p.x << ", y: " << p.y;
        return os;
    }
    
    static PointFactory Factory; // this is the only instance of the factory, it is static, so it is shared between all instances of the Point class
    
// If i make it private, i need a singleton instance
private:
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
