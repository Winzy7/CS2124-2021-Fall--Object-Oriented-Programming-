//
// Jiezhi Winston Zuo-yu
// protector.cpp
//

#include "protector.h"
#include "noble.h"
using namespace std;

namespace WarriorCraft{

    //Protector Constructor
    Protector::Protector(const string& name, const double str):
            name(name), str(str), lord(nullptr), alive (true) {};

    //Gets the lord of the Protector
    const Lord* Protector::getLord() const {
        return lord;
    }

    //Checks if the Protector is hired
    const bool Protector::isHired() const {
        return !(lord==nullptr);
    }

    //Gets the Protector's strength
    int Protector::getStr() const{
        return str;
    }

    //Gets the Protector's name
    string Protector::getName() const {
        return name;
    }

    //Changes the Protector's strength
    void Protector::changeStr(const double ratio) {
        str -= str * ratio;
    }

    //Changes the Protector's Noble
    bool Protector::changeNoble(Lord* newLord) {
        if (!lord) {
            lord = newLord;
            return true;
        }
        return false;
    }

    //A protector runs away from his/her Noble
    bool Protector::runaway() {
        if (lord) {
            cout << name << " flees in terror, abandoning "
            << "his lord, " << lord->getName() << endl;
            lord->orderPop(this);
            lord = nullptr;
            return true;
        }
        return false;
    }

    //Wizard constructor
    Wizard::Wizard(const string &name, double str) : Protector(name, str) {};

    //Wizard defends
    void Wizard::defend() const {
        cout << "POOF!" << endl;
    }

    //Warrior constructor
    Warrior::Warrior(const string &name, double str) : Protector(name, str) {};

    //Warrior defends
    void Warrior::defend() const {
        cout << " says: Take that in the name of my lord, ";
    }

    //Archer constructor
    Archer::Archer(const string &name, double str) : Warrior(name, str) {};

    //Archer defends
    void Archer::defend() const{
        if (Protector::getLord()) {
            cout << "TWANG! " << Protector::getName();
            Warrior::defend();
            cout << Protector::getLord()->getName() << endl;
        }
    }

    //Swordsman constructor
    Swordsman::Swordsman(const string &name, double str) : Warrior(name, str) {};

    //Swordsman defends
    void Swordsman::defend() const{
        if (Protector::getLord()) {
            cout << "CLANG! " << Protector::getName();
            Warrior::defend();
            cout << Protector::getLord()->getName()<< endl;
        }
    }
}