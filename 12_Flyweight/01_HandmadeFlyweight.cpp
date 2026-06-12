#include "../header.h"
#include <boost/bimap.hpp>

// massive multiplayer online game with same names

// struct User
// {
//     string first_name, last_name;
// };

// int main()
// {
//     // John now takes more bits
//     User user1{"John", "Doe"};
//     User user2{"John", "Mark"};
// }

typedef uint32_t key;

struct User {
protected:
    key first_name, last_name;
    static boost::bimap<key, string> names;
    static key seed;

    static key add(const string& s)
    {
        auto it = names.right.find(s);
        if (it == names.right.end()){
            key id = ++seed;
            names.insert({seed, s});
            return id;
        }
        return it->second;
    }

public:
    User(const string& first_name, const string& last_name)
     : first_name{add(first_name)}, last_name{add(last_name)} {}

    const string& get_first_name() const {
        return names.left.find(first_name)->second;
    }
    
    const string& get_last_name() const {
        return names.left.find(last_name)->second;
    }

    friend ostream &operator<<(ostream &os, const User &user) {
        os << user.get_first_name() << " (" << user.first_name << ") "
           << user.get_last_name()  << " (" << user.last_name  << ") ";
        return os;
    }
};

key User::seed{0};
// bimap can search from two-sides
// find key, add string and vica-versa
// it is a static data member, there is 1 bimap to the entire project
// this is a storage allocation, created before main, lives until the end
boost::bimap<key, string> User::names{};

int main()
{
    User user1{"Aklon", "Smith"};
    User user2{"Felon", "Smith"};

    cout << user1 << endl << user2 << endl;
}
