/*
  Jiezhi Winston Zuo-yu: rec04.cpp
 */

 // Provided
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Task 1
// Define an Account struct
struct AccountInfo {
    string name;
    int number;
};


// Task 2
// Define an Account class
class Account {
    friend ostream& operator<<(ostream& os, const Account& someone);
private:
    string name;
    int number;
public:
    Account(const string& aName,const int& num) : name(aName), number(num) {}
    const string& getName() const {
        return name;
    }
    const int& getNum() const {
        return number;
    }
};

ostream& operator<<(ostream& os, const Account& someone) {
    //os << someone.getName() << "\t" << someone.getNum();
    os << someone.name << "\t" << someone.number;
    return os;
}

// Task 3
// Define an Account and Transaction classes

class Transaction {
    friend ostream& operator<<(ostream& os, const Transaction& tran);
private:
    string moneyio;
    int amount;
public:
    Transaction(const string& command,int num) : moneyio(command), amount(num) {};
    /*
    const string& io() const {
        return moneyio;
    }
    const int& getNum() const {
        return amount;
    }
    */
};

ostream& operator<<(ostream& os, const Transaction& tran) {
    os << tran.moneyio << " " << tran.amount;
    return os;
}

class AccountTran {
    friend ostream& operator<<(ostream& os, const AccountTran& acc);

private:
    string name;
    int accnum;
    vector<Transaction> tranHistory;
    int balance = 0;
public:
    AccountTran(const string& aName, int num) : name(aName), accnum(num) {}
    void deposit(int cash) {
        balance += cash;
        tranHistory.emplace_back("deposit", cash );
    }
    void withdrawal(int cash) {
        if (balance < cash) {
            cout << "Account# " << accnum << " has only " << balance << ". Insufficient for withdrawal of " << cash << "." << endl;
        }
        else {
            balance -= cash;
            tranHistory.emplace_back("withdrawal", cash);
        }
    }
    int getBalance() const {
        return balance;
    }
    int getNumber() const {
        return accnum;
    }
};

ostream& operator<<(ostream& os, const AccountTran& acc) {
    os << acc.name << "\t" << acc.accnum << ":" << endl;
    for (size_t tran = 0; tran < acc.tranHistory.size(); ++tran) {
        os << "\t" << acc.tranHistory[tran] << endl;
    }
    return os;
}
// Task 4
// Define an Account with a nested public Transaction class

// Task 5
// Define an Account with a nested private Transaction class


int main() {

    // Task 1: account as struct
    //      1a
    cout << "Task1a:\n";
    ifstream accs("accounts.txt");
    if (!accs) {
        cerr << "Could not open the file.\n";
        exit(1);
    }
    AccountInfo acc;
    vector<AccountInfo> vectorOfAccounts;
    string name;
    int num;
    while (accs >> name) {
        accs >> num;
        acc.name = name;
        acc.number = num;
        vectorOfAccounts.push_back(acc);
    }
    accs.close();
    for (size_t accnum = 0; accnum < vectorOfAccounts.size(); ++accnum) {
        cout << vectorOfAccounts[accnum].name << "\t" << vectorOfAccounts[accnum].number << endl;
    }
    vectorOfAccounts.clear();
    accs.open("accounts.txt");
    while (accs >> name) {
        accs >> num;
        AccountInfo acc{ name,num };
        vectorOfAccounts.push_back(acc);
    }
    cout << endl;
    for (size_t accnum = 0; accnum < vectorOfAccounts.size(); ++accnum) {
        cout << vectorOfAccounts[accnum].name << "\t" <<  vectorOfAccounts[accnum].number << endl;
    }
    accs.close();
    vectorOfAccounts.clear();
    //      1b
    cout << "Task1b:\n";
    cout << "Filling vector of struct objects, using {} initialization:\n";


    //==================================
    // Task 2: account as class

    //      2a
    cout << "==============\n";
    cout << "\nTask2a:";
    cout << "\nFilling vector of class objects, using local class object:\n";
    vector<Account> vectorClassAccounts;
    accs.open("accounts.txt");
    while (accs >> name >> num) {
        //accs >> num;
        Account acc(name,num);
        vectorClassAccounts.push_back(acc);
    }

    for (size_t accnum = 0; accnum < vectorClassAccounts.size(); ++accnum) {
        cout << vectorClassAccounts[accnum].getName() << "\t" << vectorClassAccounts[accnum].getNum() << endl;
    }

    cout << "\nTask2b:\n";
    cout << "output using output operator with getters\n";
    /*
    ostream& operator<<(ostream & os, const Account & someone) {
        os << someone.getName() << someone.getNum();
        return os;
    }
    */
    for (size_t accnum = 0; accnum < vectorClassAccounts.size(); ++accnum) {
        cout << vectorClassAccounts[accnum] << endl;
    }
    cout << "\nTask2c:\n";
    cout << "output using output operator as friend without getters\n";

    for (size_t accnum = 0; accnum < vectorClassAccounts.size(); ++accnum) {
        cout << vectorClassAccounts[accnum] << endl;
    }

    cout << "\nTask2d:\n";
    cout << "Filling vector of class objects, using temporary class object:\n";

    vectorClassAccounts.clear();
    accs.close();
    accs.open("accounts.txt");
    while (accs >> name) {
        accs >> num;
        vectorClassAccounts.push_back(Account( name, num ));
    }
    for (size_t accnum = 0; accnum < vectorClassAccounts.size(); ++accnum) {
        cout << vectorClassAccounts[accnum] << endl;
    }

    cout << "\nTask2e:\n";
    cout << "Filling vector of class objects, using emplace_back:\n";

    vectorClassAccounts.clear();
    accs.close();
    accs.open("accounts.txt");
    while (accs >> name) {
        accs >> num;
        vectorClassAccounts.emplace_back(name, num);
    }
    for (size_t accnum = 0; accnum < vectorClassAccounts.size(); ++accnum) {
        cout << vectorClassAccounts[accnum] << endl;
    }
    

    cout << "==============\n";
    cout << "\nTask 3:\nAccounts and Transaction:\n";

    accs.close();
    accs.open("transactions.txt");
    vector<AccountTran> TranAccounts;
    string command;
    
    while (accs >> command) {
        if (command == "Account") {
            accs >> name;
            accs >> num;
            TranAccounts.emplace_back(name, num);
        }
        else if (command == "Deposit") {
            accs >> num;
            for (size_t accnum = 0; accnum < TranAccounts.size(); ++accnum) {
                if (TranAccounts[accnum].getNumber() == num) {
                    accs >> num;
                    TranAccounts[accnum].deposit(num);
                }
            }
        }
        else {
            accs >> num;
            for (size_t accnum = 0; accnum < TranAccounts.size(); ++accnum) {
                if (TranAccounts[accnum].getNumber() == num) {
                    accs >> num;
                    TranAccounts[accnum].withdrawal(num);
                }
            }
        }
    }
    accs.close();
    for (size_t acc = 0; acc < TranAccounts.size(); ++acc) {
        cout << TranAccounts[acc] << endl;
    }
    

    cout << "==============\n";
    cout << "\nTask 4:\nTransaction nested in public section of Account:\n";

    cout << "==============\n";
    cout << "\nTask 5:\nTransaction nested in private section of Account:\n";


}
