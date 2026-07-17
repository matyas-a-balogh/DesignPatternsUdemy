#include "../header.h"

int main()
{
    vector<string> names{"Matyas", "John", "Jane", "James"};
    vector<string>::iterator it = names.begin(); // begin(names)
    
    cout << "first name is " << *it << endl;

    ++it;
    it->append(" Doe"); // it->append(" Doe");
    cout << "second name is " << *it << endl;

    // 1 2 3 4 
    //         ^ end
    while (++it != names.end()) {
        cout << "next name is " << *it << endl;
    }

    // backwards iteration
    //     1 2 3
    //   ^     ^ rbegin
    for (auto ri = rbegin(names); ri != rend(names); ++ri) { // vector<string>::iterator can be auto
        cout << *ri;
        if (ri + 1 != rend(names)) {
            cout << ", ";
        }
    }

    vector<string>::const_reverse_iterator jack = crbegin(names);
    // *jack += string(" Smith"); // doesnt work, bc it is const

    // Most modern format
    // need begin/end - you get *it - assign it to variable (auto) - so it is wrapped
    for (auto&& name : names) {
        cout << "name = " << name << endl;
    }

    return 0;
}
