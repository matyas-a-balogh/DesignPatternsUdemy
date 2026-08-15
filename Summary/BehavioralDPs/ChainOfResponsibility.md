# Chain of Responsibility

## Real-life example

A customer request moves from support agent to supervisor to manager until someone can handle it.

## Explain it like I'm in kindergarten

Ask the first grown-up. If they cannot help, they pass your question along to the next helper.

## The code that really matters

`14_ChainOfResponsibility/02_BrokerChain.cpp`

```cpp
Query q{name, Query::Argument::attack, attack};
game.queries(q);

conn = game.queries.connect([&](Query& q) { q.result *= 2; });
```

`Creature` sends a query through `Game`; subscribed modifiers can inspect and change it. The sender does not need to know which modifiers exist.

## What to remember

- Pass a request through possible handlers.
- Each handler may handle, change, or ignore it.
- This example uses a signal broker rather than explicit `next` pointers.
