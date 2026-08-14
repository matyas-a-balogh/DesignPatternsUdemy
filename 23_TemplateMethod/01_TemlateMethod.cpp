#include "../header.h"

class Game {
protected:
    int number_of_players;

    int current_player{0};
    virtual void start() = 0;
    virtual void take_turn() = 0;
    virtual bool have_winner() = 0;
    virtual int get_winner() = 0;

public:
    Game(int number_of_players) : number_of_players(number_of_players) {}

    // this is the template method, it defines the skeleton of the algorithm,
    // and calls the primitive operations that are defined in the subclasses
    void run() {
        start();
        while (!have_winner()) {
            take_turn();
        }
        cout << "Player " << get_winner() << " wins." << endl;
    }
};

class Chess : public Game {
protected:
    void start() override {
        cout << "Starting a game of chess with " << number_of_players << " players." << endl;
    }

    void take_turn() override {
        cout << "Turn " << turn << " by player " << current_player << endl;
        ++turn;
        current_player = (current_player + 1) % number_of_players;
    }

    bool have_winner() override {
        return turn == max_turns;
    }

    int get_winner() override {
        return current_player;
    }
private:
    int turn{0}, max_turns{10};
public:
    Chess() : Game(2) {}
};

int main() {
    Chess chess;
    chess.run();    

    return 0;
}
