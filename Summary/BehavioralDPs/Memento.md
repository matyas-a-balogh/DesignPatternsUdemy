# Memento

## Real-life example

A game saves a checkpoint. You can return to that checkpoint without needing to know how the whole game state is stored.

## Explain it like I'm in kindergarten

Take a picture of your block tower before moving blocks. To undo, make the tower look like the picture again.

## The code that really matters

`19_Memento/02_UndoAndRedo.cpp`

```cpp
shared_ptr<Memento> deposit(int amount) {
  balance += amount;
  auto m = make_shared<Memento>(balance);
  changes.push_back(m);
  return m;
}
void restore(const shared_ptr<Memento>& m) { balance = m->balance; }
```

Each change records an opaque `Memento` containing the balance. Undo/redo restores earlier snapshots rather than redoing account logic.

## What to remember

- Save and restore an object’s state.
- Keep snapshot details private to the originator.
- Histories of mementos naturally support undo and redo.
