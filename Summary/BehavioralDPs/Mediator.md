# Mediator

## Real-life example

Air-traffic control coordinates pilots so each plane talks to the tower instead of directly to every other plane.

## Explain it like I'm in kindergarten

Children tell the teacher their message. The teacher gives it to the right child, so everyone does not shout at everyone else.

## The code that really matters

`18_Mediator/01_ChatRoom/person.cpp`

```cpp
void Person::broadcast(const string& message) const {
  if (room) room->broadcast(name, message);
}
```

`18_Mediator/01_ChatRoom/chatroom.cpp`

```cpp
void ChatRoom::broadcast(const string& origin, const string& message) const {
  for (auto p : people) if (p->name != origin) p->receive(origin, message);
}
```

`Person` sends through `ChatRoom`; the room knows the participants and routes the message. Participants do not need direct references to one another.

## What to remember

- Centralize coordination among collaborating objects.
- Participants communicate with the mediator, not every peer.
- This reduces many-to-many coupling.
