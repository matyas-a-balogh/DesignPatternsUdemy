#include "person.h"

class Person::PersonImpl{
public:
    void greet(Person* p);
private:
    void secret() {}
};

// it cant be seen from outside - this is the implementation
void Person::PersonImpl::greet(Person* p){
    cout << "Hi, I'm " << p->name << endl;
}

Person::Person() : impl(new PersonImpl) {}

Person::~Person() { delete impl; }

void Person::greet() {}
