# Facade

## Real-life example

At a hotel desk, you ask for a room; the receptionist handles keys, payment, cleaning, and records behind the scenes.

## Explain it like I'm in kindergarten

Instead of pushing lots of confusing buttons, press one big “make my window” button.

## The code that really matters

`11_Facade/Bloom_example_project/Bloom.cpp`

```cpp
auto window = Console::instance().multicolumn("Test", 2, 40, 40);
window->buffers[1]->add_string(...);
window->Show();
```

`Console` presents a small, convenient entry point for building a multi-column console. It hides coordination of `Window`, `Viewport`, and `TextBuffer` objects.

## What to remember

- Provide a simpler front door to a complicated subsystem.
- It simplifies use; it does not change an incompatible interface.
- Clients may still access subsystem objects when needed.
