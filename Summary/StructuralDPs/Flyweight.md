# Flyweight

## Real-life example

A library keeps one copy of each book title’s information and uses it for many borrowed copies, rather than rewriting it on every card.

## Explain it like I'm in kindergarten

Many letters can share one little “make this part big” note instead of every letter carrying its own note.

## The code that really matters

`12_Flyweight/03_TextFormatting.cpp`

```cpp
struct TextRange { int start, end; bool capitalized; };
TextRange& get_range(int start, int end) {
  formatting.emplace_back(TextRange{start, end});
  return *formatting.rbegin();
}
```

`BetterFormattedText` stores a few ranges instead of one formatting flag per character. Each `TextRange` is shared compact state that covers many characters.

## What to remember

- Share reusable, intrinsic state to save memory.
- Keep changing, contextual state outside the shared object.
- Helpful only when many objects repeat the same data.
