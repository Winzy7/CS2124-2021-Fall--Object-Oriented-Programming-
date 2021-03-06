/*
  Jiezhi Winston Zuo-yu
  rec06.cpp
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class TimeSlot {
    friend ostream& operator<<(ostream& os, const TimeSlot& timeS);
private:
    string day;
    int time;
public:
    TimeSlot(const string& date, int timeofday): day(date), time(timeofday) {}
};

ostream& operator<<(ostream& os, const TimeSlot& timeS) {
    os << "Time Slot: [Day: Tuesday, Start time: ";
    if (timeS.time <= 12) {
        os << timeS.time << "am]";
    }
    else {
        os << timeS.time - 12 << "pm]";
    }
    return os;
}

class Student {
    friend ostream& operator<<(ostream&, const Student& student);
private:
    string name;
    vector<int> grades;
public:
    Student(const string& studentName) : name(studentName), grades(14,-1) {}
    const string& getName() {
        return name;
    }
    void editGrades(int grade, int week) {
        grades[week - 1] = grade;
        
    }
};

ostream& operator<<(ostream& os, const Student& student) {
    os << "Name: " << student.name << ", Grades: ";
    for (int p : student.grades) {
        os << p << " ";
    }
    return os;
}

class Section {
    friend ostream& operator<<(ostream& os, const Section& sec);
private:
    string secName;
    vector<Student*> vectorOfPointers;
    TimeSlot info;
public:
    Section(const string& section, const string& date, int timeofday) : secName(section), info(date, timeofday) {}
    void addStudent(const string& name) {
        Student* student = new Student(name);
        vectorOfPointers.push_back(student);
    }
    void changeGrade(const string& studentName, int grade, int week) {
        for (size_t i = 0; i < vectorOfPointers.size(); ++i) {
            if (vectorOfPointers[i]->getName() == studentName) {
                vectorOfPointers[i]->editGrades(grade, week);
                return;
            }
        }
    }
    ~Section() {
        cout << "Section " << secName << " is being deleted" << endl;
        for (Student* p : vectorOfPointers) {
            cout << "Deleting " << p->getName() << endl;
            delete p;
        }
    }
    Section(const Section& anotherSection) : 
        secName(anotherSection.secName), info(anotherSection.info) {
        for (size_t i = 0; i < anotherSection.vectorOfPointers.size(); ++i) {
            vectorOfPointers.push_back(new Student(*anotherSection.vectorOfPointers[i]));
        }
    }
};

ostream& operator<<(ostream& os, const Section& sec) {
    os << "Section: " << sec.secName << ", " << sec.info << ", Students:";
    if (sec.vectorOfPointers.size() == 0) {
        os << " None" << endl;
    }
    else {
        os << endl;
        for (const Student* p : sec.vectorOfPointers) {
            os << *p << endl;
        }
    }
    return os;
}

class LabWorker {
    friend ostream& operator<<(ostream& os, const LabWorker& worker);
private:
    string name;
    Section* section;
public:
    LabWorker(const string& workerName) : name(workerName), section(nullptr) {}
    void addSection(Section& sec) {
        if (!section) {
            section = &sec;
        }
    }
    void addGrade(const string& name, int grade, int week) {
        if (section){
            section->changeGrade(name, grade, week);
        }
    }
};

ostream& operator<<(ostream& os, const LabWorker& worker) {
    if (worker.section == nullptr) {
        os << worker.name << " does not have a section" << endl;
    }
    else {
        os << worker.name << " has " << *worker.section << endl;
    }
    return os;
}
// Test code
void doNothing(Section sec) { cout << sec << endl; }

int main() {

    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    cout << secA2 << endl;

    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    cout << secA2 << endl;

    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe( "Moe" );
    cout << moe << endl;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection( secA2 );
    cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
     secB3.addStudent("Thorin");
     secB3.addStudent("Dwalin");
     secB3.addStudent("Balin");
     secB3.addStudent("Kili");
     secB3.addStudent("Fili");
     secB3.addStudent("Dori");
     secB3.addStudent("Nori");
     secB3.addStudent("Ori");
     secB3.addStudent("Oin");
     secB3.addStudent("Gloin");
     secB3.addStudent("Bifur");
     secB3.addStudent("Bofur");
     secB3.addStudent("Bombur");
     jane.addSection( secB3 );
     cout << jane << endl;

    cout << "\nTest 6: Adding some grades for week one\n";
     moe.addGrade("John", 17, 1);  
     moe.addGrade("Paul", 19, 1);  
     moe.addGrade("George", 16, 1);  
     moe.addGrade("Ringo", 7, 1);  
     cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);  
    moe.addGrade("Paul", 20, 3);  
    moe.addGrade("Ringo", 0, 3);  
    moe.addGrade("George", 16, 3);  
    cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
        << "those students (or rather their records?)\n";

    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
        << "then make sure the following call works:\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n";

} // main
