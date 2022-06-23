//
// Noble.h
// Jiezhi Winston Zuo-yu
//

#ifndef HW06_NOBLE_H
#define HW06_NOBLE_H

#include "Warrior.h"
#include<iostream>
#include<vector>
#include<string>

namespace WarriorCraft {

    class Noble {
        friend std::ostream &operator<<(std::ostream &os, const Noble &noble);

    public:
        Noble(const std::string &myName);

        const bool hire(Warrior &warrior);

        const bool fire(Warrior &warrior, const std::string &cmd = "");

        void changeArmy(double mult);

        void battle(Noble &opponent);

    private:
        std::string name;
        double armyStr;
        std::vector<Warrior *> army;
        bool alive;
    };
}

#endif //HW06_NOBLE_H
