#include <string>
#include <iostream>
using namespace std;

struct Person
{
  int id;
  string name;

  friend ostream &operator<<(ostream  &os, const Person &p) {
      os << "Name: " << p.name << ", ID: " << p.id;
      return os;
  }
};

class PersonFactory
{
public:
  int id = 0;

  Person create_person(const string& name)
  {
      Person p{id, name};
      id++;
      return p;
  }
};

int main() {

    auto pf = PersonFactory();
    auto p0 = pf.create_person("John");
    auto p1 = pf.create_person("Jake");
    auto p2 = pf.create_person("Jack"); 

    cout << p0 << endl;
    cout << p1 << endl;
    cout << p2 << endl;

    
    return 0;
}
