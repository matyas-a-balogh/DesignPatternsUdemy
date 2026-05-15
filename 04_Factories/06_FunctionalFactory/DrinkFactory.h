#include "HotDrink.h"
#include <memory>
#include <map>
#include <functional>

using namespace std;

// not oop, functional approach
class DrinkWithVolumeFactory
{
    // lets use lambda function - autonom - more versatile
    map<string, function<unique_ptr<HotDrink>()>> factories;
public:
    // this is the factory method, its just encapsulated
    // instead of creatung HotDrinkFactory.h with all declarations, its all here
    DrinkWithVolumeFactory()
    {
        factories["tee"] = [] {
            auto tee = make_unique<Tee>();
            tee->prepare(200); // note: volume can be easily parameterized
            return tee;
        };

        factories["coffee"] = [] {
            auto coffee = make_unique<Coffee>();
            coffee->prepare(200);
            return coffee;
        };
    }

    unique_ptr<HotDrink> make_drink(const string& name)
    {
        // simply invoke it
        // not based on inheritance
        return factories.at(name)();
    }
};
