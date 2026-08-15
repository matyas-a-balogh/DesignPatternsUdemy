# Structural Pattern Comparison

## Adapter vs Decorator vs Proxy

- Use **Adapter** when two existing interfaces do not fit; translate `Line` into iterable `Point`s.
- Use **Decorator** when the object needs extra behavior; wrap `Shape` with color or transparency.
- Use **Proxy** when access to the same kind of object must be controlled; `LazyBitmap` delays loading.
- Common confusion: all wrap an object, but adapter changes the usable interface, decorator adds responsibilities, and proxy controls access.

## Bridge vs Adapter

- Use **Bridge** before or during design when two class dimensions should vary independently, such as `Shape` and `Renderer`.
- Use **Adapter** later to make already incompatible code cooperate.

## Composite vs Decorator

- Use **Composite** to treat one object and a group alike, such as `Neuron` and `NeuronLayer`.
- Use **Decorator** to add behavior to one wrapped object. Both recurse, but their intent differs.

## Facade vs Proxy

- Use **Facade** for a simpler API over many subsystem classes.
- Use **Proxy** as a stand-in for one object with the same interface.

## Flyweight

- Unlike the others, **Flyweight** is mainly about sharing repeated data to reduce memory use, not changing APIs or access.
