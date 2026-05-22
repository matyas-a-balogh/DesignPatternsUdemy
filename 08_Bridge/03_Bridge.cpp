#include "../header.h"

// Shapes - circle, square
// Renderer - raster, vector

// No 2x2 renderer, but 2 hierarchical system
// abstraction and implementation - refactorguru

struct Renderer
{
    virtual void render_circle(float x, float y, float radius) = 0;
};

struct VectorRenderer : Renderer
{
    void render_circle(float x, float y, float radius) override {
        cout << "Vector render circle at (" << x << ", " << y 
             << "), radius: " << radius << endl;
    }
};

struct RasterRenderer : Renderer
{
    void render_circle(float x, float y, float radius) override {
        cout << "Raster render circle at (" << x << ", " << y 
             << "), radius: " << radius << endl;
    }
};

struct Shape
{
// bridge
protected:
    Renderer& renderer;
    Shape(Renderer &renderer) : renderer(renderer) {}
public:
    // all kinds of fn-s
    virtual void draw() = 0;
    virtual void resize(float factor) = 0;
};

struct Circle : Shape
{
    float x, y, radius;
    
    Circle(Renderer &renderer, float x, float y, float radius) : 
        Shape(renderer), x{x}, y{y}, radius{radius} {}

    // it is fun - any renderer can be used
    void draw() override { 
        renderer.render_circle(x,y,radius);
    }

    void resize(float factor) override {radius *= factor;}

};

int main()
{
    RasterRenderer rr;
    Circle raster_circle{rr,5,5,5};
    raster_circle.draw();
    raster_circle.resize(2);
    raster_circle.draw();

    VectorRenderer vr;
    Circle vector_circle{vr,5,5,5};
    vector_circle.draw();
    vector_circle.resize(3);
    vector_circle.draw();
}
