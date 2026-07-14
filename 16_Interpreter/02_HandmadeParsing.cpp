#include "../header.h"
#include <boost/lexical_cast.hpp>

struct Token
{
    enum Type { integer, plus, minus, lparen, rparen } type;
    string text;

    Token(Type type, const string& text) : type(type), text(text) {}

    friend ostream &operator<<(ostream &os, const Token &token) {
        return os << "`" << token.text << "`";
    }
};

vector<Token> lex(const string &input) {
    vector<Token> result;
    for (size_t i = 0; i < input.size(); ++i) {
        switch (input[i]) {
            case '+':
                result.push_back(Token{ Token::plus, "+" });
                break;
            case '-':
                result.push_back(Token{ Token::minus, "-" });
                break;
            case '(':
                result.push_back(Token{ Token::lparen, "(" });
                break;
            case ')':
                result.push_back(Token{ Token::rparen, ")" });
                break;
            default:
                ostringstream buffer;
                buffer << input[i];
                for (int j=i+1; j < input.size(); j++)
                {
                    if (isdigit(input[j])){
                        buffer << input[j];
                        ++i;
                    }
                    else {
                        result.push_back(Token {Token::integer, buffer.str()});
                        break;
                    }
                }
        }
    }
    return result;
}

struct Element
{
    virtual int eval() const = 0; // this is visitor dp too, see later
};

struct Integer : Element
{
    int value;

    Integer(int value) : value(value) {}

    int eval() const override {
        return value;
    }
};

struct BinaryOperation : Element
{
    enum Type { addition, subtraction } type;
    shared_ptr<Element> left, right;

    int eval() const override {
        switch (type) {
            case addition:
                return left->eval() + right->eval();
            case subtraction:
                return left->eval() - right->eval();
            default:
                throw runtime_error("Unsupported operation");
        }
    }
};

shared_ptr<Element> parse(const vector<Token>& tokens) {
    auto result = make_shared<BinaryOperation>();
    bool haveLHS{false};

    for (size_t i = 0; i < tokens.size(); ++i) {
        auto& token = tokens[i];
        switch (token.type) {
            case Token::integer: {
                int value = boost::lexical_cast<int>(token.text);
                auto integer = make_shared<Integer>(value);
                if (!result->left) {
                    result->left = integer;
                } else {
                    result->right = integer;
                }
                break;
            }
            case Token::plus:
                result->type = BinaryOperation::addition;
                break;
            case Token::minus:
                result->type = BinaryOperation::subtraction;
                break;
            case Token::lparen:
                {
                    int j = i;
                    for(; j < tokens.size(); ++j)
                        if (tokens[j].type == Token::rparen)
                            break;
                    vector<Token> subexpression(&tokens[i+1], &tokens[j]);
                    auto element = parse(subexpression);
                    if (!haveLHS){
                        result->left = element;
                        haveLHS = true;
                    }
                    else {
                        result->right = element;
                    }
                    i = j; // skip parens
                }
                break;
            default:
                throw runtime_error("Unexpected token");
        }
    }
    return result;
}

int main() {
    string input{"(13-4)-(12+1)"};

    auto tokens = lex(input);

    for (auto& t: tokens)
        cout << t << endl;

    try {
        auto parsed = parse(tokens);
        cout << input << " = " << parsed->eval() << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
