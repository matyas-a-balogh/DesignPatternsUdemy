#include "../header.h"


struct Shape
{
    virtual string str() const = 0;
};

struct Circle : Shape
{
    float radius;

    Circle() {}

    Circle(float radius) : radius(radius) {}

    void resize(float factor) { radius *= factor; }

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

// restrict T to Shape-s only
// saying for ColoredShape: this decorator only  works for Shape-s
template <typename T> concept IsAShape = std::is_base_of<Shape, T>::value;

// static: bake code into existing obj
// 1. step: mixin inheritance (only C++)
// it basically "mixes in" extra behavior onto T (it inherits from T too)
// ColoredShape is a new type as a result
template <IsAShape T> struct ColoredShape : T
{
    // i want T to be a Shape - so i use concept
    // C++20: concept - ths is for explicit intention with Shape and safety guard
    
    string color;

    ColoredShape() {} // just in case i need default constructor

    // 2. step: perfect forwarding
    // bunch of args, not concrete baseclass
    // it accepts whatever arg remain and forwards it to T
    template<typename... Args> ColoredShape(const string& color, Args&& ...args) : T(std::forward<Args>(args)...), color{color} {}

    string str() const override{
        ostringstream oss;
        // T is baseclass - get baseclasse's str()
        oss << T::str() << " has the color " << color;
        return oss.str();
    }
};

// do the same for transparency
template <IsAShape T> struct TransparentShape : T
{
    uint8_t transparency;

    template<typename... Args> TransparentShape(const uint8_t transparency, Args&& ...args) : T(std::forward<Args>(args)...), transparency{transparency} {}

    string str() const override{
        ostringstream oss;
        oss << T::str() << " has " << static_cast<float>(transparency) / 255.f * 100.f << "% transparency";
        return oss.str();
    }
};

int main()
{
    ColoredShape<Circle> redCircle;
    redCircle.resize(1.0f); // now i can do it

    ColoredShape<Circle> green_circle{"green", 5}; // forwarding: green to ColoredShape, 5 to underlying T
    cout << green_circle.str() << endl;

    // static: you effectively make a new type (multiple new types)
    TransparentShape<ColoredShape<Square>> blue_invis{0, "blue", 10}; // it can be merged - pass 10 to Square, blue to ColoredShape, 0 to Transp...
    blue_invis.color = "ligh blue"; // you reach the baseclass memberaccess
    blue_invis.side = 20;
    cout << blue_invis.str() << endl;
}
