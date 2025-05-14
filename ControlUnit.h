#ifndef COURSEWORKOOP_CONTROLUNIT_H
#define COURSEWORKOOP_CONTROLUNIT_H

#include "MagazineRatings.h"
#include "Student.h"
#include "UnFabrika.h"
#include "WorkLoad.h"
#include <memory>
#include <iostream>
#include <limits>

class ControlUnit {
private:
    GradeBook* gradeBook;

    void printMainMenu() {
        std::cout << "\n=== Учет успеваемости студентов в ВУЗе ==="
                  << "\n1. Выбрать институт"
                  << "\n2. Сохранить данные"
                  << "\n3. Выход\n";
    }

    void instituteMenu() {
        std::cout << "\nИнституты:\n1. ИИТУС\n2. ИЭИЭ\n3. Назад\n";
    }

    void departmentMenu(const std::string& institute) {
        std::cout << "\nКафедры:\n";
        if (institute == "ИИТУС") std::cout << "1. ПОВТАС\n2. ИТ\n";
        else std::cout << "1. Электроэнергетика и электротехника\n2. Теплоэнергетика и теплотехника\n";
        std::cout << "3. Назад\n";
    }



};
#endif //COURSEWORKOOP_CONTROLUNIT_H
