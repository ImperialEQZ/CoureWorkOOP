#ifndef COURSEWORKOOP_STUDENTFACTORY_H
#define COURSEWORKOOP_STUDENTFACTORY_H
#include <string>
#include "Student.h"
//Создание студента со всей информацией о нем
class StudentFactory {
public:
    static Student createStudent(const std::string& institute,
                                 const std::string& direction,
                                 const std::string& book,
                                 const std::string& group,
                                 const std::string& name,
                                 const std::string& surname,
                                 const std::string& middlename) {
        return Student(institute, direction, book, group, name, surname, middlename);
    }
};
#endif //COURSEWORKOOP_STUDENTFACTORY_H
