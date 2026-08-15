# Singleton

## Real-life example

A building has one shared fire-alarm control panel; every guard uses that same panel.

## Explain it like I'm in kindergarten

There is one special toy box for the whole classroom. Everyone can use it, but there is only one box.

## The code that really matters

`06_Singleton/04_SingletonLifetime.cpp`

```cpp
di::bind<IFoo>().to<Foo>().in(di::singleton)

cout << (bar1->foo.get() == bar2->foo.get()) << endl;
```

The DI container gives both `Bar` objects the same `Foo` instance. The pointer comparison demonstrates the shared lifetime.

## What to remember

- Singleton means one shared instance for a chosen scope.
- Prefer DI-managed lifetime over a hidden global when possible.
- Shared mutable state can make tests and concurrency harder.
