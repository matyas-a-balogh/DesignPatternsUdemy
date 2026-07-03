#include "../header.h"

struct Creature;

struct Game {
  vector<Creature*> creatures;
};

struct StatQuery {
  enum Statistic { attack, defense } statistic;
  int result;
};

struct Creature 
{
protected:
  Game& game;
  int base_attack, base_defense;

public:
  Creature(Game &game, int base_attack, int base_defense) : game(game), base_attack(base_attack),
                                                            base_defense(base_defense) {}
  virtual int get_attack() = 0;
  virtual int get_defense() = 0;
  virtual bool is_king() const { return false; }
};

class Goblin : public Creature 
{
public:
  Goblin(Game &game, int base_attack, int base_defense) : Creature(game, base_attack, base_defense) {}

  Goblin(Game &game) : Creature(game, 1, 1) {}

  int get_attack() override {
      StatQuery q{StatQuery::attack, base_attack};
      for (auto creature : game.creatures) {
        if (creature != this && creature->is_king()) {
          q.result += 1;
        }
      }
      return q.result;
  }

  int get_defense() override {
    int goblin_count = 0;
    for (auto creature : game.creatures) {
      // dynamic_cast returns nullptr if the cast fails, so we can use it to check if the creature is a Goblin
      if (creature != this && dynamic_cast<Goblin*>(creature)) goblin_count++;
    }
    StatQuery q{StatQuery::defense, base_defense + goblin_count};
    return q.result;
  }
};

class GoblinKing : public Goblin
{
public:
  GoblinKing(Game &game) : Goblin(game, 3, 3) {}

  bool is_king() const override { return true; }
};

int main() {
  Game game;

  Goblin g1(game);
  Goblin g2(game);
  Goblin g3(game);
  GoblinKing king(game);

  game.creatures.push_back(&g1);
  game.creatures.push_back(&g2);
  game.creatures.push_back(&g3);
  game.creatures.push_back(&king);

  cout << "g1: " << g1.get_attack() << "/" << g1.get_defense() << '\n';
  cout << "g2: " << g2.get_attack() << "/" << g2.get_defense() << '\n';
  cout << "g3: " << g3.get_attack() << "/" << g3.get_defense() << '\n';
  cout << "king: " << king.get_attack() << "/" << king.get_defense() << '\n';

  return 0;
}
