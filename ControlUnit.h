#ifndef COURSEWORKOOP_CONTROLUNIT_H
#define COURSEWORKOOP_CONTROLUNIT_H

#include "MagazineRatings.h"
#include "Student.h"
#include "WorkLoad.h"
#include <memory>
#include <iostream>
#include <limits>

class ControlUnit {
private:
    GradeBook* gradeBook;

    void printMainMenu() {
        std::cout << "\n=== Accounting for students academic performance at the university ==="
                  << "\n1. Select an institute"
                  << "\n2. Save data"
                  << "\n3. Exit\n";
    }
    //Меню институтов
    void instituteMenu() {
        //1) ИИТУС 2) ИЭИЭ
        std::cout << "\nInstitutions:\n1. IITUS\n2. IEEI\n3. Back\n";
    }
    //Меню кафедр
    void departmentMenu(const std::string& institute) {
        std::cout << "\nDepartment:\n";
        if (institute == "IITUS") std::cout << "1. POVTAS\n2. IT\n";
        //1) Электроэнергетика и электротехника  2) Теплоэнергетика и теплотехника
        else std::cout << "1. Electricity and electrical engineering\n2. Heat power engineering and heat engineering\n";
        std::cout << "3. Back\n";
    }

    void studentOperations(const std::string& institute, const std::string& department, const std::string& group, const std::string& studentId);
    //Поменять оценку
    void changeGrade(const std::string& institute, const std::string& department, const std::string& group, const std::string& studentId);
    //Показать средний балл студента
    void displayAverageGrade(const std::string& studentId);
    //Показать информацию об студенте (ФИО, группа, номер зачетной книжки, предметы, оценки)
    void displayStudentInfo(const std::string& institute, const std::string& department, const std::string& group, const std::string& studentId);
    //Выбор института
    void selectInstitute();
    //Выбор кафедры
    void selectDepartment(const std::string& institute);
    //Выбор группы
    void selectGroup(const std::string& institute, const std::string& department);
    //Выбор студента из группы
    void selectStudent(const std::string& institute, const std::string& department, const std::string& group);

public:
    //Получение экзепляра журнала оценок и информации
    ControlUnit() : gradeBook(GradeBook::getInstance()) {}
    //Запуск панели управления
    void run();
};
#endif //COURSEWORKOOP_CONTROLUNIT_H
