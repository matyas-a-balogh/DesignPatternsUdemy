#include "../header.h"
#include <boost/signals2.hpp>
using namespace boost::signals2;

// mediator coupled with the observer pattern - the event broker is the mediator

struct EventData {
    virtual void print() const = 0;
};

struct Player;

struct PlayerScoredData : EventData {
    string player_name;
    int points_scored_so_far;

    PlayerScoredData(const string& name, int points) : player_name(name), points_scored_so_far(points) {};

    void print() const override {
        cout << "Player " << player_name << " scored " << points_scored_so_far << " points." << endl;
    }
};

// Mediator - player and coach has a reference to it, but they don't know about each other
struct Game {
    signal<void(EventData*)> events;
};

struct Player {
    string name;
    int points_scored{0};
    Game& game;

    Player(const string& name, Game& game) : name(name), game(game) {}

    void score() {
        points_scored++;
        PlayerScoredData ps(name, points_scored);
        game.events(&ps);
    }
};

// Observer - listens to the events of the game
struct Coach {
    Game& game;

    Coach(Game& game) : game(game) {
        game.events.connect([](EventData* ed) {
            if (auto ps = dynamic_cast<PlayerScoredData*>(ed)) {
                if (ps->points_scored_so_far < 3) {
                    cout << "Coach: well done, " << ps->player_name << ", you have scored " << ps->points_scored_so_far << " points." << endl;
                } else {
                    cout << "Coach: " << ps->player_name << ", you are out!" << endl;
                }
            }
        });
    }
};

int main()
{
    Game game;
    Player player{"Sam", game};
    Coach coach{game};

    player.score();
    player.score();
    player.score();
    
    return 0;
}
