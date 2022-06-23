//
// Noble.cpp
// Jiezhi Winston Zuo-yu
//


#include "Noble.h"
using namespace std;

namespace WarriorCraft {
    int warExists(const vector<Warrior*>& warriors, const string& warName) {
        for (size_t i = 0; i < warriors.size(); ++i) {
            if (warriors[i]->getName() == warName) {
                return i+1;
            }
        }
        return 0;
    }
    //Warrior output operator
    ostream& operator<<(ostream& os, const Noble& noble) {
        os << noble.name << " has an army of " << noble.army.size() << endl;
        for (const Warrior* war : noble.army) {
            os << *war;
        }
        return os;
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

    void Noble::changeArmy(double mult) {
        for (Warrior* war : army) {
            war->changeStr(mult);
        }
    }

    void Noble::battle(Noble& opponent) {
        cout << name << " battles " << opponent.name << endl;
        if (!alive && !opponent.alive) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        else if (!opponent.alive) {
            cout << "He's dead, " << name << endl;
        }
        else if (!alive) {
            cout << "He's dead, " << opponent.name << endl;
        }
        else if (armyStr == opponent.armyStr) {
            cout << "Mutual Annihilation: " << name << " and " << opponent.name
                 << " die at each other's hands" << endl;
            changeArmy(1);
            opponent.changeArmy(1);
            armyStr = 0;
            opponent.armyStr = 0;
            alive = false;
            opponent.alive = false;
        }
        else if (armyStr > opponent.armyStr) {
            cout << name << " defeats " << opponent.name << endl;
            double mult = opponent.armyStr / armyStr;
            changeArmy(mult);
            armyStr -= armyStr * mult;
            opponent.changeArmy(1);
            opponent.armyStr = 0;
            opponent.alive = false;
        }
        else {
            cout << opponent.name << " defeats " << name << endl;
            double mult = armyStr / opponent.armyStr;
            opponent.changeArmy(mult);
            opponent.armyStr -= opponent.armyStr * mult;
            changeArmy(1);
            armyStr = 0;
            alive = false;
        }
    }
}
