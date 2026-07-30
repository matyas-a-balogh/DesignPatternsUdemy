#include "../../header.h"
#include "observer.h"
#include "observable.h"

#include <boost/signals2.hpp>
using namespace boost::signals2;

class Person : public Observable<Person> {
    int age;
public:
    Person(int age) : age(age) {}
    
    int get_age() const { return age; }

    void set_age(int age) { 
        if(this->age == age) return;
        this->age = age; 
        notify(*this, "age");
    }
};

struct ConsolePersonObserver : public Observer<Person> {
private:
    void field_changed(Person& source, const string& field_name) override 
    {
        cout << "Person's " << field_name << " has changed to " << source.get_age() << endl;
    }
};

template <typename T> struct Observable2 {
    signal<void(T&, const string&)> field_changed;
};

class Person2 : public Observable2<Person2> {
    int age;
public:
    Person2(int age) : age(age) {}
    int get_age() const { return age; }
    void set_age(int age) {
        if (this->age == age) return;
        this->age = age;
        field_changed(*this, "age");
    }
};

int main() {
    Person2 person{10};
    auto conn = person.field_changed.connect(
        [](Person2& source, const string& field_name) {
            cout << "Person's " << field_name << " has changed to " << source.get_age() << endl;
        }
    );

    person.set_age(11);
    person.set_age(12);

    conn.disconnect();
    person.set_age(13);
    
    return 0;
}
