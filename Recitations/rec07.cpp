/*
  rec07.cpp
  Jiezhi Winston Zuo-yu
 */

#include <string>
#include <iostream>
using namespace std;

// 
// Position class
// 
class Position {
    friend ostream& operator<<(ostream& os, const Position& rhs) {
        os << '[' << rhs.title << ',' << rhs.salary << ']';
        return os;
    }
public:
    Position(const string& aTitle, double aSalary)
        : title(aTitle), salary(aSalary) {}
    const string& getTitle() const { return title; }
    double getSalary() const { return salary; }
    void changeSalaryTo(double d) { salary = d; }
private:
    string title;
    double salary;
}; // class Position


// 
// Directory class
// 
class Directory {
    // 
    // nested Entry class
    // 
    class Entry {
        friend ostream& operator<<(ostream& os, const Entry& rhs) {
            os << rhs.name << ' ' << rhs.room
                << ' ' << rhs.phone << ", " << *rhs.pos;
            return os;
        }
    public:
        Entry(const string& name, unsigned room, unsigned phone, Position& position)
            : name(name), room(room), phone(phone), pos(&position) {
        }
        const string& getName() const { return name; }
        unsigned getPhone() const { return phone; }
    private:
        string name;
        unsigned room;
        unsigned phone;
        Position* pos;
    }; // class Entry


    // Overload Directory's output operator
    // ...
    friend ostream& operator<<(ostream& os, const Directory& rhs) {
        for (size_t pos = 0; pos < rhs.size; ++pos) {
            os << *rhs.entries[pos] << endl;
        }
        return os;
    }

public:
    // Of course the first function you need to write for this (or
    // any) class is...
    // ???
    // ...
    Directory(const string& company)
        : company(company), size(0), capacity(0), entries(new Entry*[0]) {
    }

    int operator[](const string& name) const {
        for (size_t pos = 0; pos < size; ++pos) {
            if (entries[pos]->getName() == name) {
                return entries[pos]->getPhone();
            }
        }

        return 99999;
    }

    // We'll get you started with the add method, but obviously you
    // have a lot of work to do here.
    //Destructor
    ~Directory() {
        cout << "Destructor" << endl;
        for (size_t pos = 0; pos < size; ++pos) {
            delete entries[pos];
        }
        delete[] entries;
    }
    //Copy contructor
    Directory(const Directory& rhs) {
        cout << "Copy Constructor" << endl;
        size = rhs.size;
        capacity = rhs.capacity;
        company = rhs.company;
        entries = new Entry * [rhs.capacity];
        for (size_t pos = 0; pos < rhs.size; ++pos) {
            entries[pos] = new Entry( *(rhs.entries[pos]));
        }
    }
    //Assignment operator
    Directory& operator=(const Directory& rhs) {
        cout << "Assignment  Operator" << endl;
        if (this != &rhs) {
            for (size_t pos = 0; pos < size; ++pos) {
                delete entries[pos];
            }
            delete[] entries;
            entries = new Entry * [rhs.capacity];
            for (size_t pos = 0; pos < rhs.size; ++pos) {
                entries[pos] = new Entry(*(rhs.entries[pos]));
            }
            size = rhs.size;
            capacity = rhs.capacity;
            company = rhs.company;
        }
        return *this;
    }
    void add(const string& name, unsigned room, unsigned ph, Position& pos) {
        if (size == capacity) {

            // something is missing!!!  Add it!
            Entry** oldEntries = entries;
            entries = new Entry* [2*capacity];
            capacity *= 2;
            for (size_t pos = 0; pos < size; ++pos) {
                entries[pos] = oldEntries[pos];
            }
            delete[] oldEntries;
        } // if
        if (capacity == 0) {
            ++capacity;
            entries = new Entry * [capacity];
        }
        entries[size] = new Entry(name, room, ph, pos);
        ++size;
    } // add

private:
    Entry** entries; // Notice the type!!! Pointer to Entry pointers.
    size_t size;
    size_t capacity;
    string company;
}; // class Directory


void doNothing(Directory dir) {
    // You need to overload the Directory output operator before
    // uncommenting the next line.

    cout << dir << endl;
}

int main() {

    // Note that the Postion objects are NOT on the heap.
    Position boss("Boss", 3141.59);
    Position pointyHair("Pointy Hair", 271.83);
    Position techie("Techie", 14142.13);
    Position peon("Peonissimo", 34.79);

    
    // Create a Directory
    Directory d("HAL");
    d.add("Marilyn", 123, 4567, boss);
    cout << d << endl;

    Directory d2 = d;	// What function is being used??
    d2.add("Gallagher", 111, 2222, techie);
    d2.add("Carmack", 314, 1592, techie);
    cout << d << endl;

    cout << "Calling doNothing\n";
    doNothing(d2);
    cout << "Back from doNothing\n";
    cout << d2 << endl;

    //// Should display 1592
    cout << d2["Carmack"] << endl;

    Directory d3("IBM");
    d3.add("Torvalds", 628, 3185, techie);
    d3.add("Ritchie", 123, 5813, techie);


    d2 = d3;
    //// Should display 5813
    cout << d2["Ritchie"] << endl;

    cout << d2 << endl;
    
} // main
