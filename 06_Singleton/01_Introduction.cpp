#include "../header.h"
#include <boost/lexical_cast.hpp>

using namespace boost;


class SingletonDatabase
{
    map<string, int> capitals;

    // has to be hidden
    // how to expose it?
    // it cant be instatiated, just with copy contsr.
    SingletonDatabase()
    {
        cout << "Initialize databse\n";
        ifstream ifs("capitals.txt");
        if (!ifs)
        {
            cerr << "Could not open capitals.txt\n";
            return;
        }

        string city, population;

        while(getline(ifs, city))
        {
            getline(ifs, population);
            capitals[city] = lexical_cast<int>(population);
        }
    }
public:
    // ensure nobody can replicate it
    SingletonDatabase(SingletonDatabase const&) = delete;
    void operator=(SingletonDatabase const&) = delete;

    // make it reachable
    static SingletonDatabase& get()
    {
        static SingletonDatabase db;
        return db;
    }

    int get_population(const string& name)
    {
        return capitals[name];
    }
};

int main()
{
    // cant use = 
    // auto db = SingletonDatabase::get();

    string city = "London";
    cout << city << " has population" << SingletonDatabase::get().get_population(city) << endl;
}
