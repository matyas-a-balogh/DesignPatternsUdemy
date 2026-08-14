#include "../header.h"

struct Expression {
    virtual ~Expression() = default;
    virtual void print(ostringstream& os) = 0; // visitor
    // this is why it is intrusive visitor, because it is part of the expression interface, so it is known at compile time that all expressions will have this method
    // it was easy now, bc it was a small hierarchy, but if it was a big hierarchy, it would be hard to add this method to all expressions, so it is not a good idea to do this in a big hierarchy
};

// 1+2+3 - numbers and addition are expressions

struct DoubleExpression : Expression {
    double value;
    explicit DoubleExpression(double value) : value(value) {}

    void print(ostringstream& os) override {
        os << value;
    }
};

struct AdditionExpression : Expression {
    Expression* left;
    Expression* right;

    AdditionExpression(Expression* left, Expression* right) : left(left), right(right) {}

    ~AdditionExpression() {
        delete left;
        delete right;
    }

    void print(ostringstream& os) override {
        os << "(";
        left->print(os);
        os << " + ";
        right->print(os);
        os << ")";
    }
};

int main() {
    auto e = new AdditionExpression{
        new DoubleExpression{1},
        new AdditionExpression{
            new DoubleExpression{2},
            new DoubleExpression{3}
        }
    };

    // 1 + (2 + 3)
    ostringstream os;
    e->print(os);
    cout << os.str() << endl;

    delete e;

    return 0;
}
