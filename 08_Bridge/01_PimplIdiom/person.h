#include "../../header.h"

class Person{
public:
    string name;

    class PersonImpl;
    PersonImpl* impl;
    
    Person();
    ~Person();

    // it is not implemented here, but it is seen
    void greet();
// private:
    // this is seen to, but it shouldnt - pimpl solves it
    // void secret() {}
};
