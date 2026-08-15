# Abstract Factory

## Real-life example

A coffee machine accepts “coffee” or “tea” and uses the matching preparation station without making you operate its boiler and filters.

## Explain it like I'm in kindergarten

Tell the drink machine what you want. It picks the right drink helper, and that helper knows how to make it.

## The code that really matters

`04_Factories/05_AbstractFactory/DrinkFactory.h`

```cpp
hot_factories["coffee"] = make_unique<CoffeeFactory>();
hot_factories["tee"] = make_unique<TeeFactory>();

unique_ptr<HotDrink> make_drink(const string& name) {
  auto drink = hot_factories[name]->make();
  drink->prepare(200);
  return drink;
}
```

`DrinkFactory` selects a concrete `HotDrinkFactory`, which creates its matching `HotDrink`. The caller asks for a product family through a common abstraction.

## What to remember

- Create related concrete products without exposing their concrete classes.
- The factory interface is the switch point between product families.
- Add a new family by adding a factory that follows the same interface.
