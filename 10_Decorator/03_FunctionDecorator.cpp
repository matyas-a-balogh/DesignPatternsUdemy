#include "../header.h"


struct Logger 
{
    function<void()> func;
    string name;

    Logger(const function<void()> &func, const string &name) : func(func), name(name) {}

    void operator()() const
    {
        cout << "Entering " << name << endl;
        func();
        cout << "Exiting " << name << endl;        
    }
};

// update
template <typename Func> struct LoggerTempl
{
    Func func;
    string name;

    LoggerTempl(const Func &func, const string &name) : func(func), name(name) {}

    void operator()() const
    {
        cout << "Entering " << name << endl;
        func();
        cout << "Exiting " << name << endl;        
    }
};

// helper for type definition - since C++17 it is automatically deduces it
// template<typename Func> auto make_logger_templ(Func func, const string& name)
// {
//     return LoggerTempl<Func>{func, name};
// };

// it becomes much more complex if there are params involved
double add(double a, double b)
{
    cout << a << "+" << b << "=" << (a+b) << endl;
    return a+b;
};

template<typename> struct LoggerEvolved;

template<typename  R, typename... Args> struct LoggerEvolved<R(Args...)>
{
    // a function that return R and takes number of arguments 
    function<R(Args...)> func;
    string name;

    LoggerEvolved(const function<R(Args...)> &func, const string &name) : func(func), name(name) {}

    R operator() (Args... args)
    {
        cout << "Entering " << name << endl;
        R result = func(args...);
        cout << "Exiting " << name << endl;
        return result;
    }
};

// helper to figure out args
template<typename R, typename... Args> auto make_logger_evolved(R (*func)(Args...), const string& name)
{
    return LoggerEvolved<R(Args...)>(
        function<R(Args...)>(func), name
    );
};

int main()
{
    // how to update a function, not just classes
    cout << "Hello" << endl; // augment this - wrap it

    Logger([](){cout << "Hello" << endl;}, "HelloFunction")();
    LoggerTempl([](){cout << "Hello" << endl;}, "HelloFunction")(); // shouldnnt run without concrete type definition, but in newer versions it is handled as lambda
    // auto log = make_logger_templ([](){cout << "Hello" << endl;}, "HelloFunction");
    // log();

    auto logged_add = make_logger_evolved(add, "Add");
    auto result = logged_add(2, 3);
    cout << "result = " << result << endl;
}
