#include "../header.h"

// it is crazy to sum it, avg it or anything that requires all instance
//class Creature
//{
//  int strength, agility, intelligence;
//  // new property
//  int charisma;
//public:
//  int get_strength() const
//  {
//    return strength;
//  }
//
//  void set_strength(int strength)
//  {
//    Creature::strength=strength;
//  }
//
//  int get_agility() const
//  {
//    return agility;
//  }
//
//  void set_agility(int agility)
//  {
//    Creature::agility=agility;
//  }
//
//  int get_intelligence() const
//  {
//    return intelligence;
//  }
//
//  void set_intelligence(int intelligence)
//  {
//    Creature::intelligence=intelligence;
//  }
//
//  // sum, average, max.
//
//  double sum() const {
//    return strength + agility + intelligence;
//  }
//
//  double average() const {
//    return sum() / 3.0;
//  }
//
//  int max() const {
//    return ::max(::max(strength, agility), intelligence);
//  }
//};


// have aggregate storage for fields
// fields doesnt have to be stored seperately
// this is array-backed properties
class Creature
{
    // count: i can add abilites and i will know how many i have, bc the count starts with 0
    enum Abilities { str, agl, intl, count }; 
    // store abilities in array - lenght is count
    array<int, count> abilities; 
public:
    int get_strength() const { return abilities[str]; }
    void set_strength(int value) { abilities[str] = value; }
      
    int get_agility() const { return abilities[agl]; }
    void set_agility(int value) { abilities[agl] = value; }
      
    int get_intelligence() const { return abilities[intl]; }
    void set_intelligence(int value) { abilities[intl] = value; }

    // array algorithms are easy
    int sum() const {
        return accumulate(abilities.begin(), abilities.end(), 0);
    }
      
    double average() const {
        return sum() / (double)count;
    }
      
    int max() const {
        return *max_element(abilities.begin(), abilities.end());
    }
};

int main()
{
    Creature orc;
    orc.set_strength(16);
    orc.set_agility(11);
    orc.set_intelligence(9);
  
    cout << "The orc has an average stat of "
         << orc.average()
         << " and a maximum stat of "
         << orc.max() << "\n";
         
    return 0;
}
