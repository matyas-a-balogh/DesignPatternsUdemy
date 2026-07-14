#include "../header.h"

struct BankAccount
{
    int balance{0};
    int overdraft_limits{-500};

    void deposit(int amount)
    {
        balance += amount;
        cout << "Deposited " << amount 
             << ", balance is now " << balance << endl;
    }

    bool withdraw(int amount)
    {
        if (balance - amount >= overdraft_limits)
        {
            balance -= amount;
            cout << "Withdrew " << amount 
                 << ", balance is now " << balance << endl;
            return true;
        }
        return false;
    }

    friend ostream& operator<<(ostream& os, const BankAccount& obj) {
        return os << "balance: " << obj.balance;
    }
};

// Commands
struct Command
{
    bool succeeded;
    virtual void call() = 0;
    virtual void undo() = 0;
};

struct BankAccountCommand : Command
{
    BankAccount& account;
    enum Action { deposit, withdraw } action;
    int amount;

    BankAccountCommand(BankAccount& account, Action action, int amount)
        : account(account), action(action), amount(amount) { succeeded = false; }

    void call() override {
        switch(action) {
            case deposit:
                account.deposit(amount);
                succeeded = true;
                break;
            case withdraw:
                succeeded = account.withdraw(amount);
                break;
        }
    }

    void undo() override {
        if (!succeeded) return;
        switch(action) {
            case deposit:
                account.withdraw(amount);
                break;
            case withdraw:
                account.deposit(amount);
                break;
        }
    }
};

// its also a composite design pattern
struct CompositeBankAccountCommand : vector<BankAccountCommand>, Command
{
    CompositeBankAccountCommand(const initializer_list<BankAccountCommand>& items)
        : vector(items) {}

    void call() override {
        for (auto& cmd : *this)
            cmd.call();
    }

    void undo() override {
        for (auto it = rbegin(); it != rend(); ++it)
            it->undo();
    }
};

// there is a lot of complication if one command fails, so we can create a dependent composite command
// there are lot of factors when multiple commands work together
struct DependentCompositeCommand : CompositeBankAccountCommand
{
    DependentCompositeCommand(const initializer_list<BankAccountCommand>& items)
        : CompositeBankAccountCommand(items) {}

    void call() override {
        bool ok = true;
        for (auto& cmd : *this) {
            if (ok) {
                cmd.call();
                ok = cmd.succeeded; 
            }
            else {
                cmd.succeeded = false;
            }
        }
    }
};

struct MoneyTransferCommand : DependentCompositeCommand
{
    MoneyTransferCommand(BankAccount& from, BankAccount& to, int amount)
        : DependentCompositeCommand{
            BankAccountCommand{from, BankAccountCommand::withdraw, amount},
            BankAccountCommand{to, BankAccountCommand::deposit, amount}            
        } {}
};

int main()
{
    BankAccount ba, ba2;
    ba.deposit(100);

    MoneyTransferCommand cmd{ba, ba2, 5000};
    cmd.call();
    cout << ba << endl << ba2 << endl;
    cmd.undo();
    cout << ba << endl << ba2 << endl;

    return 0;
}
