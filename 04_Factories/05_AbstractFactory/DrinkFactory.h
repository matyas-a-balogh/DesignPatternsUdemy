#include "HotDrink.h"
#include "HotDrinkFactory.h"
#include <map>

using namespace std;

// We have a corresponfing family of factories
class DrinkFactory
{
    map<string, unique_ptr<HotDrinkFactory>> hot_factories;
public:
    DrinkFactory()
    {
        //using polymorphism
        hot_factories["coffee"] = make_unique<CoffeeFactory>();
        hot_factories["tee"] = make_unique<TeeFactory>();
    }

    unique_ptr<HotDrink> make_drink(const string& name)
    {
        auto drink = hot_factories[name]->make();
        drink->prepare(200);
        return drink;
    }
}
