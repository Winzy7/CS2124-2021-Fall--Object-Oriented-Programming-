/*
 * Jiezhi Winston Zuo-yu
 * student.h
 */

#ifndef REC08_STUDENT_H
#define REC08_STUDENT_H
#include<iostream>
#include<vector>
#include<string>

namespace BrooklynPoly {

    class Course;

    class Student {
        friend std::ostream &operator<<(std::ostream &os, const Student &rhs);

    public:
        // Student methods needed by Registrar
        Student(const std::string &myName);

        const std::string &getName() const;

        bool addCourse(Course *course);

        size_t findCourse(const Course *course);

        size_t coursesSize() const;

        // Student method needed by Course
        void removedFromCourse(Course *course);

    private:
        std::string name;
        std::vector<Course *> courses;
    };
}
#endif //REC08_STUDENT_H
