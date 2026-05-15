#include <iostream>
using namespace std;


// We have a family of products
struct HotDrink
{
    virtual ~HotDrink() = default;
    virtual void prepare(int volume) = 0;
};

struct Tee: public HotDrink
{
    void prepare(int volume) override
    {
        cout << "Take tea bag, boil water, pour " << volume << " ml, add lemon!" << endl;
    }
};

struct Coffee: public HotDrink
{
    void prepare(int volume) override
    {
        cout << "Grind some beans, boil water, pour " << volume << " ml, add cream!" << endl;
    }
};
