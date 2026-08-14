#include "../header.h"

// Classic visitor is DOUBLE DISPATCH: first we call accept on the expression, then we call visit on the visitor, 
// so it is known at compile time which visit method will be called, so it is good for performance and maintainability

struct DoubleExpression;
struct AdditionExpression;
struct SubstractionExpression;

struct ExpressionVisitor {
    virtual void visit(DoubleExpression *de) = 0;
    virtual void visit(AdditionExpression *ae) = 0;  
    virtual void visit(SubstractionExpression *se) = 0;  
};

struct ExpressionPrinter : ExpressionVisitor {
    ostringstream os;
    string str() const { return os.str(); }

    void visit(DoubleExpression *de) override;
    void visit(AdditionExpression *ae) override;
    void visit(SubstractionExpression *se) override;
};

// not only printing can be done, but evaluating too
// with double dispatch you can implement whatever visitor you want
struct ExpressionEvaluator : ExpressionVisitor {
    double result;
    
    void visit(DoubleExpression *de) override;
    void visit(AdditionExpression *ae) override;
    void visit(SubstractionExpression *se) override;
};

// Double dispatch means the final function chosen depends on two things:
// 1. the real type of the expression object
// 2. the visitor object/function overload
//
// Example:
// Expression* e = new AdditionExpression{...};
// ExpressionPrinter printer;
// e->accept(&printer);
//
// Even though e is typed as Expression*, the real object can be AdditionExpression.
// e->accept(&printer) uses virtual dispatch and jumps to AdditionExpression::accept.
//
// Inside AdditionExpression::accept, this has the exact type AdditionExpression*.
// So visitor->visit(this) selects ExpressionPrinter::visit(AdditionExpression*).
//
// Important lines:
// e->accept(&printer);      // first dispatch: which concrete expression am I?
// visitor->visit(this);     // second dispatch: call the matching visitor overload
//
// Without accept(), visitor->visit(e) would only see Expression* and would not
// automatically choose visit(AdditionExpression*).

// Double dispatch summary:
// 1. have an accept(visitor* v) method to all hierarchy
// 2. cretae a visit(*) for each element
// 3. each accept() simply calls visitor.visit(this)

struct Expression {
    virtual ~Expression() = default;
    
    virtual void accept(ExpressionVisitor* visitor) = 0; // always called accept()
};

struct DoubleExpression : Expression {
    double value;
    explicit DoubleExpression(double value) : value(value) {}

    void accept(ExpressionVisitor* visitor) override {
        visitor -> visit(this);
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

    // this is the trick, so no type have to be passed
    // ugly solution
    void accept(ExpressionVisitor* visitor) override {
        visitor -> visit(this); // we need the type of this pointer, I need to add it to all inheritance - this is the "double"
    }
};

struct SubstractionExpression : Expression {
    Expression* left;
    Expression* right;

    SubstractionExpression(Expression* left, Expression* right) : left(left), right(right) {}

    ~SubstractionExpression() {
        delete left;
        delete right;
    }

    void accept(ExpressionVisitor* visitor) override {
        visitor -> visit(this);
    }
};

// Printer implementations

void ExpressionPrinter::visit(DoubleExpression *de) {
    os << de->value;
}

void ExpressionPrinter::visit(AdditionExpression *ae) {
    // adding new stuff, lets make it harder
    ae->left->accept(this);
    os << "+";
    bool need_braces = dynamic_cast<SubstractionExpression*>(ae->right);
    if (need_braces) os << "(";
    ae->right->accept(this);
    if (need_braces) os << ")";   
    
}

void ExpressionPrinter::visit(SubstractionExpression *se) {
    se->left->accept(this);
    os << "-";
    bool need_braces = dynamic_cast<SubstractionExpression*>(se->right);
    if (need_braces) os << "(";
    se->right->accept(this);
    if (need_braces) os << ")";    
}

// Evaluator implementations

void ExpressionEvaluator::visit(DoubleExpression *de) {
    result = de->value;
}

void ExpressionEvaluator::visit(AdditionExpression *ae) {
    ae->left->accept(this);
    auto temp = result;
    ae->right->accept(this);
    result += temp;    
}

void ExpressionEvaluator::visit(SubstractionExpression *se) {
    se->left->accept(this);
    auto temp = result;
    se->right->accept(this);
    result = temp - result;    
}

int main() {
    auto e = new AdditionExpression {
        new DoubleExpression{1},
        new SubstractionExpression {
            new DoubleExpression{2},
            new DoubleExpression{3}
        }
    };

    ExpressionPrinter printer;
    printer.visit(e);
    cout << printer.str() << endl;

    ExpressionEvaluator evaluator;
    evaluator.visit(e);
    cout << printer.str() << " = " << evaluator.result << endl;

    return 0;
}
