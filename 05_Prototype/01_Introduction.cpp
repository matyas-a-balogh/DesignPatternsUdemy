#include <iostream>

using namespace std;

struct Address{
    string street, city;
    int suite;

    //constructor
};

struct Contact{
    string name;
    // Address addr;
    Address* addr;

    // constructor
};

int main(){
  Contact john{"John Doe", Address{"123 East", "Lnd", 123}};  

  // have to replicate it again and again and just iterate 1 property
  // its better like this:
  Contact jane = john;
  jane.name = "Jane Smith";
  jane.addr.suite = 103;

  // what if a class changes - constructor has to be changed too
  // eg. Address becomes a pointer? everything changes - problematic
  Contact john{"John Doe", new Address{"123 East", "Lnd", 123}};  
  Contact jane = john;
  jane.name = "Jane Smith";
  jane.addr->suite = 103; // but it will change john's suit too, bc its a pointer
  // thats why we want to clone it, not only copy - prototype pattern needed
}
