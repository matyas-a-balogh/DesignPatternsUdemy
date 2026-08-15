# Iterator

## Real-life example

A museum guide walks visitors through exhibits in a chosen order without exposing the museum’s storage rooms.

## Explain it like I'm in kindergarten

Hold a finger on one tree picture, then say “next” to visit each picture without needing to know how the tree is kept.

## The code that really matters

`17_Iterator/02_BinaryTreeIterator.cpp`

```cpp
iterator begin() { /* choose first node */ return iterator(n); }
iterator end() { return iterator(nullptr); }
PreOrderIterator<U>& operator++() { /* advance current */ }
```

`BinaryTree` exposes `begin`, `end`, dereference, and increment, so callers traverse through a standard iterator interface instead of managing tree navigation.

## What to remember

- Traverse a collection without exposing its internals.
- The iterator keeps traversal position and next-step logic.
- Note: the file’s comments correctly flag that its named preorder traversal does not currently output true preorder.
