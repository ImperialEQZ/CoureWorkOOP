#ifndef COURSEWORKOOP_STUDENT_H
#define COURSEWORKOOP_STUDENT_H
#include <string>
#include <vector>
#include "Grade.h"
//Создание класса студент
class Student {
public:
    std::string Name;//Имя
    std::string SurName;//Фамилия
    std::string MiddleName;//Отчество
    std::string InstituteName;//Название института
    std::string DirectionName;//Название направления
    std::string NumberCreditBook;//Номер зачетной книжки
    std::vector<Grade> grades;// вектор оценок по предметам
    std::string GroupName;//Название группы (пример, ВТ-232)

    Student() {}

    Student(std::string Name) : Name(Name) {}

    Student(std::string institute, std::string direction, std::string book,
            std::string group, std::string Name, std::string SurName, std::string MiddleName)

            : InstituteName(institute), DirectionName(direction), NumberCreditBook(book),
              GroupName(group), Name(Name), SurName(SurName), MiddleName(MiddleName) {}

    double getAverageRating() const {
        if (grades.empty()) return 0;
        double sum = 0.0;//Для точности
        for (const auto& grade : grades) {
            sum += grade.mark;
        }
        return sum / grades.size();
    }

    void outputStudentInfo() const {
        std::cout << "ФИО: " << Name << " " << SurName << " " << MiddleName << std::endl;
        std::cout << "Группа: " << GroupName << std::endl;
        std::cout << "Номер зачетной книжки: " << NumberCreditBook << std::endl;
    }

    void outputGrades() const {
        if (grades.empty()) {
            std::cout << "У студента нет оценок." << std::endl;
            return;
        }
        std::cout << "Оценки студента:" << std::endl;
        for (const auto& grade : grades) {
            grade.outputGrade();
        }
    }
};
#endif //COURSEWORKOOP_STUDENT_H
