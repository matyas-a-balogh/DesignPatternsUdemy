# Bridge

## Real-life example

The same remote control can operate different TV brands because the remote’s buttons and the TV’s internal electronics vary independently.

## Explain it like I'm in kindergarten

A circle can ask either a crayon robot or a pixel robot to draw it. The circle does not need to know how each robot works.

## The code that really matters

`08_Bridge/03_Bridge.cpp`

```cpp
struct Shape { protected: Renderer& renderer; };
struct Circle : Shape {
  void draw() override { renderer.render_circle(x, y, radius); }
};
```

`Shape` keeps a `Renderer` separately from its own shape hierarchy. A `Circle` can therefore work with either `RasterRenderer` or `VectorRenderer`.

## What to remember

- Split two dimensions that should vary independently.
- Here: shape type and rendering method.
- The bridge is the composition link to the implementation hierarchy.
