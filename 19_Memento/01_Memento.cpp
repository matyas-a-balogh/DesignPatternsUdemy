#include "../header.h"

class Memento {
    int balance;
public:
    Memento(int balance) : balance(balance) {}

    friend class BankAccount;
};

class BankAccount {
    int balance{0};
public:
    BankAccount(int balance) : balance(balance) {}

    Memento deposit(int amount) {
        balance += amount;
        return {balance};
    }

    void restore(const Memento& m) {
        balance = m.balance;
    }

    friend ostream& operator<<(ostream& os, const BankAccount& ba) {
        return os << "balance: " << ba.balance;
    }
};

int main() {
    BankAccount ba{100};
    auto m1 = ba.deposit(50);
    auto m2 = ba.deposit(25);

    cout << ba << endl;
    ba.restore(m1);
    cout << "Restored to m1: " << ba << endl;
    ba.restore(m2);
    cout << "Restored to m2: " << ba << endl;

    return 0;
}
