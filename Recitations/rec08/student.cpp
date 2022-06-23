/*
 * Jiezhi Winston Zuo-yu
 * student.cpp
 */

#include "student.h"
#include "course.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace BrooklynPoly {

    Student::Student(const std::string &myName) : name(myName) {}

    const std::string &Student::getName() const {
        return name;
    }

    size_t Student::coursesSize() const {
        return courses.size();
    }

    std::ostream &operator<<(std::ostream &os, const Student &rhs) {
        os << rhs.name << ": ";
        if (rhs.courses.size() == 0) {
            os << "No Courses";
        }
        for (Course *course: rhs.courses) {
            os << course->getName() << " ";
        }
        os << std::endl;
        return os;
    }

    size_t Student::findCourse(const Course *course) {
        for (size_t i = 0; i < courses.size(); ++i) {
            if (courses[i]->getName() == course->getName()) {
                return i;
            }
        }
        return courses.size() + 1;
    }

    bool Student::addCourse(Course *course) {
        for (Course *classes: courses) {
            if (classes->getName() == course->getName()) {
                return false;
            }
        }
        courses.push_back(course);
        return true;
    }

    void Student::removedFromCourse(Course *course) {
        size_t coursePos = findCourse(course);
        if (coursePos != courses.size() + 1) {
            for (size_t i = coursePos; i < courses.size() - 1; ++i) {
                courses[i] = courses[i + 1];
            }
            courses.pop_back();
        }
    }

}



