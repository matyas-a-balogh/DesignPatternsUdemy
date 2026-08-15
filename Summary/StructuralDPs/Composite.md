# Composite

## Real-life example

A folder can contain files and other folders, but you can ask either one for its size.

## Explain it like I'm in kindergarten

One Lego brick and a whole Lego box can both be called “Lego.” You can connect one brick to another brick or to a whole box.

## The code that really matters

`09_Composite/02_NeuralNetworks.cpp`

```cpp
struct Neuron : SomeNeurons<Neuron> {
  Neuron* begin() { return this; }
  Neuron* end() { return this + 1; }
};
struct NeuronLayer : vector<Neuron>, SomeNeurons<NeuronLayer> {};
```

Both a single `Neuron` and a `NeuronLayer` can be iterated and inherit `connect_to`. That lets one operation treat an individual and a collection uniformly.

## What to remember

- Treat a single object and a group through the same operation.
- A leaf and a composite share a useful interface.
- Great for trees and nested part-whole structures.
