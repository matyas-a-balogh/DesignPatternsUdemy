#include "../header.h"
#include <variant>
#include <type_traits>

// C-style variant
// struct House {
//     union {
//         string house_number;
//         int house_number;
//     };
//     enum class Type { name, number } type;
// };

struct AddressPrinter {
    void operator()(const string& house_name) const {
        cout << "A house called " << house_name << endl;
    }

    void operator()(const int house_number) const {
        cout << "House number " << house_number << endl;
    }
};

int main() {
    // modern C++ style
    variant<string, int> house; // only one of the can be given to it
    // house = 123;
    house = "Balogh Castle";

    // how can i print the assigned value for the house? visitor

    AddressPrinter printer;
    visit(printer, house); // std::visit()

    // with lambda
    visit([](auto& arg) {
        using T = decay_t<decltype(arg)>;

        if constexpr (is_same_v<T, string>) {
            cout << "A house called " << arg << endl;
        } else {
            cout << "House number " << arg << endl;
        }
    }, house);

    return 0;
}
