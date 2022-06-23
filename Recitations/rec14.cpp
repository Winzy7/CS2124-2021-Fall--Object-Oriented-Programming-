/*
 * Jiezhi Winston Zuo-yu
 * rec14.cpp
 */
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <fstream>
#include <set>
#include <map>
using namespace std;


//Task 9:
void printList(const list<int>& toPrint) {
    list<int>::const_iterator p;
    for (p = toPrint.begin(); p != toPrint.end(); ++p) {
        cout << *p << " ";
    }
    cout << endl;
}

//Task 10:
void printListRanked(const list<int>& toPrint) {
    for (int x : toPrint) {
        cout << x << " ";
    }
    cout << endl;
}

//Task 11:
void printListAuto(const list<int>& toPrint) {
    for (auto p = toPrint.begin(); p != toPrint.end(); ++p) {
        cout << *p << " ";
    }
    cout << endl;
}

//Task 12:
list<int>::const_iterator findList(const list<int>& searchIn, int target) {
    for (list<int>::const_iterator p = searchIn.begin(); p != searchIn.end(); ++p) {
        if (*p == target) {
            return p;
        }
    }
    return searchIn.end();
}

//Task 13:
auto findListAuto(const list<int>& searchIn, int target) {
    for (auto p = searchIn.begin(); p != searchIn.end(); ++p) {
        if (*p == target) {
            return p;
        }
    }
    return searchIn.end();
}

//Task 15:
bool even(const int number) {
    if (number % 2 == 0) {
        return true;
    }
    return false;
}

//Task 16:
class myClass {
public:
    bool operator()(int number){
        return even(number);
    }
};

//Task 19:
list<int>::const_iterator ourFind(const list<int>& searchIn, int target) {
    cout << "outFind: " << target << endl;
    for (list<int>::const_iterator p = searchIn.begin(); p != searchIn.end(); ++p) {
        if (*p == target) {
            return p;
        }
    }
    return searchIn.end();
}

//Task 20:
template <typename T, typename U, typename V>
T ourFind(const U& search, V target) {
    cout << "ourFind with Template: " << target << endl;
    for (T p = search.begin(); p != search.end(); ++p) {
        if (*p == target) {
            return p;
        }
    }
    return search.end();
}

int main() {
    //Task 1:
    vector<int> vecOfInts{1, 3, 2, 4};
    for (int x : vecOfInts) {
        cout << x << " ";
    }
    cout << endl;

    //Task 2:
    list<int> listOfInts(vecOfInts.begin(), vecOfInts.end());
    for (int x : listOfInts) {
        cout << x << " ";
    }
    cout << endl;

    //Task 3:
    sort(vecOfInts.begin(), vecOfInts.end());
    for (int x : vecOfInts) {
        cout << x << " ";
    }
    cout << endl;
    for (int x : listOfInts) {
        cout << x << " ";
    }
    cout << endl;

    //Task 4:
    for (size_t i = 0; i < vecOfInts.size(); ++i) {
        if (i % 2 == 0) {
            cout << vecOfInts[i] << " ";
        }
    }
    cout << endl;

    //Task 5:
    /*
    for (size_t i = 0; i < listOfInts.size(); ++i) {
        if (i % 2 == 0) {
            cout << listOfInts[i] << " ";
        }
    }
    cout << endl;
     */

    //Task 6:
    vector<int>:: iterator p;
    for (p = vecOfInts.begin(); p != vecOfInts.end(); p += 2) {
        cout << *p << " ";
    }
    cout << endl;

    //Task 7:
    list<int>:: iterator q;
    for (q = listOfInts.begin(); q != listOfInts.end(); ++++q) {
        cout << *q << " ";
    }
    cout << endl;

    //Task 8:
    listOfInts.sort();
    for (int x : listOfInts) {
        cout << x << " ";
    }
    cout << endl;

    //Task 9:
    printList(listOfInts);

    //Task 10:
    printListRanked(listOfInts);

    //Task 11:
    printListAuto(listOfInts);

    //Task 12:
    if (findList(listOfInts, 4) != listOfInts.end()) cout << "Found" << endl;
    else cout << "Not Found" << endl;

    if (findList(listOfInts,4) != listOfInts.end()) cout << "Found" << endl;
    else cout << "Not Found" << endl;
    //cout << *findList(listOfInts, 5) << endl;

    //Task 13:
    if (findListAuto(listOfInts,4) != listOfInts.end()) cout << "Found" << endl;
    else cout << "Not Found" << endl;
    //cout << *findListAuto(listOfInts,5) << endl;

    //Task 14:
    if (find(listOfInts.begin(), listOfInts.end(), 3) != listOfInts.end()) cout << "Found" << endl;
    else cout << "Not Found" << endl;

    //Task 15:
    if (find_if(listOfInts.begin(), listOfInts.end(), even) != listOfInts.end()) cout << "Found" << endl;
    else cout << "Not Found" << endl;

    //Task 16:
    if (find_if(listOfInts.begin(), listOfInts.end(), myClass()) != listOfInts.end()) cout << "Found" << endl;
    else cout << "Not Found" << endl;

    //Task 17:
    [] { cout << "Hello Lambda!" << endl; }();
    [] (int a, int b) {cout << a + b << endl; } (4, 5);
    int result2 = [] (int a, int b) -> int { return a + b; } (4, 5);
    cout << "the result is: " << result2 << endl;

    //Task 18:
    int* array = new int[4];
    copy(vecOfInts.begin(), vecOfInts.end(), array);
    for (int i = 0; i < 4; ++i) {
        cout << array[i] << " ";
    }
    cout << endl;
    cout << *find(array, array+4, 3) << endl;
    delete [] array;

    //Task 19:
    cout << *ourFind(listOfInts,4) << endl;
    //cout << *myFind(listOfInts,5) << endl;

    //Task 20:
    //cout << *ourFind(vecOfInts, 4) << endl;
    cout << *ourFind(listOfInts,4) << endl;
    //cout << *ourFind(listOfInts,5) << endl;

    //Task 21:
    ifstream myFile("pooh-nopunc.txt");
    if (!myFile) {
        cerr << "file wrong.\n";
        exit(1);
    }
    vector<string> words;
    string x;
    while (myFile >> x) {
        if (find(words.begin(), words.end(), x) == words.end()) {
            words.push_back(x);
        }
    }
    cout << "Vector Size: " << words.size() << endl;
    cout << "Vector Contents: " << endl;
    for (string x : words) {
        cout << x << " ";
    }
    cout << endl;
    myFile.close();

    //Task 22:
    myFile.open("pooh-nopunc.txt");
    if (!myFile) {
        cerr << "file wrong.\n";
        exit(1);
    }
    set<string> wordsSet;
    while (myFile >> x) {
        wordsSet.insert(x);
    }
    cout << "Set Size: " << wordsSet.size() << endl;
    cout << "Set Contents: " << endl;
    for (string b : wordsSet) {
        cout << b << " ";
    }
    myFile.close();

    //Task 23:
    myFile.open("pooh-nopunc.txt");
    if (!myFile) {
        cerr << "file wrong.\n";
        exit(1);
    }
    map<string, vector<int>> wordMap;
    int pos = 0;
    cout << wordMap.size();
    while (myFile >> x) {
        wordMap[x].push_back(pos);
        ++pos;
    }
    for (auto p : wordMap) {
        cout << p.first << " position(s): ";
        for (int r : p.second) {
            cout << r << " ";
        }
        cout << endl;
    }
    myFile.close();
}
