#include "../header.h"

// old school pointer chain
// in a card game, we have a creature with attack and defense
// and there are boost cards that can change the attack and defense points

// here we actually built a single linked list of modifiers, and we can apply them to the creature
// we can use a list instead

struct Creature
{
    string name;
    int attack, defense;

    Creature(const string& name, int attack, int defense)
        : name(name), attack(attack), defense(defense) {}

    friend ostream& operator<<(ostream& os, const Creature& obj) {
        return os << "name: " << obj.name << ", attack: " << obj.attack << ", defense: " << obj.defense;
    }
};

class CreatureModifier
{
    CreatureModifier* next{nullptr};
protected:
    Creature& creature;
public:
    // who are we effecting
    CreatureModifier(Creature& creature) : creature(creature) {}

    // how to add a new modifier to the chain
    void add(CreatureModifier* cm) {
        // add element to the end of the chain
        if (next) next->add(cm);
        else next = cm;
    }

    // how do you apply the modifier to the creature
    // virtual - so that we can override it in the derived classes
    virtual void handle() {
        if (next) next->handle();
    }
};

// add modifiers
class DoubleAttackModifier : public CreatureModifier
{
public:
    DoubleAttackModifier(Creature& creature) : CreatureModifier(creature) {}
    
    void handle() override {
        cout << "Doubling " << creature.name << "'s attack" << endl;
        creature.attack *= 2;
        CreatureModifier::handle(); // call the next modifier in the chain - this ables to walk in the chain
    }
};

// modifier 2.
class IncreaseDefenseModifier : public CreatureModifier
{
public:
    IncreaseDefenseModifier(Creature& creature) : CreatureModifier(creature) {}

    void handle() override {
        if (creature.attack <= 2) {
            cout << "Increasing " << creature.name << "'s defense" << endl;
            creature.defense += 3;
        }
        CreatureModifier::handle(); // call the next modifier in the chain
    }
};

// "witch" modifier - stops the chain
class NoBonusesModifier : public CreatureModifier
{
public:
    NoBonusesModifier(Creature& creature) : CreatureModifier(creature) {}

    void handle() override {
        cout << "No bonuses for " << creature.name << endl;
        // do not call the next modifier in the chain
    }
};

int main()
{
    Creature goblin{"Goblin", 2, 2};
    CreatureModifier root{goblin}; // start of the chain, root is a dummy modifier that does nothing, but it is the head of the chain
    DoubleAttackModifier r1{goblin};
    DoubleAttackModifier r1_2{goblin};
    IncreaseDefenseModifier r2{goblin};

    NoBonusesModifier curse{goblin}; // this will stop the chain, so the next modifier will not be applied

    root.add(&r1);
    root.add(&curse);
    root.add(&r1_2);
    root.add(&r2);

    root.handle(); // start the chain, it will call the handle method of the first modifier, which will call the next one and so on
    
    cout << goblin << endl;

    return 0;
}
