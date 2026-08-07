#include "../../header.h"
#include "observer.h"
#include "observable.h"

class Person : public Observable<Person> {
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

int main() {
    Person person{10};
    ConsolePersonObserver cpo;
    person.subscribe(cpo);
    
    person.set_age(15);
    person.set_age(17);
    
    return 0;
}
