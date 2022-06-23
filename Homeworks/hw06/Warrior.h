//
// Warrior.h
// Jiezhi Winston Zuo-yu
//

#ifndef HW06_WARRIOR_H
#define HW06_WARRIOR_H

#include<iostream>
#include<string>

namespace WarriorCraft {
    class Noble;

    class Warrior {
        friend std::ostream &operator<<(std::ostream &os, const Warrior &fighter);
    public:
        //Warrior Constructor
        Warrior(const std::string &myName, double strength);

        void changeNoble(const std::string &command, Noble *nbl = nullptr);

        const bool isHired() const;

        const std::string &getName() const;

        const double getStr() const;

        const bool runaway();

        void changeStr(double mult);
    private:
        std::string name;
        Noble *noblePtr;
        double str;
    };
}
#endif //HW06_WARRIOR_H
