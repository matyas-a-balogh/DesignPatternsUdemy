#include "../header.h"


struct Shape
{
    virtual string str() const = 0;
};

// there is Circle and Square - how to add Color??

struct Circle : Shape
{
    float radius;

    Circle() {}

    Circle(float radius) : radius(radius) {}

    void resize(float factor)
    {
        radius *= factor;
    }

    string str() const override{
        ostringstream oss;
        oss << "A circle of radius " << radius;
        return oss.str();
    }
};

struct Square : Shape
{
    float side;

    Square() {}

    Square(float side) : side(side) {}

    string str() const override{
        ostringstream oss;
        oss << "A square with side " << side;
        return oss.str();
    }
};

// add color

// Decorator: implements same IF, stores the obj it wraps, add behaviot without changing the original class
struct ColoredShape : Shape
{
    // stores object
    Shape& shape;
    string color;

    ColoredShape(Shape &shape, const string &color) : shape(shape), color(color) {}

    // implements the same interface - important!
    string str() const override{
        ostringstream oss;
        // adds new functionality
        oss << shape.str() << " has the color " << color;
        return oss.str();
    }
};

// Decorator
struct TransparentShape : Shape
{
    Shape& shape;
    uint8_t transparency;

    TransparentShape(Shape &shape, uint8_t transparency) : shape(shape), transparency(transparency) {}

    string str() const override{
        ostringstream oss;
        oss << shape.str() << " has " << static_cast<float>(transparency) / 255.f * 100.f << "% transparency" << endl;
        return oss.str();
    }
};

int main()
{
    // you can do TransparentShape from a ColoredShape, vica-versa
    Square square{5};
    ColoredShape red_square{square, "red"};

    cout << square.str() << endl << red_square.str() << endl;

    TransparentShape my_square{red_square, 51};
    cout << my_square.str() << endl;

    
    // you can make a ColoredShape{ColoredShape{ColoredShape{...}}}
    Square square2{10};
    ColoredShape blue{square2, "blue"};
    ColoredShape red{blue, "red"};
    cout << red.str() << endl;
    

    // 1 downside:
    Circle circle{5};
    // as soon as decorated, it is restricted by the circle IF
    ColoredShape red_circle{circle, "red"};
    // cout << red_circle.resize() << endl; // doesnt work
    // you dont have acces to underlying API
}
