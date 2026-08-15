# Proxy

## Real-life example

A receptionist answers for a doctor and only calls the doctor when an appointment actually needs them.

## Explain it like I'm in kindergarten

A helper stands in front of a big toy. Ask the helper to draw it, and the helper fetches the toy only when needed.

## The code that really matters

`13_Proxy/03_VirtualProxy.cpp`

```cpp
struct LazyBitmap : Image {
  Bitmap* bitmap{nullptr};
  void draw() override {
    if (!bitmap) bitmap = new Bitmap(filename);
    bitmap->draw();
  }
};
```

`LazyBitmap` has the same `Image` interface as `Bitmap`, but controls access by delaying the costly load until `draw()`.

## What to remember

- Stand in for another object and control access to it.
- A proxy preserves the expected interface.
- Virtual proxies delay expensive work; other proxies protect, cache, or communicate.
