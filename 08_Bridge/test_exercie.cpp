#include <string>
#include <iostream>
using namespace std;

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


struct Shape
{
protected:
    const Renderer& renderer;
    string name; // this has to be 2. bc init order :D
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
