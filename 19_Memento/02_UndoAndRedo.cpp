#include "../header.h"

class Memento {
    int balance;
public:
    Memento(int balance) : balance(balance) {}

    friend class BankAccountWithHistory;
};

class BankAccountWithHistory {
    int balance{0};
    vector<shared_ptr<Memento>> changes;
    int current;
public:
    BankAccountWithHistory(int balance) : balance(balance) {
        changes.emplace_back(make_shared<Memento>(balance));
        current = 0;
    }

    shared_ptr<Memento> deposit(int amount) {
        balance += amount;
        auto m = make_shared<Memento>(balance);
        changes.push_back(m);
        ++current;
        return m;
    }

    void restore(const shared_ptr<Memento>& m){
        if (m){
            balance = m->balance;
            changes.push_back(m);
            current = changes.size()-1;
        }
    }

    shared_ptr<Memento> undo()
    {
        if (current>0)
        {
            --current;
            auto m = changes[current];
            balance = m->balance;
            return m;
        }
        return {};
    }

    shared_ptr<Memento> redo()
    {
        if (current+1<changes.size())
        {
            ++current;
            auto m = changes[current];
            balance = m->balance;
            return m;
        }
        return {};
    }

    friend ostream& operator<<(ostream& os, const BankAccountWithHistory& ba) {
        return os << "balance: " << ba.balance;
    }
};

int main() {
    BankAccountWithHistory ba{100};
    ba.deposit(50);
    ba.deposit(25);

    cout << ba << endl;
    
    ba.undo();
    cout << "Undo 1: " << ba << endl;
    ba.undo();
    cout << "Undo 2: " << ba << endl;
    ba.redo();
    cout << "Redo: " << ba << endl;

    return 0;
}
