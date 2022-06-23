//Jiezhi Winston Zuo-yu; hw02.cpp
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct Warrior {
	int strength = 0;
	string name;
};

void battle(vector<Warrior>& warriors, ifstream& wartxt);
void status(vector<Warrior>& wars);
void createWarrior(vector<Warrior>& warriors, Warrior& warrior, ifstream& wartxt);

//reads file, checks commands, runs commands
int main() {
	ifstream wartxt("warriors.txt");
	if (!wartxt) {
		cerr << "Could not open the file. \n";
		exit(1);

	}
	vector<Warrior> warriors;
	Warrior warrior;
	string command;

	//reads first word of each line for command and runs it
	while (wartxt >> command) {
		if (command == "Warrior") {
			createWarrior(warriors, warrior, wartxt);
		}
		if (command == "Status") {
			status(warriors);
		}
		if (command == "Battle") {
			battle(warriors, wartxt);
		}
	}
	wartxt.close();
}

//adds a warrior to the vector of Warriors
void createWarrior(vector<Warrior>& warriors, Warrior& warrior, ifstream& wartxt) {
	string name;
	int strength;
	wartxt >> name;
	warrior.name = name;
	wartxt >> strength;
	warrior.strength = strength;
	warriors.push_back(warrior);
}

//prints out every warrior's name and strength
void status(vector<Warrior>& wars) {
	cout << "There are: " << wars.size() << " warriors" << endl;
	for (Warrior warout : wars) {
		cout << "Warrior: " << warout.name << ", strength: " << warout.strength << endl;
	}
}

//prints out which warrior is battling which warrior as well as the results of the battle
void battle(vector<Warrior>& warriors, ifstream& wartxt) {
	string war1;
	wartxt >> war1;
	string war2;
	wartxt >> war2;
	int found = 0;
	int war1pos;
	int war1str;
	int war2pos;
	int war2str;
	for (size_t warpos = 0; warpos < warriors.size(); ++warpos) {
		if (warriors[warpos].name == war1) {
			war1pos = warpos;
			war1str = warriors[warpos].strength;
			++found;
		}
		else if (warriors[warpos].name == war2) {
			war2pos = warpos;
			war2str = warriors[warpos].strength;
			++found;
		}
		//when both warriors have been found in vector of Warriors, stop looking and start battle
		if (found == 2) {
			cout << warriors[war1pos].name << " battles " << warriors[war2pos].name << endl;

			//accounts for scenarios where one or both warriors are already dead
			if (war1str == 0 && war2str == 0) {
				cout << "Oh, NO! They're both dead! Yuck!" << endl;
			}
			else if (war1str == 0) {
				cout << "He's dead, " << warriors[war2pos].name << endl;
			}
			else if (war2str == 0) {
				cout << "He's dead, " << warriors[war1pos].name << endl;
			}

			//same strength both warriors die
			else if (war1str == war2str) {
				warriors[war1pos].strength = 0;
				warriors[war2pos].strength = 0;
				cout << "Mutual Annihilation: " << warriors[war1pos].name << " and " << warriors[war2pos].name << " die at each other's hands" << endl;
			}

			//one warrior is stronger than the other
			else if (war1str > war2str) {
				warriors[war1pos].strength += -war2str;
				warriors[war2pos].strength = 0;
				cout << warriors[war1pos].name << " defeats " << warriors[war2pos].name << endl;
			}
			else {
				warriors[war2pos].strength += -war1str;
				warriors[war1pos].strength = 0;
				cout << warriors[war2pos].name << " defeats " << warriors[war1pos].name << endl;
			}
			break;
		}
	}
}
