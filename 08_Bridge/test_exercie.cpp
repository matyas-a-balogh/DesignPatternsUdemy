#include <string>
#include <iostream>
using namespace std;

// the implementation side
// this does the low-level work behind abstraction
// so how to create the abstraction
struct Renderer
{
  virtual string what_to_render_as() const = 0;
};

struct VectorRenderer : Renderer
{
  string what_to_render_as() const override { return "lines";} ;
};

struct RasterRenderer : Renderer
{
  string what_to_render_as() const override { return "pixels";} ;
};

// abstraction side
// i want this, but it doesnt know how to draw it
// so you create a Shape and tell it how to make it
struct Shape
{
protected:
    // this is the bridge part
    const Renderer& renderer;
    string name; // this has to be 2. bc init order :D
    // lets every Shape use any Renderer
    Shape(const Renderer &renderer, const string& name) : renderer(renderer), name(name) {}
public:
    string str() const { return "Drawing " + name + " as " + renderer.what_to_render_as(); }
    
};

struct Triangle : Shape
{
    Triangle(const Renderer &renderer) : Shape(renderer, "Triangle") {}
};

struct Square : Shape
{
    Square(const Renderer &renderer) : Shape(renderer, "Square") {}
};


int main()
{
    cout << Triangle(RasterRenderer()).str() << endl;
    cout << Square(VectorRenderer()).str() << endl;
    return 0;
}
