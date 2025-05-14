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
            groups = {"EiE-231", "EiE-232"};
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
//Выбор студента из группы (в группе может быть несколько студентов)
void ControlUnit::selectStudent(const std::string& institute, const std::string& department, const std::string& group) {
    std::vector<std::string> studentIds = gradeBook->getStudentIds(institute, department, group);

    if (studentIds.empty()) {
        std::cout << "No students in the group.\n";
        return;
    }

    std::cout << "\nStudents:\n";
    for (size_t i = 0; i < studentIds.size(); ++i) {
        // Получаем информацию о студенте для отображения ФИО
        json studentInfo = gradeBook->getStudentInfo(institute, department, group, studentIds[i]);
        if (!studentInfo.empty()) {
            std::cout << i + 1 << ". " << studentInfo["surname"].get<std::string>() << " "
                      << studentInfo["name"].get<std::string>() << " "
                      << studentInfo["middlename"].get<std::string>()
                      << " (ID: " << studentIds[i] << ")" << "\n";
        } else {
            std::cout << i + 1 << ". (Error: Student information not found) (ID: " << studentIds[i] << ")\n";
        }
    }
    //Выбор студента из группы
    int studentChoice;
    std::cout << "Select a student (1-" << studentIds.size() << "): ";
    std::cin >> studentChoice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //Если нет людей в группе или неккоректный выбор студента
    if (studentChoice < 1 || studentChoice > studentIds.size()) {
        std::cout << "Incorrect input.\n";
        return;
    }

    std::string studentId = studentIds[studentChoice - 1];
    studentOperations(institute, department, group, studentId);
}
//Операция над студентом (изменить оценку, посчитать средний балл, получить всю информацию о студенте)
void ControlUnit::studentOperations(const std::string& institute, const std::string& department, const std::string& group, const std::string& studentId) {
    while (true) {
        std::cout << "\nStudent operations (ID: " << studentId << "):\n";
        std::cout << "1. Change grade\n2. Get grade average\n3. Get information about student\n4. Back\n";

        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                changeGrade(institute, department, group, studentId);
                break;
            case 2:
                displayAverageGrade(studentId);
                break;
            case 3:
                displayStudentInfo(institute, department, group, studentId);
                break;
            case 4:
                return;
            default:
                std::cout << "Incorrect input.\n";
        }
    }
}
//Изменение оценок по предмету
void ControlUnit::changeGrade(const std::string& institute, const std::string& department,
                              const std::string& group, const std::string& studentId) {
    // Получаем информацию о студенте
    json studentInfo = gradeBook->getStudentInfo(institute, department, group, studentId);

    std::string subject;//Название предмета
    std::string workloadTypeStr;//Тип работы в виде строки
    int mark;//Оценка

    // Выводим список предметов студента
    std::cout << "\nList of subject:\n";
    for (auto& [subj, grade] : studentInfo["grades"].items()) {
        std::cout << "- " << subj << "\n";
    }
    //Пользователь должен написать название предмета
    std::cout << "\nWrite name subject: ";
    std::getline(std::cin, subject);

    // Проверяем, есть ли такой предмет у студента, нет - Ошибка: не найден
    if (!studentInfo["grades"].contains(subject)) {
        std::cout << "Error: subject not found!\n";
        return;
    }

    // Получаем текущий тип работы для написанного предмета
    std::string currentType = studentInfo["grades"][subject]["type"].get<std::string>();
    //Текущий тип работы выбранного предмета (подсказка для пользователя)
    std::cout << "Current type work: " << currentType << "\n";
    std::cout << "Type work (1 - exam, 2 - laboratory, 3 - coursework, 4 - credit): ";
    std::getline(std::cin, workloadTypeStr);

    //Выбор вида нагрузки
    WorkloadType newType;
    if (workloadTypeStr == "1") newType = WorkloadType::EXAM;
    else if (workloadTypeStr == "2") newType = WorkloadType::LAB;
    else if (workloadTypeStr == "3") newType = WorkloadType::COURSE_PROJECT;
    else if (workloadTypeStr == "4") newType = WorkloadType::CREDIT;
    else {
        std::cout << "Error: enter 1-4!\n";
        return;
    }

    // Преобразуем newType в строку для сравнения
    std::string newTypeStr;
    switch(newType) {
        case WorkloadType::EXAM: newTypeStr = "exam"; break;
        case WorkloadType::LAB: newTypeStr = "laboratory"; break;
        case WorkloadType::COURSE_PROJECT: newTypeStr = "coursework"; break;
        case WorkloadType::CREDIT: newTypeStr = "credit"; break;
    }

    // Сравниваем типы (если пользователь ошибся - выводим текущий тип нагрузки у предмета)
    if (currentType != newTypeStr) {
        std::cout << "Error: subject " << subject
                  << " is not a type of work " << newTypeStr << "!\n";
        std::cout << "Current type of work: " << currentType << "\n";
        return;
    }

    // Если типы нагрузки совпадают, продолжаем изменение оценки
    if (newType != WorkloadType::CREDIT) {//У зачета не важна оценка = не меняем
        std::cout << "New grade (2-5): ";
        std::cin >> mark;
        if (mark < 2 || mark > 5) {
            std::cout << "Incorrect grade!\n";
            return;
        }
    } else {
        mark = 0; // Для зачета
    }
    std::cin.ignore();

    // Обновляем оценку
    TechnicalWorkloadFactory factory;
    std::unique_ptr<Workload> workload;
    switch(newType) {
        case WorkloadType::LAB: workload = factory.createLab(mark); break;
        case WorkloadType::EXAM: workload = factory.createExam(mark); break;
        case WorkloadType::COURSE_PROJECT: workload = factory.createCourseProject(mark); break;
        case WorkloadType::CREDIT: workload = factory.createCredit(); break;
    }

    gradeBook->addGrade(institute, department, group, studentId, subject, newType, workload->getMark());
    std::cout << "Grade has been changed!\n";
}
//Вывод среднего арифметического оценок
void ControlUnit::displayAverageGrade(const std::string& studentId) {
    double average = gradeBook->calculateAverage(studentId);
    std::cout << "Average score: " << average << "\n";
}
//Вывод полной информации о студенте
void ControlUnit::displayStudentInfo(const std::string& institute, const std::string& department, const std::string& group, const std::string& studentId) {
    // Получаем информацию о студенте из GradeBook (MagazineRatings)
    json studentInfo = gradeBook->getStudentInfo(institute, department, group, studentId);
    //Студент не найден
    if (studentInfo.empty()) {
        std::cout << "Student not found.\n";
        return;
    }
    //Вывод информации
    //ФИО
    std::cout << "FULL NAME: " << studentInfo["surname"].get<std::string>() << " " << studentInfo["name"].get<std::string>() << " " << studentInfo["middlename"].get<std::string>() << "\n";
    //Группа
    std::cout << "Group: " << group << "\n";
    //Номер зачетной книжки
    std::cout << "Credit book number: " << studentId << "\n";
    //Оценки по предметам (с названием предмета и его типом работы, нагрузки)
    std::cout << "\nGrades:\n";
    // Используем итератор для обхода оценок
    for (auto it = studentInfo["grades"].begin(); it != studentInfo["grades"].end(); ++it) {
        std::string subject = it.key();
        json gradeData = it.value();
        std::cout << "  " << subject << ": " << gradeData["mark"].get<int>() << " (" << gradeData["type"].get<std::string>() << ")\n";
    }
}