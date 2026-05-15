#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct HtmlElement{
    string name, text;
    vector<HtmlElement> elements;
    const size_t indent_size = 2;
    
    HtmlElement(){};
    HtmlElement(const string& name, const  string& text) : name(name), text(text) {}
    
    // makes indentation in the correct way - official html stuff and naming
    // this is printing actually
    string str(int indent = 0) const {
        ostringstream oss;
        string i(indent_size*indent, ' ');
        oss << i << "<" << name << ">" << endl;
        if (text.size() > 0)
          oss << string(indent_size*(indent + 1), ' ') << text << endl;
    
        for (const auto& e : elements)
          oss << e.str(indent + 1);
    
        oss << i << "</" << name << ">" << endl;
        return oss.str();
    }
};

// How do I build these element together?
struct HtmlBuilder{
    HtmlElement root;
    
    HtmlBuilder(string root_name){ root.name = root_name; }
    
    // Make utility function
    HtmlBuilder& add_child(string child_name, string child_text){
        HtmlElement e{child_name, child_text};
        root.elements.emplace_back(e);
        return *this; // stays the same object, it can be chained
    }
    
    string str() const { return root.str(); }
};

int main() {
   // Now we can build differently
   HtmlBuilder builder{"ul"};
   
   // Fluent builder can add one after another - changes the return type of add_child
   builder.add_child("li", "hello").add_child("li", "world");
   cout << builder.str() << endl;

   return 0;
}
