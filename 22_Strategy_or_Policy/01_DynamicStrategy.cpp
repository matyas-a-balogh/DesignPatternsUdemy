#include "../header.h"

// Dynamic enables run-time selection of the strategy

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
    void start(ostream&) override {} // not used
    void end(ostream&) override {} // not used
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

struct TextProcessor {
private:
    ostringstream os;
    unique_ptr<ListStrategy> list_strategy;    
public:
    void set_output_format(OutputFormat format) {
        switch (format) {
            case OutputFormat::markdown:
                list_strategy = make_unique<MarkdownListStrategy>();
                break;
            case OutputFormat::html:
                list_strategy = make_unique<HtmlListStrategy>();
                break;
        }
    }

    void append_list(const vector<string>& items) {
        // this is where strategy is used, it is not known at compile time which strategy will be used, it is decided at run time
        list_strategy->start(os);
        for (const auto& item : items) {
            list_strategy->add_list_item(os, item);
        }
        list_strategy->end(os);
    }

    void clear() { os.str(""); os.clear(); }

    string str() const { return os.str(); }
};

int main() {
    vector<string> items{"foo", "bar", "baz"};

    TextProcessor tp;
    tp.set_output_format(OutputFormat::markdown);
    tp.append_list(items);
    cout << tp.str() << endl;

    tp.clear();
    tp.set_output_format(OutputFormat::html);
    tp.append_list(items);
    cout << tp.str() << endl;

    return 0;
}
