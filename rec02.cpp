//Jiezhi Winston Zuo-yu
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

int main() {
	ifstream life("life.txt");
	if (!life) {
		cerr << "Could not open the file.\n";
		exit(1);
	}

	//making top border
	string aString;
	getline(life, aString);
	int lineSize = aString.size();
	string firstLine(lineSize + 2, '-');

	//creating the world with outside border
	vector<string> vectorofStrings;
	vectorofStrings.push_back(firstLine);
	string dash = "-";
	vectorofStrings.push_back(dash + aString + dash);
	vector<string> vectorOut;
	vectorOut.push_back(aString);
	while (getline(life, aString)) {
		vectorofStrings.push_back(dash + aString + dash);
		vectorOut.push_back(aString);
	}
	vectorofStrings.push_back(firstLine);
	
	for (int generation = 0; generation < 11; ++generation) {
		if (generation == 0) {
			cout << "Initial world" << endl;
			for (string x : vectorOut) {
				cout << x << endl;
			}
		}
		else {
			cout << "===========================" << endl << "Generation: " << generation << endl;
			for (string x : vectorOut) {
				cout << x << endl;
			}
		}
		for (int i = 1; i < (vectorofStrings.size() - 1); ++i) {
			for (int j = 1; j < (vectorofStrings[i].size() - 1); ++j) {
				int surralive = 0;
				if (vectorofStrings[i][j - 1] == '*') {
					++surralive;
				}
				if (vectorofStrings[i][j + 1] == '*') {
					++surralive;
				}
				if (vectorofStrings[i - 1][j - 1] == '*') {
					++surralive;
				}
				if (vectorofStrings[i - 1][j] == '*') {
					++surralive;
				}
				if (vectorofStrings[i - 1][j + 1] == '*') {
					++surralive;
				}
				if (vectorofStrings[i + 1][j - 1] == '*') {
					++surralive;
				}
				if (vectorofStrings[i + 1][j] == '*') {
					++surralive;
				}
				if (vectorofStrings[i + 1][j + 1] == '*') {
					++surralive;
				}
				if (vectorofStrings[i][j] == '-') {
					if (surralive == 3) {
						//vectorofStrings[i][j] = '*';
						vectorOut[i - 1][j - 1] = '*';
					}
				}
				else if (surralive != 3 && surralive != 2) {
					//vectorofStrings[i][j] = '-';
					vectorOut[i - 1][j - 1] = '-';
				}
				else if (surralive >= 5) {
					//vectorofStrings[i][j] = '-';
					vectorOut[i - 1][j - 1] = '-';
				}
			}
		}
		vectorofStrings.clear();
		vectorofStrings.push_back(firstLine);
		for (string x : vectorOut) {
			vectorofStrings.push_back(dash + x + dash);
		}
		vectorofStrings.push_back(firstLine);

	}
	cout << "====================" << endl;
	life.close();
}
