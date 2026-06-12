#include "../header.h"


struct Flower{
    virtual string str() = 0;
};

struct Rose : Flower{
    string str() override {
        ostringstream oss;
        oss << "A rose";
        return oss.str();
    }
};

struct RedFlower : Flower{
    Flower& flower;
    string color = "red";

    RedFlower(Flower& flower) : flower(flower) {};

    string str() override {
        ostringstream oss;
        oss << flower.str() << " that is " << color;
        return oss.str();
    }
};

struct BlueFlower : Flower{
    Flower& flower;
    string color = "blue";

    BlueFlower(Flower& flower) : flower(flower) {};

    string str() override {
        ostringstream oss;
        oss << flower.str() << " that is " << color;
        return oss.str();
    }
};

int main()
{
    Rose rose;
    RedFlower red_rose{rose};
    BlueFlower blue_rose{rose};
    RedFlower red_red_rose{red_rose};
    BlueFlower blue_blue_rose{blue_rose};
    RedFlower red_blue_rose{blue_rose};
    BlueFlower blue_red_rose{red_rose};
    RedFlower blue_red_blue_rose{red_blue_rose};
    BlueFlower red_blue_red_rose{blue_red_rose};
    cout << rose.str() << endl;               // "A rose"
    cout << red_rose.str() << endl;           // "A rose that is red"
    cout << blue_rose.str() << endl;          // "A rose that is blue"
    cout << red_red_rose.str() << endl;       // "A rose that is red"
    cout << blue_blue_rose.str() << endl;     // "A rose that is blue"
    cout << blue_red_rose.str() << endl;      // "A rose that is red and blue"
    cout << red_blue_rose.str() << endl;      // "A rose that is blue and red"
    cout << red_blue_red_rose.str() << endl;  // "A rose that is red and blue"
    cout << blue_red_blue_rose.str() << endl; // "A rose that is blue and red"
}
