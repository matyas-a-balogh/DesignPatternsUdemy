#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>

#include <boost/lexical_cast.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace boost;

//make a fake Database
class Database
{
    public:
        virtual int get_population(const string& name) = 0;
};

class SingletonDatabase
{
    map<string, int> capitals;

    SingletonDatabase()
    {
        cout << "Initialize databse\n";
        ifstream ifs("utils/capitals.txt");
        if (!ifs)
        {
            cerr << "Could not open capitals.txt\n";
            return;
        }

        string city, population;

        while(getline(ifs, city))
        {
            getline(ifs, population);
            cout << "city=[" << city << "], population=[" << population << "]\n";
            capitals[city] = lexical_cast<int>(population);
        }
    }
public:
    SingletonDatabase(SingletonDatabase const&) = delete;
    void operator=(SingletonDatabase const&) = delete;

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

class DummyDatabase : public Database
{
    map<string, int> capitals;
public:
    DummyDatabase(){
        capitals["alpha"] = 1;
        capitals["beta"] = 2;
        capitals["gamma"] = 3;
    }
    int get_population(const string &name) override { return capitals.at(name); }
};

struct SingletonRecordFinder
{
    int total_pop(vector<string> names)
    {
        int result{0};
        for (auto& name : names)
            // we are bound to this database
            result += SingletonDatabase::get().get_population(name);
        return result;
    }
};

struct ConfigurableRecordFinder
{
    Database& db; // not singleton
    ConfigurableRecordFinder(Database &db) : db(db) {}

    int total_pop(vector<string> names)
    {
        int result{0};
        for (auto& name : names)
            result += db.get_population(name); // change this
        return result;
    }
};

// this is integrational test
TEST(RecordFinderTests, SingletonTotalPopTest)
{
    SingletonRecordFinder rf;
    vector<string> names{"London", "Budapest"};
    EXPECT_EQ(35051450+2000000, rf.total_pop(names));
}

// this is unittest
// implemented an interface and made a dummy class for it with given data
TEST(RecordFinderTests, DependantTotalPopTest)
{
    DummyDatabase db;
    ConfigurableRecordFinder rf{db};
    EXPECT_EQ(4, rf.total_pop(vector<string>{"alpha", "gamma"}));
}


int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
