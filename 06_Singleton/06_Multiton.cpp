#include <map>
#include <iostream>
#include <memory>

using namespace std;

// its not really linked to singleton
// it sets up key-value store
// optionally restrict the number of element in that store
enum class Importance
{
    primary,
    secondary,
    tertiary
};

// singleton for all element
template <typename T, typename Key = std::string>
class Multiton
{
public:
    // it meant to be called by get
    // never instantiated
    static shared_ptr<T> get(const Key& key)
    {
        if(const auto it = instances.find(key);
            it != instances.end())
        {
            return it->second;
        }

        auto instance = make_shared<T>();
        instances[key] = instance;
        return instance;
    }
protected:
    Multiton() = default;
    virtual ~Multiton() = default;
private:
    static map<Key, shared_ptr<T>> instances;
};

template <typename T, typename Key>
map<Key, shared_ptr<T>> Multiton<T, Key>::instances;


// you can have 3 of them (we declared it, but all singleton)
class Printer
{
public:
    Printer()
    {
        ++Printer::totalInstanceCount;
        cout << "A totally created: " << Printer::totalInstanceCount << endl;
    }
private:
    // just to show we dont construct more
    static int totalInstanceCount;
};

int main()
{
    typedef Multiton<Printer, Importance> mt;

    auto main = mt::get(Importance::primary);
    auto aux = mt::get(Importance::secondary);
    auto aux2 = mt::get(Importance::tertiary);
}
