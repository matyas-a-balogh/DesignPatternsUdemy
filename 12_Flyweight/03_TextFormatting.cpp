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

class BetterFormattedText
{
public:
    struct TextRange {
        int start, end;
        bool capitalized; // bold, italic

        bool covers(int position) const {
            return position >= start && position <= end;
        }
    };

    // TextRange is a flyweight
    // instead of a lot of bools, we have a few TextRanges
    TextRange& get_range(int start, int end) {
        formatting.emplace_back(TextRange{start, end});
        return *formatting.rbegin();
    }

    BetterFormattedText(const string &plain_text) : plain_text(plain_text) {}

    friend ostream &operator<<(ostream &os, const BetterFormattedText &obj) {
        string s;
        for (int i=0; i< obj.plain_text.length(); i++){
            char c = obj.plain_text[i];
            for (const auto& rng : obj.formatting){
                if (rng.covers(i) && rng.capitalized){
                    c = toupper(c);
                }
            }
            s += c;
        }
        return os << s;
    }
    
private:
    string plain_text;
    vector<TextRange> formatting;
};

int main() {
    FormattedText ft{"This is all caps in this scope."};
    ft.capitalize(10, 15);
    cout << ft << endl;

    BetterFormattedText bft{"This is all caps in this scope."};
    bft.get_range(10, 15).capitalized = true;
    cout << bft << endl;
}
