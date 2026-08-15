# Decorator

## Real-life example

Start with a plain ice cream, then add chocolate sauce and sprinkles; each addition keeps the original dessert and adds something.

## Explain it like I'm in kindergarten

Put a red sticker on a square, then a shiny sticker on top. It is still the same square, just with extra things.

## The code that really matters

`10_Decorator/01_DynamicDecorator.cpp`

```cpp
struct ColoredShape : Shape {
  Shape& shape;
  string str() const override {
    return shape.str() + " has the color " + color;
  }
};
```

The decorator implements the same `Shape` interface, stores a `Shape`, and delegates before adding its own result. Therefore decorators can be stacked.

## What to remember

- Add behavior by wrapping an object.
- Wrapper and wrapped object share the same interface.
- Stack decorators for combinations without subclass explosion.
