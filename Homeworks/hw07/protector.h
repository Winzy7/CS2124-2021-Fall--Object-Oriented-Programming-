//
// Jiezhi Winston Zuo-yu
// protector.h
//

#ifndef HW07_PROTECTOR_H
#define HW07_PROTECTOR_H
#include <iostream>
#include <string>
namespace WarriorCraft {
    class Lord;

    class Protector {
    public:
        Protector(const std::string &name, const double str);

        bool runaway();

        void changeStr(const double ratio);

        bool changeNoble(Lord *newLord);

        virtual void defend() const = 0;

        std::string getName() const;

        const Lord *getLord() const;

        const bool isHired() const;

        int getStr() const;

    private:
        std::string name;
        double str;
        Lord *lord;
        bool alive;
    };

    class Wizard: public Protector{
    public:
        Wizard(const std::string &name, double str);
        void defend() const override;
    };

    class Warrior : public Protector{
    public:
        Warrior(const std::string& name, double str);
        void defend() const override;
    };

    class Archer : public Warrior {
    public:
        Archer(const std::string &name, double str);

        void defend() const override;
    };

    class Swordsman : public Warrior{
    public:
        Swordsman(const std::string& name, double str);

        void defend() const override;
    };
}
#endif //HW07_PROTECTOR_H
