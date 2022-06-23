//
// Jiezhi Winston Zuo-yu
// noble.h
//

#ifndef HW07_NOBLE_H
#define HW07_NOBLE_H
#include <vector>
#include <string>
#include <iostream>
#include "protector.h"

namespace WarriorCraft{
    class Noble {
    public:
        Noble(const std::string& name);
        void battle(Noble& enemy);
        virtual std::string getName() const = 0;
        virtual double getStr() const = 0;
        virtual void changeStr(double mult) = 0;
        virtual void defend() = 0;
    private:
        std::string name;
        bool alive;
    };

    class Lord: public Noble{
    public:
        Lord(const std::string& name);
        const bool fires(Protector* protector);
        void orderPop(const Protector* out);
        const bool hires(Protector &protector);
        std::string getName() const override;
        double getStr() const override;
        virtual void changeStr(double mult) override;
        virtual void defend() override;
    private:
        std::vector<Protector*> army;
        double str;
    };
    class PersonWithStrengthToFight : public Noble{
    public:
        PersonWithStrengthToFight (const std::string &name, const double str);
        std::string getName() const override;
        double getStr() const override;
        virtual void changeStr(double mult) override;
        virtual void defend() override;
    private:
        double str;
    };

    int protectorExists(const std::vector<Protector*>& army, const Protector* protector);
}
#endif //HW07_NOBLE_H
