# Adapter

## Real-life example

A travel plug adapter lets a charger with one plug shape work in a wall socket with another shape.

## Explain it like I'm in kindergarten

You have square blocks but the game needs round dots. An adapter turns the blocks into dots so the game can use them.

## The code that really matters

`07_Adapter/AdapterVisual/AdapterVisualDlg.cpp`

```cpp
struct LineToPointAdapter {
  Points points;
  LineToPointAdapter(Line& line) { /* make Point values from line */ }
  Points::iterator begin() { return points.begin(); }
  Points::iterator end() { return points.end(); }
};
```

The drawing code expects an iterable sequence of `Point`s, while the source is a `Line`. The adapter converts that incompatible representation and exposes the expected iteration interface.

## What to remember

- Make incompatible interfaces work together.
- The adapter translates; it does not add a new responsibility.
- It can also cache converted results, as `LineToPointCachingAdapter` does.
