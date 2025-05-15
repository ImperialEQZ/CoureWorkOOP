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
        int count = 0;
        for (const auto& grade : grades) {
            if (grade.type != WorkloadType::CREDIT) { // Исключаем зачеты, доработка старой функции
                sum += grade.mark;
                count++;
            }
        }
        return (count > 0) ? (sum / count) : 0.0;
    }
    //Вывод информации о студенте
    void outputStudentInfo() const {
        std::cout << "FULL NAME: " << Name << " " << SurName << " " << MiddleName << std::endl;
        std::cout << "Group: " << GroupName << std::endl;
        std::cout << "Credit book number: " << NumberCreditBook << std::endl;
    }
};
#endif //COURSEWORKOOP_STUDENT_H
