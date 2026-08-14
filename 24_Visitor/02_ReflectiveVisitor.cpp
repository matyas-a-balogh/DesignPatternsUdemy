#include "../header.h"

struct Expression {
    virtual ~Expression() = default;
};

// 1+2+3 - numbers and addition are expressions

struct DoubleExpression : Expression {
    double value;
    explicit DoubleExpression(double value) : value(value) {}
};

struct AdditionExpression : Expression {
    Expression* left;
    Expression* right;

    AdditionExpression(Expression* left, Expression* right) : left(left), right(right) {}

    ~AdditionExpression() {
        delete left;
        delete right;
    }
};

struct ExpressionPrinter {
    // void print(DoubleExpression* de, ostringstream& os) {
    //     os << de->value;
    // }

    // here it wont work, so we need general
    // void print(AdditionExpression* ae, ostringstream& os) {
    //     os << "(";
    //     ae->left->print(os);
    //     os << " + ";
    //     ae->right->print(os);
    //     os << ")";
    // }

    ostringstream os;

    void print(Expression* e) {
        if (auto de = dynamic_cast<DoubleExpression*>(e)) { // reflection
            os << de->value;
        } else if (auto ae = dynamic_cast<AdditionExpression*>(e)) { // reflection
            os << "(";
            print(ae->left);
            os << " + ";
            print(ae->right);
            os << ")";
        }
    }
    // downsides: 
    // - dynamic cast not good, 
    //   bc it is not known at compile time, 
    //   so it is not good for performance, 
    //   and it is not good for maintainability, 
    //   bc if we add a new expression, 
    //   we need to add a new case here, 
    //   so it is not good for extensibility
    // - there are too many if-s, if bigger
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
    ExpressionPrinter ep;
    ep.print(e);
    cout << ep.os.str() << endl;

    delete e;

    return 0;
}
