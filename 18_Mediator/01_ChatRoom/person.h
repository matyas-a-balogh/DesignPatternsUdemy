#pragma once
#include "../../header.h"

struct ChatRoom;

struct Person {
    string name;
    ChatRoom* room{nullptr}; // exclusively talking on this
    vector<string> chat_log;

    Person(const string& name);

    // doesnt have any pointer to others - the chatroom is the mediator

    void broadcast(const string& message) const; // "say"
    void pm(const string& who, const string& message) const; // private message
    void receive(const string& origin, const string& message); // origin can be person or group

    bool operator==(const Person& other) const;
    bool operator!=(const Person& other) const;
};
