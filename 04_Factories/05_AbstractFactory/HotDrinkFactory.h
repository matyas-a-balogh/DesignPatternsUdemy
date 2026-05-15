#include "HotDrink.h"
#include <memory>

// Abstract Factory - we inherit from this
struct HotDrinkFactory
{
    virtual unique_ptr<HotDrink> make() const = 0;
};

struct TeeFactory : HotDrinkFactory
{
    unique_ptr<HotDrink> make() const override
    {
        return make_unique<Tee>();
    }
};

struct CoffeeFactory : HotDrinkFactory
{
    unique_ptr<HotDrink> make() const override
    {
        return make_unique<Coffee>();
    }
};
