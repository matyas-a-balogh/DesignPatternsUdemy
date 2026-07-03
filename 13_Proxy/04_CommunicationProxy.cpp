#include "../header.h"
#include "stdafx.h"

// it is in the big folder

struct Pingable{
    virtual wstring ping(const wstring& message) = 0;
};

struct Pong : Pingable{
    // what if this comes back from a server?
    // the solution is in the folder conatined file
    wstring ping(const wstring& message) override {
        return message + L" pong";
    };
};

void tryit(Pingable& pp){
    wcout << pp.ping(L"ping") << endl;
}

int main()
{
    Pong pp; // finally all i have to do is add Remote(Pong pp;) here - this works around in the background, but wont be seen
    for (int i = 0; i < 10; i++){
        tryit(pp);
    }
    return 0;
}
