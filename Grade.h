#ifndef COURSEWORKOOP_GRADE_H
#define COURSEWORKOOP_GRADE_H
#include <string>
#include <iostream>

class Grade {
public:
    std::string assignmentName;//Название предмета
    int mark;//оценка

    Grade(std::string name, int m) : assignmentName(name), mark(m) {}

    void outputGrade() const {
        std::cout << "Название предмета: " << assignmentName << ", Оценка: " << mark << std::endl;
    }
};
#endif //COURSEWORKOOP_GRADE_H
