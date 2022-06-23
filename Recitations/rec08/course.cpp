/*
 * Jiezhi Winston Zuo-yu
 * course.cpp
 */

#include "course.h"
#include "student.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace BrooklynPoly {

    ostream &operator<<(ostream &os, const Course &rhs) {
        os << rhs.getName() << ": ";
        if (rhs.students.size() == 0) {
            os << "No Students";
        }
        for (Student *student: rhs.students) {
            os << student->getName() << " ";
        }
        os << endl;
        return os;
    }

    Course::Course(const string &courseName) : name(courseName) {}

    const string &Course::getName() const {
        return name;
    }

    void Course::removeStudentsFromCourse(Student *student) {
        size_t studentPos = findStudent(student);
        if (studentPos != (students.size() + 1)) {
            student->removedFromCourse(this);
            for (size_t i = studentPos; i < students.size() - 1; ++i) {
                students[studentPos] = students[studentPos + 1];
            }
            students.pop_back();
        }
    }

    bool Course::addStudent(Student *student) {
        for (Student *x: students) {
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
            if (students[i]->getName() == student->getName()) {
                return i;
            }
        }
        return students.size() + 1;
    }
}