# State

## Real-life example

A vending machine reacts differently to the same button depending on whether it has money and stock.

## Explain it like I'm in kindergarten

When the light is off, pressing ON changes it. When it is already on, pressing ON just says it is already on.

## The code that really matters

`21_State/01_ClassicStateMachine.cpp`

```cpp
void LightSwitch::on() { state->on(this); }
void OffState::on(LightSwitch* light_switch) {
  light_switch->set_state(new OnState());
}
```

`LightSwitch` delegates behavior to its current `State`. `OffState` handles `on` by swapping the current state, changing future behavior.

## What to remember

- Put state-specific behavior in state objects.
- The same call can act differently after a state transition.
- State objects may decide the next state.
