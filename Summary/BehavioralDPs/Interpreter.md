# Interpreter

## Real-life example

A calculator reads “(13-4)-(12+1),” understands the symbols, and works out the answer.

## Explain it like I'm in kindergarten

First sort the number and plus/minus blocks. Then build a little math tree and ask the tree for its answer.

## The code that really matters

`16_Interpreter/02_HandmadeParsing.cpp`

```cpp
vector<Token> lex(const string& input);
shared_ptr<Element> parse(const vector<Token>& tokens);
int BinaryOperation::eval() const { return left->eval() - right->eval(); }
```

`lex()` turns text into tokens, `parse()` creates `Integer` and `BinaryOperation` objects, and `eval()` gives each expression its meaning.

## What to remember

- Represent a small language with objects/tree nodes.
- Parsing builds the structure; interpretation evaluates it.
- Use a parser library for real languages with complex grammar.
