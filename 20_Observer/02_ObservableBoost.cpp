#include "../header.h"

#include <boost/signals2.hpp>
using namespace boost::signals2;

template <typename T> struct Observable {
    signal<void(T&, const string&)> field_changed;
};

class Person : public Observable<Person> {
    int age;
public:
    Person(int age) : age(age) {}
    int get_age() const { return age; }
    void set_age(int age) {
        if (this->age == age) return;
        this->age = age;
        field_changed(*this, "age");
    }
};

int main() {
    Person person{10};
    auto conn = person.field_changed.connect(
        [](Person& source, const string& field_name) {
            cout << "Person's " << field_name << " has changed to " << source.get_age() << endl;
        }
    );

    person.set_age(11);
    person.set_age(12);

    conn.disconnect();
    person.set_age(13);
    
    return 0;
}
