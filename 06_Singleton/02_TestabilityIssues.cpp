#include "../header.h"

#include <boost/lexical_cast.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace boost;


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

// so this became an integrational test, not a unit test
TEST(RecordFinderTests, SingletonTotalPopTest)
{
    SingletonRecordFinder rf;
    vector<string> names{"London", "Budapest"};
    int tp = rf.total_pop(names);
    EXPECT_EQ(35051450+2000000, tp);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
