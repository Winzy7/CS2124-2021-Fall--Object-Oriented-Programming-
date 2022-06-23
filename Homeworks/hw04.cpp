/*
  hw04.cpp
  Winston Zuo-yu
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

//Warrior class
class Warrior {
	friend ostream& operator<<(ostream& os, const Warrior& fighter);
private:
	//Warrior has a name, strength, and a boolean for whether or not he has been hired
	string name;
	double str;
	bool noble = false;
public:
	Warrior(const string& myName, double strength) : str(strength), name(myName) {}
	void changeNoble(const string& command) {
		if (command == "hire") {
			noble = true;
		}
		else if (command == "fire") {
			noble = false;
		}
	}
	const bool hasNoble() {
		return noble;
	}
	Warrior* address() {
		return this;
	}
	const string& getName() {
		return name;
	}
	const double getStr() {
		return str;
	}
	void changeStr(double mult) {
		str -= str * mult;
	}
};

//output operator for class Warrior
ostream& operator<<(ostream& os, const Warrior& fighter) {
	os << "\t" << fighter.name << ": " << fighter.str << endl;
	return os;
}

//Noble class
class Noble {
	friend ostream& operator<<(ostream& os, const Noble& noble);
private:
	//Noble has a name, an army of Warriors, the army's combined strength, and
	//a boolean for whether the Noble is dead or alive
	string name;
	vector<Warrior*> army;
	double army_str = 0;
	bool alive = true;
public:
	Noble(const string& myName) : name(myName) {}
	//Noble attempt to hire a Warrior
	bool hire(Warrior& fighter) {
		if (fighter.hasNoble() || !alive) {
			return false;
		}
		fighter.changeNoble("hire");
		army.push_back(fighter.address());
		army_str += fighter.getStr();
		return true;
	}
	//Noble attempt to fire a Warrior
	bool fire(Warrior& fighter) {
		if (!fighter.hasNoble() || !alive) {
			return false;
		}
		else {
			for (size_t i = 0; i < army.size(); ++i) {
				if (army[i] == fighter.address()) {
					fighter.changeNoble("fire");
					removeFromArmy(army, i);
					army_str -= fighter.getStr();
					cout << "You don't work for me anymore " << fighter.getName()
					<< "! -- " << name << "." << endl;
					return true;
				}
			}
		}
		return false;
	}
	//Removes a given Warrior in the Noble's army
	void removeFromArmy(vector<Warrior*>& army, size_t position) {
		for (size_t i = position; i < (army.size() - 1); ++i) {
			swap(army[i],army[i + 1]);
		}
		army.pop_back();
	}
	//Noble does battle with another Noble
	void battle(Noble& opponent) {
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
		else if (army_str == opponent.army_str) {
			cout << "Mutual Annihilation: " << name << " and " << opponent.name
				<< " die at each other's hands" << endl;
			changeArmy(army, 1);
			opponent.changeArmy(opponent.army, 1);
			army_str = 0;
			opponent.army_str = 0;
			alive = false;
			opponent.alive = false;
		}
		else if (army_str > opponent.army_str) {
			cout << name << " defeats " << opponent.name << endl;
			double mult = opponent.army_str / army_str;
			changeArmy(army, mult);
			army_str -= army_str * mult;
			opponent.changeArmy(opponent.army, 1);
			opponent.army_str = 0;
			opponent.alive = false;
		}
		else {
			cout << opponent.name << " defeats " << name << endl;
			double mult = army_str / opponent.army_str;
			opponent.changeArmy(opponent.army, mult);
			opponent.army_str -= opponent.army_str * mult;
			changeArmy(army, 1);
			army_str = 0;
			alive = false;
		}
	}
	//Changes the strength of each Warrior in the army
	void changeArmy(vector<Warrior*>& army, double mult) {
		for (Warrior* war : army) {
			war->changeStr(mult);
		}
	}
};

ostream& operator<<(ostream& os, const Noble& noble) {
	os << noble.name << " has an army of " << noble.army.size() << endl;
	for (const Warrior* war : noble.army) {
		os << *war;
	}
	return os;
}

int main() {
	Noble art("King Arthur");
	Noble lance("Lancelot du Lac");
	Noble jim("Jim");
	Noble linus("Linus Torvalds");
	Noble billie("Bill Gates");

	Warrior cheetah("Tarzan", 10);
	Warrior wizard("Merlin", 15);
	Warrior theGovernator("Conan", 12);
	Warrior nimoy("Spock", 15);
	Warrior lawless("Xena", 20);
	Warrior mrGreen("Hulk", 8);
	Warrior dylan("Hercules", 3);

	jim.hire(nimoy);
	lance.hire(theGovernator);
	art.hire(wizard);
	lance.hire(dylan);
	linus.hire(lawless);
	billie.hire(mrGreen);
	art.hire(cheetah);

	cout << "==========\n"
		<< "Status before all battles, etc.\n";
	cout << jim << endl;
	cout << lance << endl;
	cout << art << endl;
	cout << linus << endl;
	cout << billie << endl;
	cout << "==========\n";

	art.fire(cheetah);
	cout << art << endl;

	art.battle(lance);
	jim.battle(lance);
	linus.battle(billie);
	billie.battle(lance);

	cout << "==========\n"
		<< "Status after all battles, etc.\n";
	cout << jim << endl;
	cout << lance << endl;
	cout << art << endl;
	cout << linus << endl;
	cout << billie << endl;
	cout << "==========\n";
}