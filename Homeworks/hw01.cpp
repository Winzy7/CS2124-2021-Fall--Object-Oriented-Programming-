//Jiezhi Winston Zuo-yu; hw1.cpp; decrypts a file encrypted by the Caesar cypher
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

char charDecrypt(char letter, const int shift);
void stringDecrypt(string& someString, const int shift);

//prints out the decrypted file in reverse
int main() {

	//reads file, finds decryption integer, stops reading right before encrypted text
	ifstream message("encrypted.txt");
	if (!message) {
		cerr << "Could not open the file.\n";
		exit(1);
	}
	int shift;
	message >> shift;
	string line;
	getline(message, line);
	vector<string> reverseResult;

	//stores each decrypted line in a vector
	while (getline(message, line)) {
		stringDecrypt(line, shift);
		reverseResult.push_back(line);
	}

	//prints out the vector in reverse
	for (size_t linesLeft = reverseResult.size(); linesLeft > 0; --i) {
		cout << reverseResult[linesLeft - 1] << endl;
	}

	message.close();
}

//takes a chracter and integer; changes the character depending on the integer
char charDecrypt(char letter, const int shift) {

	//capital letters unchanged and returned instantly
	if (letter >= 'a' && letter <= 'z') {
		int repeat = 'z' - 'a' + 1;
		int finalShift = shift % repeat;
		int toZ = 'z' - letter;
		int toA = letter - 'a';

		//takes an integer too big, sets character to 'a' or 'z', decreases integer
		if (toA < finalShift) {
			letter = 'z';
			finalShift += -(toA + 1);
		}

		else if (finalShift < -toZ) {
			letter = 'a';
			finalShift += toZ + 1;
		}

		letter += -finalShift;
		return letter;
	}

	return letter;
}

//takes a string and an integer, decrypts the string by integer amount of letters
void stringDecrypt(string& someString, const int shift) {

	//changes every character to decrypted character
	for (int charTrack = 0; charTrack < someString.length(); ++i) {
		someString[i] = charDecrypt(someString[charTrack], shift);
	}

}



