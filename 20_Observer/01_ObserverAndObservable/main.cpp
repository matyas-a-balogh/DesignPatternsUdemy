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

int main() {
    Person person{10};
    ConsolePersonObserver cpo;
    person.subscribe(cpo);
    
    person.set_age(11);
    person.set_age(12);

    person.unsubscribe(cpo);
    person.set_age(13);
    
    return 0;
}
