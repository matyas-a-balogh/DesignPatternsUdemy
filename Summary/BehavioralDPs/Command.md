# Command

## Real-life example

A restaurant ticket says what to cook. The waiter can queue it, and the kitchen can later cancel or reverse it.

## Explain it like I'm in kindergarten

Write “put 10 coins in” on a card. Later, use the same card to do it, or use its undo rule to take the coins back.

## The code that really matters

`15_Command/02_Undo.cpp`

```cpp
struct Command { virtual void call() = 0; virtual void undo() = 0; };
void BankAccountCommand::call() { /* deposit or withdraw */ }
void BankAccountCommand::undo() { /* perform the opposite */ }
```

The account operation becomes a separate object that carries receiver, action, and amount. That object can be stored, executed later, and undone.

## What to remember

- Turn a request into an object.
- Commands enable queues, logs, macros, and undo.
- The command knows the receiver and how to invoke it.
