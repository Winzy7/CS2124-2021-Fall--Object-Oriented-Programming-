/*
hw06.cpp
Jiezhi Winston Zuo-yu
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Warrior;

//Noble Class
class Noble {
    friend ostream& operator<<(ostream& os, const Noble& noble);
public:
    //Noble Constructor
    Noble(const string& myName);
    const bool hire(Warrior& warrior);
    const bool fire(Warrior& warrior, const string& cmd = "");
    //Changes the strength of the entire army by a multiplier
    void changeArmy(double mult);
    void battle(Noble& opponent);
private:
    string name;
    double armyStr;
    vector<Warrior*> army;
    bool alive;
};

//Warrior Class
class Warrior {
    friend ostream& operator<<(ostream& os, const Warrior& fighter);
public:
    //Warrior Constructor
    Warrior(const string& myName, double strength);
    void changeNoble(const string& command, Noble* nbl);
    const bool isHired() const;
    const string& getName() const;
    const double getStr() const;
    //Warrior runs away from his/her employer
    const bool runaway();
    //Changes the strength of the Warrior
    void changeStr(double mult);
private:
    string name;
    Noble* noblePtr;
    double str;
};

int main(){
}

ostream& operator<<(ostream& os, const Warrior& fighter) {
    os << "\t" << fighter.name << ": " << fighter.str << endl;
    return os;
}

Warrior::Warrior(const string& myName, double strength) : name(myName), str(strength), noblePtr(nullptr) {}

void Warrior::changeNoble(const string& command, Noble* nbl = nullptr) {
    noblePtr = nbl;
}
const bool Warrior::isHired() const {
    return noblePtr;
}
const string& Warrior::getName() const {
    return name;
}
const double Warrior::getStr() const {
    return str;
}
void Warrior::changeStr(double mult) {
    str -= str * mult;
}


const bool Warrior::runaway() {
    if (!noblePtr){
        return false;
    }
    noblePtr->fire(*this, "runaway");
    noblePtr = nullptr;
    return true;
}

//Noble output operator
ostream& operator<<(ostream& os, const Noble& noble) {
    os << noble.name << " has an army of " << noble.army.size() << endl;
    for (const Warrior* war : noble.army) {
        os << *war;
    }
    return os;
}

//Checks if a Warrior exists in a given army
int warExists(const vector<Warrior*>& warriors, const string& warName) {
    for (size_t i = 0; i < warriors.size(); ++i) {
        if (warriors[i]->getName() == warName) {
            return i+1;
        }
    }
    return 0;
}

Noble::Noble(const string& myName) : name(myName), armyStr(0), alive(true) {}

const bool Noble::hire(Warrior& warrior) {
    if (warrior.isHired()) {
        cout << "Attempting to hire using employed warrior: "
             << warrior.getName() << endl;
        return false;
    }
    warrior.changeNoble("hire", this);
    army.push_back(&warrior);
    armyStr += warrior.getStr();
    return true;
}

void Noble::changeArmy(double mult) {
    for (Warrior* war : army) {
        war->changeStr(mult);
    }
}

const bool Noble::fire(Warrior& warrior, const string& cmd) {
    int war = warExists(army, warrior.getName());
    if (!war || army.size() == 0) {
        cout << "Attempting to fire warrior not employed by noble: "
             << name << endl;
        return false;
    }
    for (size_t i = (war - 1); i < (army.size() - 1); ++i) {
        army[i] = army[i + 1];
    }
    warrior.changeNoble("fire");
    armyStr -= warrior.getStr();
    if (cmd == "runaway") {
        cout << warrior.getName() << " flees in terror, abandoning "
             << "his lord, " << name << endl;
    }
    else {
        cout << "You don't work for me anymore " << warrior.getName()
             << "! -- " << name << "." << endl;
    }
    army.pop_back();
    return true;
}

void Noble::battle(Noble &opponent) {
        cout << name << " battles " << opponent.name << endl;
        if (!alive && !opponent.alive) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        } else if (!opponent.alive) {
            cout << "He's dead, " << name << endl;
        } else if (!alive) {
            cout << "He's dead, " << opponent.name << endl;
        } else if (armyStr == opponent.armyStr) {
            cout << "Mutual Annihilation: " << name << " and " << opponent.name
                 << " die at each other's hands" << endl;
            changeArmy(1);
            opponent.changeArmy(1);
            armyStr = 0;
            opponent.armyStr = 0;
            alive = false;
            opponent.alive = false;
        } else if (armyStr > opponent.armyStr) {
            cout << name << " defeats " << opponent.name << endl;
            double mult = opponent.armyStr / armyStr;
            changeArmy(mult);
            armyStr -= armyStr * mult;
            opponent.changeArmy(1);
            opponent.armyStr = 0;
            opponent.alive = false;
        } else {
            cout << opponent.name << " defeats " << name << endl;
            double mult = armyStr / opponent.armyStr;
            opponent.changeArmy(mult);
            opponent.armyStr -= opponent.armyStr * mult;
            changeArmy(1);
            armyStr = 0;
            alive = false;
        }
    }
