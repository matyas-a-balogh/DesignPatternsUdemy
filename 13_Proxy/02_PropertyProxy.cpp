#include "../header.h"

template <typename T> struct Property
{
    T value;

    Property(T value){
        *this = value;
    }

    // set value
    T operator=(T new_value){
        cout << "Assign!" << endl;
        return value = new_value;
    }

    // get value ...
    operator T() const
    {
        return value;
    }
};

// struct Creature
// {
//     int strength{10};
//     int agility{10};

//     int getStrength() const { return strength; }
//     int getAgility() const { return agility; }  
//     int setStrength(int strength) { return this->strength = strength; }
//     int setAgility(int agility) { return this->agility = agility; }
// };

struct Creature
{
    Property<int> strength{10};
    Property<int> agility{5};
};

int main()
{
    Creature c;
    c.strength = 11;
    int x = c.agility;

    return 0;
}
