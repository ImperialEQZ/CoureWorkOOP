#ifndef COURSEWORKOOP_DEPARTMENT_H
#define COURSEWORKOOP_DEPARTMENT_H
#include <iostream>
#include <string>
#include <vector>
#include "Group.h"

class Department {
public:
    std::string name;
    std::vector<Group> groups;

    Department(const std::string& name) : name(name) {}

    void addGroup(const Group& group) {
        groups.push_back(group);
    }

    void displayDepartmentInfo() const {
        std::cout << "Department: " << name << "\n";
        std::cout << "Groups:\n";
        for (const auto& group : groups) {
            group.displayGroupInfo();
        }
    }
};
#endif //COURSEWORKOOP_DEPARTMENT_H
