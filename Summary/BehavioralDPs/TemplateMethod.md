# Template Method

## Real-life example

Every board game follows “start, take turns, find winner,” but chess supplies its own rules for those steps.

## Explain it like I'm in kindergarten

The grown-up says the game always starts, then children take turns, then someone wins. Each game decides what “take a turn” means.

## The code that really matters

`23_TemplateMethod/01_TemlateMethod.cpp`

```cpp
void Game::run() {
  start();
  while (!have_winner()) take_turn();
  cout << "Player " << get_winner() << " wins.";
}
```

`run()` fixes the algorithm’s order. `Chess` supplies the variable primitive operations such as `take_turn()` and `have_winner()`.

## What to remember

- Base class owns a stable algorithm skeleton.
- Subclasses fill in selected steps.
- Use it when order must stay fixed but steps vary.
