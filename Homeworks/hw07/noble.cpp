//
// Jiezhi Winston Zuo-yu
// noble.cpp
//

#include "noble.h"
#include "protector.h"
using namespace std;

namespace WarriorCraft{
    Noble::Noble(const string &name) : name(name), alive(true) {};

    //Gets the name of the noble
    string Noble::getName() const {
        return name;
    }

    //Lord Constructor
    Lord::Lord(const string& name) : Noble(name), str(0) {};

    //Lord attempts to hire a Protector
    const bool Lord::hires(Protector &protector) {
        if (!protector.isHired()) {
            protector.changeNoble(this);
            army.push_back(&protector);
            str += protector.getStr();
            return true;
        }
        return false;
    }

    //Removes a Protector from the army while keeping the army order
    void Lord::orderPop(const Protector* out) {
        int position = protectorExists(army, out);
        for (size_t i = position; i < army.size() - 1; ++i) {
            army[position] = army[position + 1];
        }
        army.pop_back();
    }

    //Gets the name of the Lord
    string Lord::getName() const {
        return Noble::getName();
    }

    //Gets the strength of the Lord
    double Lord::getStr() const {
        return str;
    }

    //When the lord defends, each Protector in the army defends as well
    void Lord::defend() {
        for (Protector* protector: army) {
            protector->defend();
        }
    }

    //Gets the strength for a PWSTF
    double PersonWithStrengthToFight::getStr() const {
        return str;
    }
    //PWSTF Defense method
    void PersonWithStrengthToFight::defend() {
        cout << "UGH!" << endl;
    }

    //Two nobles battle each other
    void Noble::battle(Noble &enemy) {
        cout << name << " battles " << enemy.name << endl;
        if (alive && enemy.alive) {
            defend();
            enemy.defend();
        }
        if (!alive && !enemy.alive) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        else if (!enemy.alive) {
            defend();
            cout << "He's dead, " << name << endl;
        }
        else if (!alive) {
            enemy.defend();
            cout << "He's dead, " << enemy.name << endl;
        }
        else if (getStr() == enemy.getStr()) {
            cout << "Mutual Annihilation: " << name << " and " << enemy.name
                 << " die at each other's hands" << endl;
            changeStr(1);
            enemy.changeStr(1);
            alive = false;
            enemy.alive = false;
        }
        else if (getStr() > enemy.getStr()) {
            cout << name << " defeats " << enemy.name << endl;
            double mult = enemy.getStr() / getStr();
            changeStr(mult);
            enemy.changeStr(1);
            enemy.alive = false;
        }
        else {
            cout << enemy.name << " defeats " << name << endl;
            double mult = getStr() / enemy.getStr();
            enemy.changeStr(mult);
            changeStr(1);
            alive = false;
        }
    }

    //Changes the strength of each protector in the lord's army
    void Lord::changeStr(double mult) {
        for (Protector* protector : army) {
            protector->changeStr(mult);
        }
        str -= str * mult;
    }

    //Changes the strength of a PWSTF
    void PersonWithStrengthToFight::changeStr(double mult) {
        str -= str * mult;
    }

    //Lord attempts to fire a Protector
    const bool Lord::fires(Protector* protector) {
        int position = protectorExists(army, protector);
        if (!position || army.size() == 0) {
            cout << "Attempting to fire warrior not employed by noble: "
                 << Noble::getName() << endl;
            return false;
        }
        protector->changeNoble(nullptr);
        orderPop(protector);
        str -= protector->getStr();
        cout << "You don't work for me anymore " << protector->getName()
            << "! -- " << Noble::getName() << "." << endl;
        army.pop_back();
        return true;
    }

    //Checks for the position of a protector within a given army
    int protectorExists(const vector<Protector*>& army, const Protector* protector) {
        for (size_t i = 0; i < army.size(); ++i) {
            if (army[i] == protector) {
                return i;
            }
        }
        return 0;
    }

    //PWSTF Constructor
    PersonWithStrengthToFight::PersonWithStrengthToFight (const string &name, const double str) : Noble(name), str(str) {};

    //Gets the PWSTF's name
    string PersonWithStrengthToFight::getName() const {
        return Noble::getName();
    }
}