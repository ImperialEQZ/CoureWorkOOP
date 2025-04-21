#ifndef COURSEWORKOOP_CONTROLUNIT_H
#define COURSEWORKOOP_CONTROLUNIT_H

#include "MagazineRatings.h"
#include "Student.h"
#include "UnFabrika.h"
#include <memory>
#include <iostream>
#include <limits>

class ControlUnit {
private:
    GradeBook* gradeBook;
    std::unique_ptr<UniversityFactory> factory;

    void printMenu() {
        std::cout << "\n=== Учет успеваемости студентов ===\n"
                  << "1. Просмотр всех институтов и групп\n"
                  << "2. Изменить оценку студента\n"
                  << "3. Просмотреть оценки студента\n"
                  << "4. Просмотреть информацию о студенте\n"
                  << "5. Сохранить данные в файл\n"
                  << "6. Подсчитать средний балл студента\n"
                  << "7. Выход\n"
                  << "Выберите действие: ";
    }

    void displayInstitutes() {
        for (const auto& groupEntry : gradeBook->markBook) {
            std::cout << "Группа: " << groupEntry.first << std::endl;
            for (const auto& studentEntry : groupEntry.second) {
                const StudentInfo& studentInfo = studentEntry.second.first;
                std::cout << "  Студент (ID: " << studentEntry.first << "): "
                          << studentInfo.surname << " " << studentInfo.name << " " << studentInfo.middlename
                          << std::endl;
            }
        }
    }

    void changeGrade() {
        std::string groupName, studentID, subject;
        int newMark;

        std::cout << "Введите название группы: ";
        std::cin >> groupName;
        std::cout << "Введите номер зачетной книжки студента: ";
        std::cin >> studentID;
        std::cout << "Введите название предмета: ";
        std::cin >> subject;
        std::cout << "Введите новую оценку: ";
        std::cin >> newMark;

        gradeBook->updateGrade(groupName, studentID, subject, newMark);
        std::cout << "Оценка изменена.\n";
    }

    void viewStudentGrades() {
        std::string groupName, studentID;

        std::cout << "Введите название группы: ";
        std::cin >> groupName;
        std::cout << "Введите номер зачетной книжки студента: ";
        std::cin >> studentID;

        const auto& group = gradeBook->markBook.find(groupName);
        if (group != gradeBook->markBook.end()) {
            const auto& student = group->second.find(studentID);
            if (student != group->second.end()) {
                std::cout << "Оценки студента (ID: " << studentID << ") в группе " << groupName << ":\n";
                for (const auto& grade : student->second.second) {
                    std::cout << "  " << grade.first << ": " << grade.second << std::endl;
                }
            } else {
                std::cout << "Студент не найден.\n";
            }
        } else {
            std::cout << "Группа не найдена.\n";
        }
    }

    void viewStudentInfo() {
        std::string groupName, studentID;

        std::cout << "Введите название группы: ";
        std::cin >> groupName;
        std::cout << "Введите номер зачетной книжки студента: ";
        std::cin >> studentID;

        StudentInfo studentInfo = gradeBook->getStudentInfo(groupName, studentID);
        std::cout << "Информация о студенте (ID: " << studentID << ") в группе " << groupName << ":\n";
        std::cout << "  ФИО: " << studentInfo.surname << " " << studentInfo.name << " " << studentInfo.middlename << std::endl;
    }

    void calculateStudentAverageGrade() {
        std::string groupName, studentID;

        std::cout << "Введите название группы: ";
        std::cin >> groupName;
        std::cout << "Введите номер зачетной книжки студента: ";
        std::cin >> studentID;

        double averageGrade = gradeBook->calculateAverageGrade(groupName, studentID);
        std::cout << "Средний балл студента (ID: " << studentID << ") в группе " << groupName << ": " << averageGrade << std::endl;
    }

    void clearInputBuffer() {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

public:
    ControlUnit() : gradeBook(GradeBook::getInstance()),
                    factory(std::make_unique<TechnicalInstituteFactory>()) {}

    void run() {
        int choice;
        do {
            printMenu();
            std::cin >> choice;

            if (std::cin.fail()) {
                std::cout << "Неверный ввод. Пожалуйста, введите число.\n";
                std::cin.clear();
                clearInputBuffer();
                choice = -1;
                continue;
            }

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            switch (choice) {
                case 1:
                    displayInstitutes();
                    break;
                case 2:
                    changeGrade();
                    break;
                case 3:
                    viewStudentGrades();
                    break;
                case 4:
                    viewStudentInfo();
                    break;
                case 5:
                    gradeBook->saveToFile("output.txt");
                    break;
                case 6:
                    calculateStudentAverageGrade();
                    break;
                case 7:
                    std::cout << "Выход...\n";
                    break;
                default:
                    std::cout << "Неверный ввод!\n";
            }
        } while (choice != 7);
    }
};
#endif //COURSEWORKOOP_CONTROLUNIT_H
