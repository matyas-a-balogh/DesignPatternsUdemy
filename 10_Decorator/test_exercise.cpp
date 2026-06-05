#include "../header.h"


struct Flower
{
    virtual string str() = 0;
};

struct Rose : Flower
{
    string str() override {
        ostringstream oss;
        oss << "A rose";
        return oss.str();
    }
};

struct RedFlower : Flower
{
    Flower& flower;

    RedFlower(Flower& flower) : flower(flower) {};

    string str() override {
        ostringstream oss;
        oss << flower.str() << " that is red";
        return oss.str();
    }
};

struct BlueFlower : Flower
{
    Flower& flower;

    BlueFlower(Flower& flower) : flower(flower) {};

    string str() override {
        ostringstream oss;
        oss << flower.str() << " that is blue";
        return oss.str();
    }
};

int main()
{
    Rose rose;
    RedFlower red_rose{rose};
    BlueFlower blue_rose{rose};
    RedFlower red_red_rose{red_rose};
    BlueFlower blue_red_rose{red_rose};
    cout << rose.str() << endl;          // "A rose"
    cout << red_rose.str() << endl;      // "A rose that is red"
    cout << blue_rose.str() << endl;     // "A rose that is blue"
    cout << red_red_rose.str() << endl;  // "A rose that is red"
    cout << blue_red_rose.str() << endl; // "A rose that is red and blue"
}
