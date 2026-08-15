# Observer

## Real-life example

People who subscribe to a delivery tracker get notified whenever the parcel status changes.

## Explain it like I'm in kindergarten

Tell the teacher, “Please tell me when the cake is ready.” When it is ready, the teacher tells every child who asked.

## The code that really matters

`20_Observer/01_ObserverAndObservable/main.cpp`

```cpp
void set_age(int age) {
  if (this->age == age) return;
  this->age = age;
  notify(*this, "age");
}
person.subscribe(cpo);
```

`Person` changes its state then notifies subscribers. The observer is attached independently, so the subject does not depend on the concrete observer.

## What to remember

- Notify interested subscribers when state changes.
- Subject owns notification; observers react.
- Always consider unsubscribe and lifetime/thread-safety rules.
