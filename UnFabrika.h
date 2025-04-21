#ifndef COURSEWORKOOP_UNFABRIKA_H
#define COURSEWORKOOP_UNFABRIKA_H
#include "Student.h"
#include <string>
#include <memory>

// Абстрактная фабрика для создания объектов университета
class UniversityFactory {
public:
    virtual ~UniversityFactory() = default;
    virtual std::unique_ptr<Student> createStudent(
            const std::string& institute,
            const std::string& direction,
            const std::string& bookNumber,
            const std::string& group,
            const std::string& name,
            const std::string& surname,
            const std::string& middlename
    ) = 0;
};

// Конкретная фабрика, для технического института
class TechnicalInstituteFactory : public UniversityFactory {
public:
    std::unique_ptr<Student> createStudent(
            const std::string& institute,
            const std::string& direction,
            const std::string& bookNumber,
            const std::string& group,
            const std::string& name,
            const std::string& surname,
            const std::string& middlename
    ) override {
        return std::make_unique<Student>(institute, direction, bookNumber, group, name, surname, middlename);
    }
};

#endif //COURSEWORKOOP_UNFABRIKA_H
