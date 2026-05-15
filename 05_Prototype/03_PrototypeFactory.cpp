#include <memory>
#include <string>

using namespace std;

struct Address{
    string street, city;
    int suite;

    Address(const string& street, const string& city, const int& suite) :
    street(street), city(city), suite(suite) {}  
};

struct Contact{
    string name;
    Address* address;

    Contact(const string& name, Address *address) :
    name(name), address(address) {}
};

// A option - not intuitive - not a prototype
// Contact main{"", new Address{"123 East", "Lnd", 0}};  

struct EmployeeFactory
{
private:
    static unique_ptr<Contact> new_employee
        (const string& name, const int suite, const Contact& prototype) 
    {
        // clone it
        auto result = make_unique<Contact>(prototype);
        // customize
        result->name = name;
        result->address->suite = suite;
        return result;
    }
public:
    static unique_ptr<Contact> new_main_office_employee
        (const string& name, const int suite)
    {
        static Contact p{ "", new Address {"123 East", "London", 0}};
        return new_employee(name, suite, p);
    }
};

int main(){
  // can you give a "template" for this? = prototype
  // Contact john{"John Doe", new Address{"123 East", "Lnd", 123}};  

  auto john = EmployeeFactory::new_main_office_employee("John", 123);

}
