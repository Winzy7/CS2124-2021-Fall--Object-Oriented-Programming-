//
// Warrior.cpp
// Jiezhi Winston Zuo-yu
//

#include"Warrior.h"
#include"Noble.h"
using namespace std;

namespace WarriorCraft{
    Warrior::Warrior(const string& myName, double strength) : name(myName), str(strength), noblePtr(nullptr) {}
    void Warrior::changeNoble(const string& command, Noble* nbl) {
        noblePtr = nbl;
    }

    ostream& operator<<(ostream& os, const Warrior& fighter) {
        os << "\t" << fighter.name << ": " << fighter.str << endl;
        return os;
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
    const bool Warrior::runaway(){
        if (!noblePtr){
            return false;
        }
        noblePtr->fire(*this, "runaway");
        noblePtr = nullptr;
        return true;
    }
    void Warrior::changeStr(double mult) {
        str -= str * mult;
    }
}
