# Creational Pattern Comparison

## Builder vs Factory Method vs Prototype

- Use **Builder** when one object needs step-by-step assembly, such as `HtmlBuilder` adding children.
- Use **Factory Method** when the main question is *which way should this product be created?*, such as polar versus Cartesian `Point` input.
- Use **Prototype** when a ready-made object is the best starting point and you need a copy.
- Common confusion: a builder creates one object gradually; a factory method chooses and returns it in one request.

## Factory Method vs Abstract Factory

- Use **Factory Method** for alternate ways to make one product, such as `Point::NewCartesian` and `Point::NewPolar`.
- Use **Abstract Factory** for a family of related products or factories, such as `CoffeeFactory` and `TeeFactory` behind `DrinkFactory`.

## Singleton vs the others

- Use **Singleton** for lifetime/identity: callers must share one instance.
- Use Builder, Factory, or Prototype for *how a new instance is made*.
