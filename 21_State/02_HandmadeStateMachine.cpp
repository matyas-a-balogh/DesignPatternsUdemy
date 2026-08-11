#include "../header.h"

enum class State {
    off_hook,
    connecting,
    connected,
    on_hold,
    on_the_hook
};

inline ostream& operator<<(ostream& os, const State& state) {
    switch (state) {
        case State::off_hook: return os << "off_hook";
        case State::connecting: return os << "connecting";
        case State::connected: return os << "connected";
        case State::on_hold: return os << "on_hold";
        case State::on_the_hook: return os << "on_the_hook";
    }
    return os;
}

enum class Trigger {
    call_dialed,
    hung_up,
    call_connected,
    placed_on_hold,
    taken_off_hold,
    left_message,
    stop_using_phone
};

inline ostream& operator<<(ostream& os, const Trigger& trigger) {
    switch (trigger) {
        case Trigger::call_dialed: return os << "call_dialed";
        case Trigger::hung_up: return os << "hung_up";
        case Trigger::call_connected: return os << "call_connected";
        case Trigger::placed_on_hold: return os << "placed_on_hold";
        case Trigger::taken_off_hold: return os << "taken_off_hold";
        case Trigger::left_message: return os << "left_message";
        case Trigger::stop_using_phone: return os << "stop_using_phone";
    }
    return os;
}

int main() {
    // Modelling state machine
    map<State, vector<pair<Trigger, State>>> rules{
        {State::off_hook, {{Trigger::call_dialed, State::connecting}, {Trigger::stop_using_phone, State::on_the_hook}}}, // means that if we are in off_hook state and call_dialed trigger is fired, we will go to connecting state
        {State::connecting, {{Trigger::hung_up, State::off_hook}, {Trigger::call_connected, State::connected}}},
        {State::connected, {{Trigger::left_message, State::off_hook}, {Trigger::hung_up, State::off_hook}, {Trigger::placed_on_hold, State::on_hold}}},
        {State::on_hold, {{Trigger::taken_off_hold, State::connected}, {Trigger::hung_up, State::off_hook}}}
    };

    State current_state{State::off_hook}; // init state
    State exit_state{State::on_the_hook}; // exit state

    // Running it
    // we are in a loop, we will print the current state and the possible triggers, then we will read the input and change the state accordingly
    while(true) {
        cout << "The phone is currently " << current_state << endl;
        cout << "Select a trigger: " << endl;

        // print triggers
        for (int i = 0; i < rules[current_state].size(); ++i) {
            auto [trigger, _] = rules[current_state][i];
            cout << i << ". " << trigger << endl;
        }

        // get input from user
        int input;
        cin >> input;

        if (input < 0 || input >= rules[current_state].size()) {
            cout << "Invalid input" << endl;
            continue;
        }

        auto [trigger, next_state] = rules[current_state][input];
        current_state = next_state;

        if (current_state == exit_state) {
            cout << "Exiting..." << endl;
            break;
        }
    }
    
    return 0;
}
