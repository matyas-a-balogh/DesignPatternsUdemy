#pragma once
#include "../../header.h"
#include "person.h"

struct ChatRoom {
    vector<Person*> people;

    void broadcast(const string& origin, const string& message) const;

    void join(Person* p);

    void message(const string& origin, const string& who, const string& message) {
        auto target = find_if(people.begin(), people.end(), [&](const Person* p) { return p->name == who; });
        if (target != end(people)) { (*target)->receive(origin, message); }
    };
};
