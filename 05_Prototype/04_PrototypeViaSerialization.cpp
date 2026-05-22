#include "../header.h"

#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
using namespace boost;

struct Address{
    string street, city;
    int suite;

    Address(){}
    Address(const string& street, const string& city, const int& suite) :
    street(street), city(city), suite(suite) {}  

private:
    // this need it too, to have all param serialized
    friend class serialization::access;
    template <class archive> void serialize(archive& ar, const unsigned version)
    {
        ar & street;
        ar & city;
        ar & suite;
    }
};

// if you want to copy it, pointers or other not basic types gets really hars
// thats where serialization and deserial. comes in
// but there is no magic bullet to copy wout code
// we will save the pointer points to
struct Contact{
    string name;
    Address* address;

    Contact(){}
    Contact(const string& name, Address *address) :
    name(name), address(address) {}

private:
    friend class serialization::access;

    template <class archive> void serialize(archive& ar, const unsigned version)
    { // you can use it to save or clone it
        ar & name;
        ar & address; // booster knows its a pointer
    }
};

struct EmployeeFactory
{
private:
    static unique_ptr<Contact> new_employee
        (const string& name, const int suite, const Contact& prototype) 
    {
        auto result = make_unique<Contact>(prototype);
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
    auto clone = [](const Contact& c)
    {
        ostringstream oss;
        archive::text_oarchive oa(oss);
        oa << c;
        atring s == oss.str();
        cout << s << endl;

        //deserialize to result
        istringstream iss(s);
        archive::text_iarchive ia(iss);
        Contact result;
        ia >> result;
        return result;
    }

    // serial. need a default constructor
    auto john = EmlpoyeeFactory::new_main_office_employee("John", 123);
    auto jane = clone(*john);
    jane.name = "Jane";

    // advantages: we get serialization functionality and cloning functionality
    // also, its impossible to miss copy constructor
}
