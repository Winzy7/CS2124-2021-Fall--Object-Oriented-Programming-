// rec01-start.cpp
// 2124 21S


#include <iostream>    // Tasks 3, 4, 5 and 6
#include <fstream>     // Task 4, 5 and 6
#include <string>      // Task 5
using namespace std;

int main() {
    // Task 3
    cout << "Task 3\n========\n";
    // Put code for Task 3 here
    cout << "Yay C++!!!\n";

    // Task 4
    cout << "Task 4\n========\n";
    // Put code for Task 4 here
    ifstream numbers("integers.txt");
    if (!numbers) {
        cerr << "Could not open the file.\n";
        exit(1);
    }
    int anInt;
    int sol = 0;
    while (numbers >> anInt) {
        sol += anInt;
    }
    cout << sol << "\n";
    numbers.close();


    // Task 5
    cout << "Task 5\n========\n";
    // Put code for Task 5 here
    ifstream text("text.txt");
    if (!text) {
        cerr << "Could not open the file.\n";
        exit(1);
    }
    string aString;
    while (text >> aString) {
        cout << aString << endl;
    }
    text.close();
    // Task 6
    cout << "Task 6\n========\n";
    // Put code for Task 6 here
    ifstream mixed("mixed.txt");
    if (!mixed) {
        cerr << "Could not open the file.\n";
        exit(1);
    }
    int randomInt;
    int sixsol = 0;
    while (mixed >> randomInt) {
        sixsol += randomInt;
    }
    cout << sixsol;
    mixed.close();
}
