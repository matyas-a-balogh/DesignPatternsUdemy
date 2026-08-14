#include "../header.h"

// Static enables compile-time selection of the strategy

enum class OutputFormat {
    markdown,
    html
};

// different formats
// * hasd
// * hasd
// <ul>
//   <li>hasd</li>
// </ul>

struct ListStrategy {
    virtual void start(ostream& os) = 0;
    virtual void end(ostream& os) = 0;
    virtual void add_list_item(ostream& os, const string& item) = 0;
};

struct MarkdownListStrategy : ListStrategy {
    void start(ostream&) override {}
    void end(ostream&) override {}
    void add_list_item(ostream& os, const string& item) override {
        os << " * " << item << endl;
    }
};

struct HtmlListStrategy : ListStrategy {
    void start(ostream& os) override {
        os << "<ul>" << endl;
    }
    void end(ostream& os) override {
        os << "</ul>" << endl;
    }
    void add_list_item(ostream& os, const string& item) override {
        os << "  <li>" << item << "</li>" << endl;
    }
};

template <typename LS> // this is the change
struct TextProcessor {
private:
    ostringstream os;
    LS list_strategy; // this is the change, now it is not a pointer, but a concrete type, so it is known at compile time
public:
    // and this: now it is not output format, bc it is alredy decided at compile time, so we don't need to set it at run time
    void append_list(const vector<string>& items) {
        list_strategy.start(os);
        for (const auto& item : items) {
            list_strategy.add_list_item(os, item);
        }
        list_strategy.end(os);
    }

    string str() const { return os.str(); }
};

int main() {
    vector<string> items{"foo", "bar", "baz"};

    TextProcessor<MarkdownListStrategy> tpm;
    tpm.append_list(items);
    cout << tpm.str() << endl;
    
    TextProcessor<HtmlListStrategy> tph;
    tph.append_list(items);
    cout << tph.str() << endl;

    return 0;
}
