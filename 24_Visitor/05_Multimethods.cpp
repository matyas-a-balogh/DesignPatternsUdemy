#include "../header.h"
#include <typeindex>

// Classic visitor:
// it is easy when there is 1 thing
// need_braces was to introduce a visitor that has 2 arguments
// now lets do that - multimethods
// 3 object, both of them meeting creates a different situation

struct GameObject;
void collide(GameObject& first, GameObject& second);

struct GameObject {
    virtual type_index type() const = 0;
    virtual void collide(GameObject& other) {
        ::collide(*this, other);
    }
};

// CRTP
// we pass info about type to baseclass
template <typename T> struct GameObjectImpl : GameObject {
    type_index type() const override {
        return typeid(T);
    }
};

struct Planet : GameObjectImpl<Planet> {};

struct Asteroid : GameObjectImpl<Asteroid> {};

struct Spaceship : GameObjectImpl<Spaceship> {};

void spaceship_planet() {cout << "spaceship lands on planet" << endl; }
void asteroid_planet() {cout << "asteroid burns planet" << endl; }
void asteroid_ship() {cout << "asteroid hits ship" << endl; }

// from the info (typeid) we define the outcomes
map<pair<type_index, type_index>, void(*)(void)> outcomes {
    {{typeid(Spaceship), typeid(Planet)}, spaceship_planet},
    {{typeid(Asteroid), typeid(Planet)}, asteroid_planet},
    {{typeid(Asteroid), typeid(Spaceship)}, asteroid_ship}
};

// this function runtime dependant on 2 arguments
// its a look-up table for a function we need to do
void collide(GameObject& first, GameObject& second) {
    auto it = outcomes.find({ first.type(), second.type() });
    if (it == outcomes.end()) {
        it = outcomes.find({ second.type(), first.type() });
        if (it == outcomes.end()) {
            cout << "objects pass each other" << endl;
            return;
        }
    }
    it -> second();
}

int main() {
    Asteroid asteroid;
    Planet planet;
    Spaceship spaceship;

    collide(planet, spaceship);
    collide(asteroid, spaceship);
    collide(asteroid, planet);
    collide(planet, planet);

    return 0;
}
