#include "../../header.h"
#include "person.h"
#include "chatroom.h"

Person::Person(const string& name) : name(name) {}

void Person::broadcast(const string& message) const
{
    if (room) {
        room->broadcast(name, message);
    }
}

void Person::pm(const string& who, const string& message) const
{
    if (room) {
        room->message(name, who, message);
    }
}

void Person::receive(const string& origin, const string& message)
{
    string s = origin + ": " + message;
    cout << "[" << name << "'s chat session] " << s << endl;
    chat_log.emplace_back(s);
}
