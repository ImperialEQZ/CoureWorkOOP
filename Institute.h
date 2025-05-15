#ifndef COURSEWORKOOP_INSTITUTE_H
#define COURSEWORKOOP_INSTITUTE_H
#include <string>
#include <vector>
#include "Department.h"

class Institute {
public:
    std::string name;
    std::vector<Department> departments;

    Institute(const std::string& name) : name(name) {}

    void addDepartment(const Department& department) {
        departments.push_back(department);
    }

    void displayInstituteInfo() const {
        std::cout << "Institute: " << name << "\n";
        std::cout << "Departments:\n";
        for (const auto& department : departments) {
            department.displayDepartmentInfo();
        }
    }
};
#endif //COURSEWORKOOP_INSTITUTE_H
