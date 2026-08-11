#include "../header.h"

#include <boost/msm/front/state_machine_def.hpp> // the front-end
#include <boost/msm/front/functor_row.hpp> // for transition actions
#include <boost/msm/back/state_machine.hpp> // the back-end

namespace msm = boost::msm;
namespace mpl = boost::mpl;
using namespace msm::front;

const char* state_names[] = { // can be vector<string> as well, but this is simpler
    "OffHook",
    "Connecting",
    "Connected",
    "OnHold",
    "PhoneDestroyed"
};

struct CallDialed {};
struct HungUp {};
struct CallConnected {};
struct PlacedOnHold {};
struct TakenOffHold {};
struct LeftMessage {};
struct PhoneThrownIntoWall {};

// state machine front-end: define the FSM structure
struct PhoneCallStateMachine : state_machine_def<PhoneCallStateMachine> {
    struct OffHook : state<> {};
    struct Connecting : state<> {
        template <class Event, class FSM>
        void on_entry(Event const&, FSM&) { cout << "We are connecting..." << endl; }
    };
    struct Connected : state<> {};
    struct OnHold : state<> {};
    struct PhoneDestroyed : state<> {};

    // transition action
    struct PhoneBeingDestroyed : state<> {
        template <class EVT, class FSM, class SourceState, class TargetState>
        void operator()(EVT const&, FSM&, SourceState&, TargetState&) { 
            cout << "Phone is being destroyed..." << endl; 
        }
    };

    // transition guard
    // this is a functor that will be called before the transition, if it returns true, the transition will happen, if it returns false, the transition will not happen
    // guards the transition from OnHold to PhoneDestroyed
    struct CanDestroyPhone {
        template <class EVT, class FSM, class SourceState, class TargetState>
        bool operator()(EVT const&, FSM&, SourceState&, TargetState&) {
            cout << "Checking if phone can be destroyed..." << endl;
            return true; // for simplicity, we will always allow it
        }
    };

    // lot of customization is possible
    struct transition_table : mpl::vector<
        // Start, Event, Next, Action, Guard
        Row<OffHook, CallDialed, Connecting>,
        Row<Connecting, HungUp, OffHook>,
        Row<Connecting, CallConnected, Connected>,
        Row<Connected, LeftMessage, OffHook>,
        Row<Connected, HungUp, OffHook>,
        Row<Connected, PlacedOnHold, OnHold>,
        Row<OnHold, PhoneThrownIntoWall, PhoneDestroyed, 
            PhoneBeingDestroyed, CanDestroyPhone>
    > {};

    typedef OffHook initial_state; // initial state of the FSM

    template <class FSM, class Event>
    void no_transition(Event const& e, FSM&, int state) {
        cout << "No transition from state " << state << " on event " << typeid(e).name() << endl;
    }
};

int main() {
    msm::back::state_machine<PhoneCallStateMachine> phone;
    phone.start(); // start the state machine, will enter OffHook state

    auto info = [&]() {
        auto i = phone.current_state()[0];
        cout << "Current state: " << state_names[i] << endl;
    };

    info();
    phone.process_event(CallDialed());
    info();
    phone.process_event(CallConnected());
    info();
    phone.process_event(PlacedOnHold());
    info();
    phone.process_event(PhoneThrownIntoWall());
    info();

    phone.process_event(HungUp()); // this will not work, because we are in PhoneDestroyed state, and there is no transition from PhoneDestroyed on HungUp event

    return 0;
}
