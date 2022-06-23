//Jiezhi Winston Zuo-yu; hw03.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;



//creates the class Warrior and takes in the Warrior's name as well as its weapon's name and strength
class Warrior {
	friend ostream& operator << (ostream& os, const Warrior& fighter);
private:
	//creates the class Weapon and takes in the weapon's name and strength
	class Weapon {
		friend ostream& operator << (ostream& os, const Weapon& weapon);
	public:
		Weapon(const string& n, int s) : name(n), strength(s) {}
		const string& getName() const {
			return name;
		}
		int getStr() const {
			return strength;
		}
		//minusStr method changes strength of weapon; used in battle 
		void minusStr(int change) {
			strength -= change;
			if (strength < 0) {
				strength = 0;
			}
		}
	private:
		string name;
		int strength;
	};
	string name;
	Weapon weapon;
	friend ostream& operator << (ostream& os, const Warrior::Weapon& weapon);

public:
	Warrior(const string& n, const string& w, int s) : name(n), weapon(w, s) {}
	void battle(Warrior& challenger) {
		cout << name << " battles " << challenger.name << endl;
		if (weapon.getStr() == 0 && challenger.weapon.getStr() == 0) {
			cout << "Oh, NO! They're both dead! Yuck!" << endl;
		}
		else if (weapon.getStr() == 0) {
			cout << "He's dead, " << challenger.name << endl;
		}
		else if (challenger.weapon.getStr() == 0) {
			cout << "He's dead, " << name << endl;
		}
		else if (weapon.getStr() == challenger.weapon.getStr()) {
			cout << "Mutual Annihilation: " << name << " and " << challenger.name << " die at each other's hands" << endl;
		}
		else if (weapon.getStr() > challenger.weapon.getStr()) {
			cout << name << " defeats " << challenger.name << endl;
		}
		else {
			cout << challenger.name << " defeats " << name << endl;
		}
		int strCopy = weapon.getStr();
		weapon.minusStr(challenger.weapon.getStr());
		challenger.weapon.minusStr(strCopy);
	}

	const string& getName() const {
		return name;
	}
};

//output operator for class weapon
ostream& operator << (ostream& os, const Warrior::Weapon& weapon) {
	os << weapon.name << ", " << weapon.strength;
	return os;
}

//output operator for class Warrior
ostream& operator << (ostream& os, const Warrior & person) {
	os << "Warrior: " << person.name << ", weapon: " << person.weapon;
	return os;
}



//function operators
void createWarrior(vector<Warrior>& warriors, ifstream& wartxt);
void battle(vector<Warrior>& warriors, ifstream& wartxt);

//main opens file and reads in commands for the Warriors
int main() {
	ifstream info("warriors.txt");
	if (!info) {
		cerr << "Could not open the file .\n";
		exit(1);
	}
	vector<Warrior> warriors;
	string command;

	//depending on command, makes Warrior, shows Status, or starts Battle
	while (info >> command) {
		if (command == "Warrior") {
			createWarrior(warriors, info);
		}
		if (command == "Status") {
			cout << "There are: " << warriors.size() << " warriors" << endl;
			for (const Warrior& warrior : warriors) {

				cout << warrior << endl;
			}
		}
		if (command == "Battle") {
			battle(warriors, info);
		}
	}
	info.close();
}

//reads in appropriate fields from file and uses them to create a Warrior
void createWarrior(vector<Warrior>& warriors, ifstream& wartxt) {
	string name;
	string weapon;
	int strength;
	wartxt >> name;
	wartxt >> weapon;
	wartxt >> strength;
	Warrior warrior{ name, weapon, strength};
	warriors.emplace_back(warrior);
}

//reads in Warrior names from file and calls the battle method on them
void battle(vector<Warrior>& warriors, ifstream& wartxt) {
	string name;
	string name2;
	int war1;
	int war2;
	wartxt >> name;
	wartxt >> name2;
	int found = 0;

	//find both Warriors in the vector of Warriors and calls battle method on them
	for (size_t warpos = 0; warpos < warriors.size(); ++warpos) {
		if (warriors[warpos].getName() == name) {
			war1 = warpos;
			++found;
		}
		else if (warriors[warpos].getName() == name2) {
			war2 = warpos;
			++found;
		}
		if (found == 2) {
			warriors[war1].battle(warriors[war2]);
			break;
		}
	}
}
