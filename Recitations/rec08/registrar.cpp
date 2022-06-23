/*
 * Jiezhi Winston Zuo-yu
 * registrar.cpp
 */

#include "registrar.h"
#include "student.h"
#include "course.h"

#include <vector>
#include <string>
#include <iostream>
using namespace std;

namespace BrooklynPoly {

    Registrar::Registrar() {}

    ostream &operator<<(ostream &os, const Registrar &rhs) {
        os << "Registrar's Report" << endl;
        os << "Courses: " << endl;
        for (Course *course: rhs.courses) {
            os << *course;
        }
        os << "Students: " << endl;
        for (Student *student: rhs.students) {
            os << *student;
        }
        return os;
    }

    bool Registrar::addCourse(const string &courseName) {
        for (Course *course: courses) {
            if (course->getName() == courseName) {
                return false;
            }
        }
        courses.push_back(new Course(courseName));
        return true;
    }

    bool Registrar::addStudent(const string &studentName) {
        for (Student *student: students) {
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
        if ((studentPos != (students.size() + 1)) && (coursePos != (courses.size() + 1))) {

            if (courses[coursePos]->findStudent(students[studentPos])
                == (courses[coursePos]->studentsSize() + 1)) {
                if (students[studentPos]->findCourse(courses[coursePos])
                    == (students[studentPos]->coursesSize() + 1)) {
                    courses[coursePos]->addStudent(students[studentPos]);
                    students[studentPos]->addCourse(courses[coursePos]);
                    return true;
                }
            }
        }
        return false;
    }

    size_t Registrar::findStudent(const string &studentName) const {
        for (size_t i = 0; i < students.size(); ++i) {
            if (students[i]->getName() == studentName) {
                return i;
            }
        }
        return students.size() + 1;
    }

    size_t Registrar::findCourse(const string &courseName) const {
        for (size_t i = 0; i < courses.size(); ++i) {
            if (courses[i]->getName() == courseName) {
                return i;
            }
        }
        return courses.size() + 1;
    }

    bool Registrar::cancelCourse(const string &courseName) {
        size_t coursePos = findCourse(courseName);
        if (coursePos != courses.size() + 1) {
            for (Student *student: students) {
                courses[coursePos]->removeStudentsFromCourse(student);
            }
            for (size_t k = coursePos; k < courses.size() - 1; ++k) {
                courses[coursePos] = courses[coursePos + 1];
            }
            delete courses[courses.size() - 1];
            courses.pop_back();
            return true;
        }
        return false;
    }

    void Registrar::purge() {
        for (Course *course: courses) {
            delete course;
        }
        for (Student *student: students) {
            delete student;
        }
        courses.clear();
        students.clear();
    }
}