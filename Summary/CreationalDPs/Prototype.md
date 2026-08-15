# Prototype

## Real-life example

A real-estate agent copies a standard listing, then changes the address and owner for the next apartment.

## Explain it like I'm in kindergarten

Instead of drawing a new picture from nothing, make a copy of your picture and color one part differently.

## The code that really matters

`05_Prototype/02_Prototype.cpp`

```cpp
Contact(const Contact& other) : name{other.name},
  address{new Address{*other.address}} {}

Contact jane{john};
jane.address->suite = 103;
```

The copy constructor makes a new `Address`, not just a new pointer. That deep copy lets Jane change her suite without changing John’s.

## What to remember

- Create a new object by copying a configured example.
- Decide whether copying must be shallow or deep.
- Use it when setup is expensive or repetitive.
