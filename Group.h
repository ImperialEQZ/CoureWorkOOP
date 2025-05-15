#ifndef COURSEWORKOOP_GROUP_H
#define COURSEWORKOOP_GROUP_H
#include <string>
#include <vector>
#include "Student.h"

class Group {
public:
    std::string name;
    std::vector<Student> students;

    Group(const std::string& name) : name(name) {}

    void addStudent(const Student& student) {
        students.push_back(student);
    }

    void displayGroupInfo() const {
        std::cout << "Groups: " << name << "\n";
        std::cout << "Students:\n";
        for (const auto& student : students) {
            student.outputStudentInfo();
        }
    }
};
#endif //COURSEWORKOOP_GROUP_H
