/*
 * Jiezhi Winston Zuo-yu
 * course.h
 */

#ifndef REC08_COURSE_H
#define REC08_COURSE_H
#include<iostream>
#include<vector>
#include<string>

namespace BrooklynPoly {

    class Student;

    class Course {
        friend std::ostream& operator<<(std::ostream& os, const Course& rhs);
    public:
        // Course methods needed by Registrar
        Course(const std::string& courseName);
        const std::string& getName() const;
        bool addStudent(Student* student);
        void removeStudentsFromCourse(Student* student);
        size_t findStudent(const Student* student) const;
        size_t studentsSize() const;
    private:
        std::string name;
        std::vector<Student*> students;
    };

}
#endif //REC08_COURSE_H
