#include "../../header.h"
#include "person.h"
#include "chatroom.h"


int main()
{
    ChatRoom room;

    Person john{"John"};
    Person jane{"Jane"};

    room.join(&john);
    room.join(&jane);

    john.broadcast("Hello, everyone!");
    jane.pm("John", "Hey John, how are you?");

    return 0;    
}
