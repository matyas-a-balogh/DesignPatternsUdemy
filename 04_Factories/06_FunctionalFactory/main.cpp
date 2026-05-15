#include <iostream>
#include "DrinkFactory.h"

using namespace std;

int main() {
    DrinkWithVolumeFactory df;
    auto c = df.make_drink("coffee");
    
    return 0;
}
