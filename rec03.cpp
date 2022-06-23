//Jiezhi Winston Zuo-yu
//rec03.cpp
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct Carbon {
	int carbons;
	int hydrogens;
	vector<string> names;
};

void openFile(ifstream& file);
void carbonsUnsorted(vector<Carbon>& carbons, ifstream& source);
void sortCarbons(vector<Carbon>& unsorted);
void printCarbons(const vector<Carbon>& sorted);

int main() {
	ifstream ogCarbons;
	vector<Carbon> carbonList;
	openFile(ogCarbons);
	carbonsUnsorted(carbonList, ogCarbons);
	sortCarbons(carbonList);
	printCarbons(carbonList);
	ogCarbons.close();
}

void openFile(ifstream& file) {
	string name;
	cout << "Please enter file name: ";
	cin >> name;
	file.open(name.c_str());
	while (!file) {
		file.clear();
		cerr << "Could not open the file. \n";
		cout << "Please enter a new file name: ";
		cin >> name;
		file.open(name);
	}
}

void carbonsUnsorted(vector<Carbon>& carbons, ifstream& source) {
	Carbon hydroCarb;
	string name;
	int carbonNum;
	int hydrogenNum;
	char blank;
	while (source >> name >> blank >> carbonNum >> blank >> hydrogenNum) {
		hydroCarb.carbons = carbonNum;
		hydroCarb.hydrogens = hydrogenNum;
		if (carbons.size() == 0) {
			hydroCarb.names.push_back(name);
			carbons.push_back(hydroCarb);
		}
		else {
			bool exists = false;
			for (size_t carbon = 0; carbon < carbons.size(); ++carbon) {
				if (carbons[carbon].carbons == carbonNum && carbons[carbon].hydrogens == hydrogenNum) {
					carbons[carbon].names.push_back(name);
					exists = true;
					break;
				}
			}
			if (exists == false) {
				hydroCarb.names.clear();
				hydroCarb.names.push_back(name);
				carbons.push_back(hydroCarb);
			}
		}
	}
}


void sortCarbons(vector<Carbon>& unsorted) {
	for (size_t carbon = 0; carbon < unsorted.size(); ++carbon) {
		for (size_t carbon2 = 0; carbon2 < (unsorted.size() - 1); ++carbon2) {
			if (unsorted[carbon2].carbons > unsorted[carbon2 + 1].carbons) {
					Carbon temp = unsorted[carbon2];
					unsorted[carbon2] = unsorted[carbon2 + 1];
					unsorted[carbon2 + 1] = temp;
			}
			if (unsorted[carbon2].carbons == unsorted[carbon2+1].carbons) {
				if (unsorted[carbon2].hydrogens > unsorted[carbon2 + 1].hydrogens) {
					Carbon temp = unsorted[carbon2];
					unsorted[carbon2] = unsorted[carbon2 + 1];
					unsorted[carbon2 + 1] = temp;
				}
			}
		}
	}	
}

void printCarbons(const vector<Carbon>& sorted) {
	for (const Carbon& x : sorted) {
		cout << 'C' << x.carbons << 'H' << x.hydrogens << ' ';
		for (const string& j : x.names) {
			cout << j << ' ';
		}
		cout << endl;
	}
}