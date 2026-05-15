#include <iostream>

using namespace std;

struct Address{
    string street, city;
    int suite;

    Address(const string& street, const string& city, const int& suite) :
    street(street), city(city), suite(suite) {}

    // make it more robust - copy-constructor
    Address(const Address& other) :
    street(other.street), city(other.city), suite(other.suite) {}    
};

struct Contact{
    string name;
    Address* address;

    Contact(const string& name, Address *address) :
    name(name), address(address) {}

    // create a copy-contsructor
    // Contact(const Contact& other) : name {other.name}, 
    //                                 address {new Address {other.address->street, 
    //                                     other.address->city, other.address->suite}} {}

    // more robust copy-constructor w Address copy-constructor
    Contact(const Contact& other) : name {other.name}, 
                                    address { new Address{*other.address}} {}

};

int main(){

  Contact john{"John Doe", new Address{"123 East", "Lnd", 123}};  

  // a deep-copy is wanted 
  // Contact jane = john; // shallow-copy
  Contact jane{john}; // deep-copy w copy-constructor
  jane.name = "Jane Smith";
  jane.address->suite = 103; 
}
