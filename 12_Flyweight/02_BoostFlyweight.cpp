#include "../header.h"
#include <boost/flyweight.hpp>


struct User
{
    boost::flyweight<string> first_name, last_name;

    User(const string& first_name, const string& last_name)
     : first_name(first_name), last_name(last_name) {}

};

int main()
{
    User user1{"Aklon", "Smith"};
    User user2{"Felon", "Smith"};

    cout << user1.first_name << endl;

    cout << boolalpha;
    cout << (&user1.first_name.get() == &user2.first_name.get()) << endl;
    cout << (&user1.last_name.get() == &user2.last_name.get()) << endl;
}
