#include "../header.h"

// very different visitor

template <typename Visitable> struct Visitor {
    virtual void visit(Visitable& obj) = 0;
};

struct VisitorBase {
    virtual ~VisitorBase() = default;
};

struct Expression {
    virtual ~Expression() = default;

    //                                v this is Visitor<T> 
    virtual void accept(VisitorBase& obj) {
        using EV = Visitor<Expression>;
        if (auto ev = dynamic_cast<EV*>(&obj))
            ev->visit(*this);
    }
};

struct DoubleExpression : Expression {
    double value;

    DoubleExpression(double value) : value(value) {}

    virtual void accept(VisitorBase& obj) {
        using DEV = Visitor<DoubleExpression>;
        if (auto ev = dynamic_cast<DEV*>(&obj))
            ev->visit(*this);
    }
};


struct AdditionExpression : Expression {
    Expression *left, *right;

    AdditionExpression(Expression *left, Expression *right) : left(left), right(right) {}

    ~AdditionExpression(){
        delete left;
        delete right;
    }

    virtual void accept(VisitorBase& obj) {
        using AEV = Visitor<AdditionExpression>;
        if (auto ev = dynamic_cast<AEV*>(&obj))
            ev->visit(*this);
    }
};

// VisitorBase is a mocker, but allows us to walk on the things
struct ExpressionPrinter : VisitorBase, 
                           // Visitor<DoubleExpression>,
                           Visitor<AdditionExpression> 
{
private:
    ostringstream os;
public:
    // advantage: it works even when i delete this - no rigid structure needed
    // void visit(DoubleExpression &obj) override {
    //     os << obj.value;
    // }

    void visit(AdditionExpression &obj) override {
        os << "(";
        obj.left->accept(*this);
        os << "+";
        obj.right->accept(*this);
        os << ")";
    }

    string str() const { return os.str(); }
};

int main() {
    auto e = new AdditionExpression {
        new DoubleExpression{1},
        new AdditionExpression {
            new DoubleExpression{2},
            new DoubleExpression{3}
        }
    };

    ExpressionPrinter printer;
    printer.visit(*e);
    cout << printer.str() << endl;

    return 0;
}
