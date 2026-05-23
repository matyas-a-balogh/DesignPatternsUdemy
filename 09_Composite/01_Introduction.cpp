#include "../header.h"

// Geometry shapes example
// Eg.: PowerPoint can group objects and use them as 1 object

struct GraphicObject{
    virtual void draw() = 0;
};

// both Circle and Group is GraphicObject
// That means, i can call draw() on a single circle or on a group

// leaf
struct Circle : GraphicObject
{
    void draw() override {
        cout<<"Circle"<<endl;}
};

// composite
struct Group : GraphicObject
{
    string name;
    // Group can conotain other GraphicObjects
    vector<GraphicObject*> objects;

    Group(const string& name) : name(name) {}
    
    void draw() override 
    {
        cout<<"Group " << name.c_str() << " contains: " << endl;
        // Group doesnt care if it s a Circle or another Group
        // It draws it
        for (auto&& o : objects) o->draw();
    }
};

int main()
{
    // Composite: a complex object is built from smaller objects using the same interface.
    Group root("root");
    Circle c1, c2;
    root.objects.push_back(&c1);

    Group subgroup("sub");
    root.objects.push_back(&subgroup); // order can be changed here
    subgroup.objects.push_back(&c2);

    root.draw();

    /*
    root
    ├── c1
    └── sub
        └── c2
    */
}
