#include "../../header.h"
#include "observer.h"
#include "saferobservable.h"

class Person : public SaferObservable<Person> {
    int age;
public:
    Person(int age) : age(age) {}
    
    int get_age() const { return age; }

    void set_age(int age) { 
        if(this->age == age) return;

        auto old_can_vote = get_can_vote(); // store the old value of can_vote
        this->age = age; 
        notify(*this, "age");

        if (old_can_vote != get_can_vote()) { // check if can_vote has changed
            notify(*this, "can_vote"); // notify observers about the change in can_vote
        }
    }

    bool get_can_vote() const { return age >= 16; } // how to notify - hard to move in properties (property is not i c++, but now we clal it)

};

struct ConsolePersonObserver : public Observer<Person> {
private:
    void field_changed(Person& source, const string& field_name) override 
    {
        cout << "Person's " << field_name << " has changed to ";
        if (field_name == "age") { cout << source.get_age(); } // not scalable - notifying getters are tricky
        else if (field_name == "can_vote") { cout << boolalpha << source.get_can_vote(); }
        cout << endl;
    }
};

// what happens if i call unsubscribe inside notify? there are 2 locks.
struct TrafficAdministration : Observer<Person> {
private:
    void field_changed(Person& source, const string& field_name) override 
    {
        if (field_name == "age") {
            if (source.get_age() < 17) {
                cout << "TrafficAdministration: Person is not old enough to vote." << endl;
            }
            else {
                cout << "TrafficAdministration: Person is old enough to vote." << endl;
                source.unsubscribe(*this);
            }            
        }
    }
};

int main() {
    Person person{10};
    TrafficAdministration ta;
    person.subscribe(ta);
    
    person.set_age(15);
    person.set_age(16); 
    try {
        person.set_age(17);
    }
    catch (const std::exception& e) { // recursive mutex works too
        cout << "Exception: " << e.what() << endl;
    }
    
    return 0;
}
