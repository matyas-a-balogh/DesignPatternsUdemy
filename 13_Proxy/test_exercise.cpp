#include "../header.h"

class Person
{
  friend class ResponsiblePerson;
  int age;

public:
  Person(int age) : age(age) {}

  int get_age() const { return age; }
  void set_age(int age) { this->age=age; }

  string drink() const { return "drinking"; }
  string drive() const { return "driving"; }
  string drink_and_drive() const { return "driving while drunk"; }
};

class ResponsiblePerson
{
    Person person;

public:
    ResponsiblePerson(const Person &person) : person(person) {}
    
    int get_age() const { return person.age; }
    void set_age(int age) { this->person.age=age; }
  
    string drink() const { 
        if(person.get_age() < 18) {
            return "too young";
        }
        return "drinking"; 
    }
    
    string drive() const { 
        if(person.get_age() < 16) {
            return "too young";
        }
        return "driving"; 
    }
    
    string drink_and_drive() const { return "dead"; }
};
