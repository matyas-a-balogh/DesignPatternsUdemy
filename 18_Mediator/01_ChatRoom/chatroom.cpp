#include "../../header.h"
#include "person.h"
#include "chatroom.h"

void ChatRoom::broadcast(const string& origin, const string& message) const
{
    for (auto p : people) {
        if (p->name != origin) {
            p->receive(origin, message);
        }
    }
}

void ChatRoom::join(Person* p)
{
    string join_message = p->name + " joins the chat";
    broadcast("room", join_message);
    p->room = this;
    people.push_back(p);
}
