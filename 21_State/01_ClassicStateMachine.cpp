#include "../header.h"

// it is not used not, it is outdated

struct LightSwitch;

struct State {
    // this is the weird part - how switch is passed to the state, so that it can change the state of the switch
    virtual void on(LightSwitch*) {
        cout << "Light is already ON" << endl;
    }

    virtual void off(LightSwitch*) {
        cout << "Light is already OFF" << endl;
    }

};

struct OnState : State {
    OnState();

    void off(LightSwitch* light_switch) override;
};

struct OffState : State {
    OffState();

    void on(LightSwitch* light_switch) override;
};

class LightSwitch {
    State* state;
public:
    LightSwitch() : state(new OffState()) {}

    void set_state(State* new_state) {
        this->state = new_state;
    }

    void on() {
        state->on(this);
    };

    void off() {
        state->off(this);
    };
};

OnState::OnState() {
    cout << "Light turned ON" << endl;
}

void OnState::off(LightSwitch* light_switch) {
    cout << "Switching light OFF" << endl;
    light_switch->set_state(new OffState());
    delete this; // red flag, but it is a common pattern in old(?) state machines
}

OffState::OffState() {
    cout << "Light turned OFF" << endl;
}

void OffState::on(LightSwitch* light_switch) {
    cout << "Switching light ON" << endl;
    light_switch->set_state(new OnState());
    delete this;
}

int main() {
    LightSwitch light_switch;
    light_switch.on();
    light_switch.off();
    light_switch.off();

    return 0;
}
