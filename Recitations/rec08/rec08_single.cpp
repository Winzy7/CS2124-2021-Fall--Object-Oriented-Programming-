/*
 * Jiezhi Winston Zou-yu
 * rec08_single.cpp
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student;

class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);
public:
    // Course methods needed by Registrar
    Course(const string& courseName);
    const string& getName() const;
    bool addStudent(Student* student);
    void removeStudentsFromCourse(Student* student);
    size_t findStudent(const Student* student) const;
    size_t studentsSize() const;
private:
    string name;
    vector<Student*> students;
};

class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);
public:
    // Student methods needed by Registrar
    Student(const string& myName);
    const string& getName() const;
    bool addCourse(Course* course);
    size_t findCourse(const Course* course);
    size_t coursesSize() const;
    // Student method needed by Course
    void removedFromCourse(Course* course);

private:
    string name;
    vector<Course*> courses;
};

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    Registrar();
    bool addCourse(const string& courseName);
    bool addStudent(const string& studentName);
    bool enrollStudentInCourse(const string& studentName,
                               const string& courseName);
    bool cancelCourse(const string& courseName);
    void purge();

private:
    size_t findStudent(const string& studentName) const;
    size_t findCourse(const string& courseName) const;

    vector<Course*> courses;
    vector<Student*> students;
};

int main() {

    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;

    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;

    /*
    // [OPTIONAL - do later if time]
    cout << "ChangeStudentName FritzTheCat MightyMouse\n";
    registrar.changeStudentName("FritzTheCat", "MightyMouse");
    cout << registrar << endl;

    cout << "DropStudentFromCourse MightyMouse CS101.001\n";
    registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
    cout << registrar << endl;

    cout << "RemoveStudent FritzTheCat\n";
    registrar.removeStudent("FritzTheCat");
    cout << registrar << endl;
    */

    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
}

ostream& operator<<(ostream& os, const Course& rhs){
    os << rhs.getName() << ": ";
    if (rhs.students.size() == 0) {
        os << "No Students";
    }
    for (Student* student: rhs.students) {
        os << student->getName() << " ";
    }
    os << endl;
    return os;
}

Course::Course(const string& courseName) : name(courseName) {}

const string& Course::getName() const {
    return name;
}

void Course::removeStudentsFromCourse(Student *student) {
    size_t studentPos = findStudent(student);
    if (studentPos != (students.size()+1)) {
        student->removedFromCourse(this);
        for (size_t i = studentPos; i < students.size()-1; ++i) {
            students[studentPos] = students[studentPos + 1];
        }
        students.pop_back();
    }
}

bool Course::addStudent(Student* student) {
    for (Student* x : students) {
        if (x->getName() == student->getName()) {
            return false;
        }
    }
    students.push_back(student);
    return true;
}

size_t Course::studentsSize() const {
    return students.size();
}

size_t Course::findStudent(const Student *student) const {
    for (size_t i = 0; i < students.size(); ++i) {
        if (students[i]->getName() == student->getName()){
            return i;
        }
    }
    return students.size()+1;
}

Student::Student(const string& myName) : name(myName) {}

const string& Student::getName() const {
    return name;
}

size_t Student::coursesSize() const {
    return courses.size();
}

ostream& operator<<(ostream& os, const Student& rhs) {
    os << rhs.name << ": ";
    if (rhs.courses.size() == 0) {
        os << "No Courses" ;
    }
    for (Course* course : rhs.courses) {
        os << course->getName() << " ";
    }
    os << endl;
    return os;
}

size_t Student::findCourse(const Course *course) {
    for (size_t i = 0; i < courses.size(); ++i) {
        if (courses[i]->getName() == course->getName()){
            return i;
        }
    }
    return courses.size()+1;
}

bool Student::addCourse(Course* course) {
    for (Course* classes : courses) {
        if (classes->getName() == course->getName()){
            return false;
        }
    }
    courses.push_back(course);
    return true;
}

void Student::removedFromCourse(Course* course){
    size_t coursePos = findCourse(course);
    if (coursePos != courses.size()+1) {
        for (size_t i = coursePos; i < courses.size()-1; ++i){
            courses[i] = courses[i+1];
        }
        courses.pop_back();
    }
}

ostream& operator<<(ostream& os, const Registrar& rhs) {
    os << "Registrar's Report" << endl;
    os << "Courses: " << endl;
    for (Course* course : rhs.courses){
        os << *course;
    }
    os << "Students: " << endl;
    for (Student* student : rhs.students) {
        os << *student;
    }
    return os;
}

Registrar::Registrar() {}

bool Registrar::addCourse(const string & courseName) {
    for (Course* course : courses) {
        if (course->getName() == courseName) {
            return false;
        }
    }
    courses.push_back(new Course(courseName));
    return true;
}

bool Registrar::addStudent(const string & studentName) {
    for (Student* student: students) {
        if (student->getName() == studentName) {
            return true;
        }
    }
    students.push_back(new Student(studentName));
    return false;
}

bool Registrar::enrollStudentInCourse(const string &studentName, const string &courseName) {
    size_t studentPos = findStudent(studentName);
    size_t coursePos = findCourse(courseName);
    if ((studentPos != (students.size()+1)) && (coursePos != (courses.size()+1))) {

        if (courses[coursePos]->findStudent(students[studentPos])
        ==(courses[coursePos]->studentsSize()+1)){
            if (students[studentPos]->findCourse(courses[coursePos])
            ==(students[studentPos]->coursesSize()+1)) {
                courses[coursePos]->addStudent(students[studentPos]);
                students[studentPos]->addCourse(courses[coursePos]);
                return true;
            }
        }
    }
    return false;
}

size_t Registrar::findStudent(const string & studentName) const {
    for (size_t i = 0; i < students.size(); ++i) {
        if (students[i]->getName() == studentName) {
            return i;
        }
    }
    return students.size()+1;
}

size_t Registrar::findCourse(const string & courseName) const {
    for (size_t i = 0; i < courses.size(); ++i) {
        if (courses[i]->getName() == courseName) {
            return i;
        }
    }
    return courses.size()+1;
}

bool Registrar::cancelCourse(const string &courseName) {
    size_t coursePos = findCourse(courseName);
    if (coursePos != courses.size()+1) {
        for (Student* student: students) {
            courses[coursePos]->removeStudentsFromCourse(student);
        }
        for (size_t k = coursePos; k < courses.size()-1; ++k) {
            courses[coursePos] = courses[coursePos+1];
        }
        delete courses[courses.size()-1];
        courses.pop_back();
        return true;
    }
    return false;
}

void Registrar::purge() {
    for (Course* course: courses) {
        delete course;
    }
    for (Student* student: students) {
        delete student;
    }
    courses.clear();
    students.clear();
}
