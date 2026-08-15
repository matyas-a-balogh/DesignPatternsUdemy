# Builder

## Real-life example

A restaurant order form lets you add a burger, toppings, and a drink one step at a time before receiving the finished meal.

## Explain it like I'm in kindergarten

Build a big Lego house by adding one piece at a time. The builder remembers every piece and gives you the house at the end.

## The code that really matters

`03_Builder/02_Builder.cpp`

```cpp
struct HtmlBuilder {
  HtmlElement root;
  void add_child(string child_name, string child_text) {
    root.elements.emplace_back(child_name, child_text);
  }
};
```

`HtmlBuilder` owns the partly built `HtmlElement`. `add_child()` hides the assembly details and lets the caller construct complex HTML incrementally.

## What to remember

- Use it when construction has many ordered or optional steps.
- The builder gathers parts; the product is the final object.
- A fluent builder is the same idea with chainable calls.
