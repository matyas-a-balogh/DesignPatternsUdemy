# Factory Method

## Real-life example

A map app offers “enter coordinates as a grid” or “enter distance and direction,” then creates the same location either way.

## Explain it like I'm in kindergarten

Tell the point maker how you know where the point is. It makes the point in the right way for you.

## The code that really matters

`04_Factories/02_FactoryMethod.cpp`

```cpp
static Point NewPolar(float r, float theta) {
  return {r*cos(theta), r*sin(theta)};
}
```

The private `Point` constructor forces callers through named creation methods. `NewPolar` converts polar input while still returning a `Point`.

## What to remember

- Put creation behind a named method when inputs can mean different things.
- Factory Method returns one product through a creation method.
- The named method makes the caller's intent clear.
