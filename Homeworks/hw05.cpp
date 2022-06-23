/*
hw05.cpp
Jiezhi Winston Zuo-yu
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

//class and method prototypes
class Warrior;
class Noble;
void status(const vector<Noble*>& nobles, const vector<Warrior*>& warriors);
int nobExists(const vector<Noble*>& nobles, const string& nobName);
int warExists(const vector<Warrior*>& warriors, const string& warName);

//Warrior Class
class Warrior {
	friend ostream& operator<<(ostream& os, const Warrior& fighter);
private:
	string name;
	bool noble = false;
	double str;
public:
	//Warrior Constructor
	Warrior(const string& myName, double strength) : name(myName), str(strength) {}
	void changeNoble(const string& command) {
		if (command == "hire") {
			noble = true;
		}
		else if (command == "fire") {
			noble = false;
		}
	}

	//Warrior Getters
	const bool hasNoble() const {
		return noble;
	} 
	const string& getName() const {
		return name;
	}
	const double getStr() const {
		return str;
	}

	//Changes Warrior Strength
	void changeStr(double mult) {
		str -= str * mult;
	}
};

//Warrior output operator
ostream& operator<<(ostream& os, const Warrior& fighter) {
	os << "\t" << fighter.name << ": " << fighter.str << endl;
	return os;
}

class Noble {
	friend ostream& operator<<(ostream& os, const Noble& noble);
private:
	string name;
	double armyStr = 0;
	vector<Warrior*> army;
	bool alive = true;
public:
	//Noble Constructor
	Noble(const string& myName) : name(myName) {}
	const string& getName() {
		return name;
	}
	//Hires a Warrior
	const bool hireWar(Warrior& warrior) {
		if (warrior.hasNoble()) {
			cout << "Attempting to hire using employed warrior: "
				 << warrior.getName() << endl;
			return false;
		}
		warrior.changeNoble("hire");
		army.push_back(&warrior);
		armyStr += warrior.getStr();
		return true;
	}

	//Checks if Noble is alive
	const bool isAlive() const {
		return alive;
	}

	//Fires a Warrior
	const bool fireWar(Warrior& warrior) {
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
		cout << "You don't work for me anymore " << warrior.getName()
			 << "! -- " << name << "." << endl;
		army.pop_back();
		return true;
	}
	//Changes strength of each Warrior in the army
	void changeArmy(double mult) {
		for (Warrior* war : army) {
			war->changeStr(mult);
		}
	}
	//Battle Method
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
};

//Warrior output operator
ostream& operator<<(ostream& os, const Noble& noble) {
	os << noble.name << " has an army of " << noble.army.size() << endl;
	for (const Warrior* war : noble.army) {
		os << *war;
	}
	return os;
}

int main(){
	ifstream nwtxt("nobleWarriors.txt");
	if (!nwtxt) {
		cerr << "Could not open the file. \n";
		exit(1);
	}
	vector<Noble*> nobles;
	vector<Warrior*> warriors;
	string command;
	string name1;
	string name2;
	int strength;
	while (nwtxt >> command) {
		if (command == "Status") {
			cout << command << endl << "======" << endl;
			status(nobles, warriors);
		}
		else if (command == "Clear") {
			nobles.clear();
			warriors.clear();
		}
		//Creates a new Noble if it does not exist
		else if (command == "Noble") {
			nwtxt >> name1;
			int nob1 = nobExists(nobles, name1);
			if (!nob1 || nobles.size() == 0) {
				nobles.push_back(new Noble(name1));
			}
			else {
				cout << "Attempting to create a Noble that already exists: "
					 << name1 << endl;
			}
		}
		//Creates a new Warrior if it does not already exist
		else if (command == "Warrior") {
			nwtxt >> name1;
			nwtxt >> strength;
			int war = warExists(warriors, name1);
			if (!war || warriors.size() == 0) {
				warriors.push_back(new Warrior(name1, strength));
			}
			else {
				cout << "Attempting to create a Warrior that already exists: "
					 << name1 << endl;
			}
		}
		//Calls Battle method if both Nobles exist
		else if (command == "Battle") {
			nwtxt >> name1;
			int nob1 = nobExists(nobles, name1);
			nwtxt >> name2;
			int nob2 = nobExists(nobles, name2);
			if (nobles.size() == 0) {
				cout << "Attempting to battle using unknowns nobles: "
					 << name1 << " and " << name2 << endl;
			}
			else if (!nob1 || !nob2) {
				cout << "Attempting to battle using unknown noble";
				if (!nob1 && !nob2) {
					cout << "s: " << name1 << " and " << name2 << endl;
				}
				else if (!nob1) {
					cout << ": " << name1 << endl;
				}
				else {
					cout << ": " << name2 << endl;
				}
			}
			else {
				nobles[nob1-1]->battle(*nobles[nob2-1]);
			}
		}
		//Calls method to Hire warrior if the Warrior and Noble exists
		else if (command == "Hire") {
			nwtxt >> name1;
			int nob1 = nobExists(nobles, name1);
			nwtxt >> name2;
			int war = warExists(warriors, name2);
			if (!nob1) {
				cout << "Attempting to hire using unknown noble: " << name1 << endl;
			}
			else if (!nobles[nob1 - 1]->isAlive()) {
				cout << "Attempting to hire using dead noble: "
					<< nobles[nob1 - 1]->getName() << endl;
			}
			if (!war) {
				cout << "Attempting to hire using unknown warrior: " << name2 << endl;
			}
			if (nob1 && war) {
				nobles[nob1 - 1]->hireWar(*warriors[war - 1]);
			}
		}
		//Calls method to fire Warrior if the Warrior and Noble exists
		else if (command == "Fire") {
			nwtxt >> name1;
			int nob1 = nobExists(nobles, name1);
			nwtxt >> name2;
			int war = warExists(warriors, name2);
			if (!nob1) {
				cout << "Attempting to fire using unknown noble: " << name1 << endl;
			}
			else if (!nobles[nob1 - 1]->isAlive()) {
				cout << "Attempting to fire using dead noble: "
					<< nobles[nob1 - 1]->getName() << endl;
			}
			if (!war) {
				cout << "Attempting to fire using unknown warrior: " << name2 << endl;
			}
			if (nob1 && war) {
				nobles[nob1 - 1]->fireWar(*warriors[war - 1]);
			}
		}
	}
	nwtxt.close();
}

//Prints all Warriors and Nobles
void status(const vector<Noble*>& nobles, const vector<Warrior*>& warriors) {
	cout << "Nobles: " << endl;
	if (nobles.size() == 0) {
		cout << "NONE" << endl;
	}
	else {
		for (const Noble* noble : nobles) {
			cout << *noble;
		}
	}
	cout << endl << "Unemployed Warriors:" << endl;
	bool found = false;
	for (Warrior* warrior : warriors) {
		if (!warrior->hasNoble()) {
			cout << *warrior;
			if (!found) {
				found = true;
			}
		}
	}
	if (!found) {
		cout << "NONE" << endl;
	}
}

//Checks if a Noble exists
int nobExists(const vector<Noble*>& nobles, const string& nobName) {
	for (size_t i = 0; i < nobles.size(); ++i) {
		if (nobles[i]->getName() == nobName) {
			return i+1;
		}
	}
	return 0;
}

//Checks if a Warrior exists in a given army
int warExists(const vector<Warrior*>& warriors, const string& warName) {
	for (size_t i = 0; i < warriors.size(); ++i) {
		if (warriors[i]->getName() == warName) {
			return i+1;
		}
	}
	return 0;
}
