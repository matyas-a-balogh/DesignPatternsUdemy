#include <iostream>
#include "HotDrinkFactory.h"
#include "DrinkFactory.h"

using namespace std;

unique_ptr<HotDrink> make_drink(string type)
{
    unique_ptr<HotDrink> drink;
    // wout abstract factory there would be an if needed
    // if (type == "tee"){
    //     drink = make_unique<Tee>();
    //     drink->prepare(200);
    // }
    // else{
    //     drink = make_unique<Coffee>();
    //     drink->prepare(100);
    // }
    // return drink;
}   

int main() {
    // auto d = make_drink("tee");
    DrinkFactory df;
    auto c = df.make_drink("coffee");
    
    return 0;
}
