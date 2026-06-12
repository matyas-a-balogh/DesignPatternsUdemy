#include "../header.h"

class FormattedText
{
    string plain_text;
    bool *caps;
public:
    FormattedText(const string &plain_text) : plain_text(plain_text) {
        caps = new bool[plain_text.length()];
        memset(caps, 0, plain_text.length());
    }

    ~FormattedText() { delete caps; }

    void capitalize(int start, int end){
        for (int i = start; i <= end; i++){
            caps[i]= true;
        }
    }

    friend ostream &operator<<(ostream &os, const FormattedText &obj) {
        string s;
        for (int i = 0; i < obj.plain_text.length(); i++){
        char c = obj.plain_text[i];
            s += (obj.caps[i] ? toupper(c) : c);
        }
        return os << s;
    }
};

class BetterFormattedTeyt
{
    
}

int main() {
    FormattedText ft{"This is all caps in this scope."};
    ft.capitalize(10, 15);
    cout << ft << endl;
}
