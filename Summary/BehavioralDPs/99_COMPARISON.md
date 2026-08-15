# Behavioral Pattern Comparison

## Strategy vs State

- Use **Strategy** when a client deliberately selects an algorithm, such as Markdown versus HTML formatting.
- Use **State** when an object’s current condition selects behavior and transitions itself, such as `OffState` becoming `OnState`.
- Common confusion: both delegate to another object; strategy is a chosen policy, state models a changing lifecycle.

## Observer vs Mediator

- Use **Observer** to broadcast that something changed to independent subscribers.
- Use **Mediator** to coordinate how peer objects communicate, such as `ChatRoom` routing messages.
- Common confusion: both reduce coupling; observer is notification, mediator is collaboration/routing.

## Command vs Memento

- Use **Command** to represent an action and optionally reverse it with `undo()`.
- Use **Memento** to save a state snapshot and restore it.
- Common confusion: both support undo. Commands store intent/operation; mementos store state.

## Template Method vs Strategy

- Use **Template Method** when a base class fixes the algorithm order and subclasses provide steps.
- Use **Strategy** when an object swaps a complete algorithm through composition.

## Chain of Responsibility vs Mediator

- Use **Chain of Responsibility** when a request passes through possible handlers/modifiers.
- Use **Mediator** when a central object routes or coordinates interactions among peers.

## Iterator, Interpreter, Visitor

- **Iterator** moves through a structure; **Interpreter** gives a language/tree meaning; **Visitor** runs different operations over a known object hierarchy.
