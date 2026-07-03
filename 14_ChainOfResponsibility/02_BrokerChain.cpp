#include "../header.h"

#include <boost/signals2.hpp>
using namespace boost;
using namespace boost::signals2;

// event broker = chainofresp + observer (signals2) pattern + command query seperation

struct Query
{
    string creature_name; // what creature to modify
    enum Argument { attack, defense } argument; // choose what to modify
    int result; // the result of the modification

    Query(const string& creature_name, Argument argument, int result)
        : creature_name(creature_name), argument(argument), result(result) {}
};

struct Game // mediator
// query it and every one can subscribe to (modify) it
{
    signal<void(Query&)> queries; // you take a signal you give it a query you invoke it and every single subscriber can modify it
};

struct Creature
{
    Game& game;
    int attack, defense;
    string name;
public:
    Creature(Game& game, const string& name, int attack, int defense)
        : game(game), name(name), attack(attack), defense(defense) {}

    int get_attack() const
    {
        // here is where Query is performed
        // name is the creature we want to query, ...
        // attack is the default value, but every subscriber can modify it
        Query q{name, Query::Argument::attack, attack};
        // invoke the signal, which will call every subscriber with the query
        game.queries(q); // every subscriber can modify the query
        return q.result;
    }

    friend ostream& operator<<(ostream& os, const Creature& obj) {
        return os << "name: " << obj.name << ", attack: " << obj.get_attack();
    }
};

class CreatureModifier
{
    Game& game;
    Creature& creature;
public:
    CreatureModifier(Game& game, Creature& creature)
        : game(game), creature(creature) {}

    virtual ~CreatureModifier() = default;
};

class DoubleAttackModifier : public CreatureModifier
{
    connection conn; // only needed to make disconnect possible
public:
    DoubleAttackModifier(Game &game, Creature& creature)
        : CreatureModifier(game, creature)
    {
        // subscribe to the signal
        conn = game.queries.connect([&](Query& q) {
            // do we have to double?
            if (q.creature_name == creature.name && q.argument == Query::Argument::attack) {
                cout << "Doubling " << creature.name << "'s attack" << endl;
                q.result *= 2;
            }
        });
    }

    ~DoubleAttackModifier()
    {
        // unsubscribe from the signal
        conn.disconnect();
    }
};

int main()
{
    Game game;
    Creature goblin{game, "Strong Goblin", 2, 2};

    cout << goblin << endl;
    {
        DoubleAttackModifier dam{game, goblin};
        cout << goblin << endl;
    } // dam is destroyed, unsubscribed from the signal
    cout << goblin << endl;
    
    return 0;
}
