# Visitor

## Real-life example

A museum inspector can count, clean, or photograph each type of exhibit without putting every new job inside every exhibit class.

## Explain it like I'm in kindergarten

Each math shape lets a printer visitor or a calculator visitor visit it. The visitor knows what job to do for that exact shape.

## The code that really matters

`24_Visitor/03_ClassicVisitor.cpp`

```cpp
void AdditionExpression::accept(ExpressionVisitor* visitor) {
  visitor->visit(this);
}
void ExpressionPrinter::visit(AdditionExpression* ae) { /* print */ }
```

`accept()` sends the concrete `this` type to the visitor. This double dispatch chooses the matching operation, letting new operations such as printing and evaluation live in visitors.

## What to remember

- Add operations across an object hierarchy without editing every operation into it.
- `accept(visitor)` plus overloaded `visit(concrete type)` is the key.
- Easy to add visitors; costly to add new element types.
