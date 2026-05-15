#include <iostream>
#include <string>
#include <vector>
using namespace std;

class CodeBuilder
{
  string class_name;

  struct Field
  {
    string name;
    string type;
  };

  vector<Field> fields;

public:
  CodeBuilder(const string& class_name) : class_name(class_name) {}

  CodeBuilder& add_field(const string& name, const string& type)
  {
    fields.push_back({name, type});
    return *this;
  }

  friend ostream& operator<<(ostream& os, const CodeBuilder& obj)
  {
    os << "class " << obj.class_name << "\n";
    os << "{\n";

    for (const auto& field : obj.fields)
    {
      os << "  " << field.type << " " << field.name << ";\n";
    }

    os << "};";

    return os;
  }
};

int main()
{
  auto cb = CodeBuilder{"Person"}.add_field("name", "string").add_field("age", "int");
  cout << cb;
  return 0;
}
