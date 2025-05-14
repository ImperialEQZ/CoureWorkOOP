#include "ControlUnit.h"
#include <iostream>
#include <limits>
#include <vector>
#include "json.hpp"
#include "WorkLoad.h"

using json = nlohmann::json;

void ControlUnit::run() {
    int choice;
    do {
        printMainMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //очистка буфера

        switch (choice) {
            case 1: // Выбрать институт
                selectInstitute();
                break;
            case 2: // Сохранить данные
                gradeBook->saveData();
                break;
            case 3: // Выход
                std::cout << "Exiting the programm.\n";
                gradeBook->saveData(); // Сохраняем данные при выходе
                break;
            default:
                std::cout << "Incorrect input.\n";
        }
    } while (choice != 3);
}
//Будет 2 института: ИИТУС и ИЭИЭ
void ControlUnit::selectInstitute() {
    instituteMenu();
    int instChoice;
    std::cin >> instChoice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (instChoice == 3) return;

    std::string institute;
    if (instChoice == 1) institute = "IITUS";
    else if (instChoice == 2) institute = "IEIE";
    else {
        std::cout << "Incorrect input.\n";
        return;
    }

    selectDepartment(institute);
}
//В сумме 4 кафедры: ПОВТАС, ИТ, Электроэнергетика и электротехника, Теплоэнергетика и теплотехника
void ControlUnit::selectDepartment(const std::string& institute) {
    departmentMenu(institute);
    int depChoice;
    std::cin >> depChoice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (depChoice == 3) return;

    std::string department;
    //ИИТУС
    if (institute == "IITUS") {
        if (depChoice == 1) department = "POVTAS";//Легенда - кафедра
        else if (depChoice == 2) department = "IT";//Кафедра Инф. технологий
        else {
            std::cout << "Incorrect input.\n";
            return;
        }
    } else { // ИЭИЭ
        if (depChoice == 1) department = "Electricity and electrical engineering";//ЭиЭ
        else if (depChoice == 2) department = "Heat power engineering and heat engineering";//ТиТ
        else {
            std::cout << "Incorrect input.\n";
            return;
        }
    }

    selectGroup(institute, department);
}
//Выбор групп в разных институтах и кафедрах
void ControlUnit::selectGroup(const std::string& institute, const std::string& department) {
    std::cout << "\nGroups:\n";

    std::vector<std::string> groups;
    if (institute == "IITUS") {
        if (department == "POVTAS") {
            std::cout << "1. VT-232\n2. PV-233\n";//Две группы ПОВТАСа
            groups = {"VT-232", "PV-233"};
        } else if (department == "IT") {
            std::cout << "1. IST-231\n2. IST-232\n"; ////Две группы ИТ
            groups = {"IST-231", "IST-232"};
        } else {
            std::cout << "No groups for this department.\n";//Не найдена группа на кафедре
            return;
        }
    } else { // Институт ИЭИЭ
        if (department == "Electricity and electrical engineering") {
            std::cout << "1. EiE-231\n2. EiE-232\n";//Две группы ЭиЭ
            groups = {"EK-231", "EK-232"};
        } else if (department == "Heat power engineering and heat engineering") {
            std::cout << "1. TiT-231\n2. TiT-232\n";//Две группы ТиТ
            groups = {"TiT-231", "TiT-232"};
        } else {
            std::cout << "No groups for this department.\n";//Не найдена группа на кафедре
            return;
        }
    }
    std::cout << "3. Back\n";

    int groupChoice;
    std::cin >> groupChoice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (groupChoice == 3) return;

    if (groupChoice < 1 || groupChoice > groups.size()) {
        std::cout << "Incorrect input.\n";
        return;
    }

    std::string group = groups[groupChoice - 1];
    selectStudent(institute, department, group);
}

